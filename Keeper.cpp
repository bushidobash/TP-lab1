#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "AdminStaff.h"
#include "DemoException.h"

#include <iostream>
#include <fstream>
#include <limits>

Keeper::Keeper()
    : items_(nullptr), size_(0), cap_(0)
{
    cap_ = INITIAL_CAP;
    items_ = new Base*[cap_];
    for (std::size_t i = 0; i < cap_; ++i) items_[i] = nullptr;
}

Keeper::~Keeper() {
    for (std::size_t i = 0; i < size_; ++i) {
        delete items_[i];
        items_[i] = nullptr;
    }
    delete[] items_;
    items_ = nullptr;
}

void Keeper::ensureCapacity() {
    if (size_ < cap_) return;
    std::size_t newCap = cap_ * 2;
    Base** newArr = new Base*[newCap];
    for (std::size_t i = 0; i < newCap; ++i) newArr[i] = nullptr;
    for (std::size_t i = 0; i < size_; ++i) newArr[i] = items_[i];
    delete[] items_;
    items_ = newArr;
    cap_ = newCap;
}

void Keeper::addObject() {
    std::cout << "Выберите тип объекта: 1 - Student, 2 - Teacher, 3 - AdminStaff: ";
    int ch{};
    if (!(std::cin >> ch)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw DemoException("Неверный ввод типа");
    }

    Base* obj = nullptr;
    switch (ch) {
        case 1: obj = new Student(); break;
        case 2: obj = new Teacher(); break;
        case 3: obj = new AdminStaff(); break;
        default: throw DemoException("Неверный выбор типа объекта");
    }

    try {
        obj->input();
        ensureCapacity();
        items_[size_++] = obj;
    } catch (...) {
        delete obj;
        throw;
    }
}

void Keeper::removeObject(std::size_t index) {
    if (index >= size_) throw DemoExceptionBadIndex();
    delete items_[index];
    // сдвигаем
    for (std::size_t i = index; i + 1 < size_; ++i) {
        items_[i] = items_[i + 1];
    }
    items_[size_ - 1] = nullptr;
    --size_;
}

void Keeper::viewAll() const {
    if (size_ == 0) {
        std::cout << "Нет объектов.\n";
        return;
    }
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << "Объект " << i << ": ";
        items_[i]->display();
    }
}

void Keeper::editObject(std::size_t index) {
    if (index >= size_) throw DemoExceptionBadIndex();
    std::cout << "Текущие данные:\n";
    items_[index]->display();
    std::cout << "Введите новые данные:\n";
    items_[index]->input();
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream out(filename, std::ios::out);
    if (!out) throw DemoException("Ошибка открытия файла для записи");
    out << size_ << '\n';
    for (std::size_t i = 0; i < size_; ++i) {
        items_[i]->save(out);
    }
    out.close();
}

Base* Keeper::createFromChar(char t) const {
    switch (t) {
        case 'S': return new Student();
        case 'T': return new Teacher();
        case 'A': return new AdminStaff();
        default: throw DemoException("Неизвестный тип при загрузке");
    }
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::in);
    if (!in) throw DemoException("Ошибка открытия файла для чтения");
    // сначала очистим текущие
    for (std::size_t i = 0; i < size_; ++i) {
        delete items_[i];
        items_[i] = nullptr;
    }
    size_ = 0;

    std::size_t newSize{};
    in >> newSize;
    if (!in) throw DemoException("Ошибка чтения размера из файла");

    for (std::size_t i = 0; i < newSize; ++i) {
        char t{};
        in >> t;
        if (!in) throw DemoException("Ошибка чтения типа объекта");
        Base* obj = createFromChar(t);
        try {
            obj->load(in);
            ensureCapacity();
            items_[size_++] = obj;
        } catch (...) {
            delete obj;
            throw;
        }
    }
    in.close();
}