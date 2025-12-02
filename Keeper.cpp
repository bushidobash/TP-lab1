#include "Keeper.h"
#include "Student.h"
#include "Teacher.h"
#include "AdminStaff.h"
#include "DemoException.h"

#include <iostream>
#include <fstream>
#include <limits>

// Конструктор по умолчанию
Keeper::Keeper()
    : items_(nullptr), size_(0), cap_(0)
{
    // Устанавливаем начальную емкость массива
    cap_ = INITIAL_CAP;
    // Выделяем динамическую память для массива указателей
    items_ = new Base*[cap_];
    // Инициализируем все указатели значением nullptr
    for (std::size_t i = 0; i < cap_; ++i) items_[i] = nullptr;
}

// Деструктор - освобождает выделенную память
Keeper::~Keeper() {
    // Удаляем все объекты, на которые ссылаются указатели
    for (std::size_t i = 0; i < size_; ++i) {
        delete items_[i];
        items_[i] = nullptr;
    }
    // Удаляем сам массив указателей
    delete[] items_;
    items_ = nullptr;
}

// Метод для обеспечения достаточной емкости массива
void Keeper::ensureCapacity() {
    // Если текущий размер меньше емкости, ничего не делаем
    if (size_ < cap_) return;
    // Увеличиваем емкость в два раза
    std::size_t newCap = cap_ * 2;
    // Создаем новый массив с увеличенной емкостью
    Base** newArr = new Base*[newCap];
    // Инициализируем новый массив nullptr
    for (std::size_t i = 0; i < newCap; ++i) newArr[i] = nullptr;
    // Копируем существующие указатели в новый массив
    for (std::size_t i = 0; i < size_; ++i) newArr[i] = items_[i];
    // Удаляем старый массив
    delete[] items_;
    // Обновляем указатель на новый массив
    items_ = newArr;
    // Обновляем значение емкости
    cap_ = newCap;
}

// Метод добавления нового объекта
void Keeper::addObject() {
    // Запрашиваем у пользователя тип объекта
    std::cout << "Выберите тип объекта: 1 - Student, 2 - Teacher, 3 - AdminStaff: ";
    int ch{};
    // Обрабатываем некорректный ввод
    if (!(std::cin >> ch)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw DemoException("Неверный ввод типа");
    }

    Base* obj = nullptr;
    // Создаем объект в зависимости от выбора пользователя
    switch (ch) {
        case 1: obj = new Student(); break;
        case 2: obj = new Teacher(); break;
        case 3: obj = new AdminStaff(); break;
        default: throw DemoException("Неверный выбор типа объекта");
    }

    // Блок try для безопасной обработки исключений
    try {
        // Запрашиваем данные для объекта
        obj->input();
        // Проверяем/увеличиваем емкость массива
        ensureCapacity();
        // Добавляем объект в массив и увеличиваем счетчик
        items_[size_++] = obj;
    } catch (...) {
        // В случае исключения удаляем созданный объект и пробрасываем исключение дальше
        delete obj;
        throw;
    }
}

// Метод удаления объекта по индексу
void Keeper::removeObject(std::size_t index) {
    // Проверка корректности индекса
    if (index >= size_) throw DemoExceptionBadIndex();
    // Удаляем объект по указанному индексу
    delete items_[index];
    // Сдвигаем все элементы после удаленного на одну позицию влево
    for (std::size_t i = index; i + 1 < size_; ++i) {
        items_[i] = items_[i + 1];
    }
    // Последний элемент обнуляем
    items_[size_ - 1] = nullptr;
    // Уменьшаем размер массива
    --size_;
}

// Метод просмотра всех объектов
void Keeper::viewAll() const {
    // Если массив пуст, выводим сообщение
    if (size_ == 0) {
        std::cout << "Нет объектов.\n";
        return;
    }
    // Итерируем по всем объектам и выводим информацию о каждом
    for (std::size_t i = 0; i < size_; ++i) {
        std::cout << "Объект " << i << ": ";
        items_[i]->display();
    }
}

// Метод редактирования объекта по индексу
void Keeper::editObject(std::size_t index) {
    // Проверка корректности индекса
    if (index >= size_) throw DemoExceptionBadIndex();
    // Показываем текущие данные объекта
    std::cout << "Текущие данные:\n";
    items_[index]->display();
    // Запрашиваем новые данные
    std::cout << "Введите новые данные:\n";
    items_[index]->input();
}

// Метод сохранения всех объектов в файл
void Keeper::saveToFile(const std::string& filename) const {
    // Открываем файл для записи
    std::ofstream out(filename, std::ios::out);
    if (!out) throw DemoException("Ошибка открытия файла для записи");
    // Записываем количество объектов
    out << size_ << '\n';
    // Для каждого объекта вызываем метод сохранения
    for (std::size_t i = 0; i < size_; ++i) {
        items_[i]->save(out);
    }
    out.close();
}

// Вспомогательный метод для создания объекта по символьному идентификатору
Base* Keeper::createFromChar(char t) const {
    switch (t) {
        case 'S': return new Student();  // Студент
        case 'T': return new Teacher();  // Преподаватель
        case 'A': return new AdminStaff();  // Административный сотрудник
        default: throw DemoException("Неизвестный тип при загрузке");
    }
}

// Метод загрузки объектов из файла
void Keeper::loadFromFile(const std::string& filename) {
    // Открываем файл для чтения
    std::ifstream in(filename, std::ios::in);
    if (!in) throw DemoException("Ошибка открытия файла для чтения");
    // Очищаем текущие объекты
    for (std::size_t i = 0; i < size_; ++i) {
        delete items_[i];
        items_[i] = nullptr;
    }
    size_ = 0;

    std::size_t newSize{};
    // Читаем количество объектов из файла
    in >> newSize;
    if (!in) throw DemoException("Ошибка чтения размера из файла");

    // Загружаем каждый объект
    for (std::size_t i = 0; i < newSize; ++i) {
        char t{};
        // Читаем символьный идентификатор типа
        in >> t;
        if (!in) throw DemoException("Ошибка чтения типа объекта");
        // Создаем объект соответствующего типа
        Base* obj = createFromChar(t);
        try {
            // Загружаем данные объекта из файла
            obj->load(in);
            // Проверяем/увеличиваем емкость
            ensureCapacity();
            // Добавляем объект в массив
            items_[size_++] = obj;
        } catch (...) {
            // В случае ошибки удаляем объект и пробрасываем исключение
            delete obj;
            throw;
        }
    }
    in.close();
}