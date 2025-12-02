#include "AdminStaff.h"
#include <iostream>
#include <limits>

// Конструктор по умолчанию - инициализирует базовый класс с типом 'A' и выводит сообщение
AdminStaff::AdminStaff() : Base('A') {
    std::cout << "[AdminStaff] Вызван конструктор по умолчанию\n";
}

// Конструктор с параметрами - инициализирует все поля класса
AdminStaff::AdminStaff(const std::string& fio, const std::string& position, const std::string& phone, const std::string& responsibility)
    : Base('A'), fio_(fio), position_(position), phone_(phone), responsibility_(responsibility)
{
    std::cout << "[AdminStaff] Вызван конструктор с параметрами\n";
}

// Конструктор копирования - создает копию объекта, копируя все поля
AdminStaff::AdminStaff(const AdminStaff& other)
    : Base(other), fio_(other.fio_), position_(other.position_), phone_(other.phone_), responsibility_(other.responsibility_)
{
    std::cout << "[AdminStaff] Вызван конструктор копирования\n";
}

// Деструктор - очищает ресурсы объекта
AdminStaff::~AdminStaff() {
    std::cout << "[AdminStaff] Вызван деструктор для " << fio_ << "\n";
}

// Метод ввода данных с клавиатуры
void AdminStaff::input() {
    // Очищаем буфер ввода перед чтением строк
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Ввод ФИО сотрудника
    std::cout << "ФИО сотрудника: ";
    std::getline(std::cin, fio_);
    
    // Ввод должности
    std::cout << "Должность: ";
    std::getline(std::cin, position_);
    
    // Ввод телефона
    std::cout << "Телефон: ";
    std::getline(std::cin, phone_);
    
    // Ввод области ответственности
    std::cout << "Область ответственности: ";
    std::getline(std::cin, responsibility_);
}

// Метод вывода информации об объекте в поток
void AdminStaff::display(std::ostream& os) const {
    os << "[Admin] ФИО: " << fio_ << ", Должность: " << position_
       << ", Телефон: " << phone_ << ", Ответственность: " << responsibility_ << '\n';
}

// Метод сохранения объекта в поток (для записи в файл)
void AdminStaff::save(std::ostream& out) const {
    out << type() << '\n';  // Записываем тип объекта (символ 'A')
    out << fio_ << '\n';    // Записываем ФИО
    out << position_ << '\n'; // Записываем должность
    out << phone_ << '\n';   // Записываем телефон
    out << responsibility_ << '\n'; // Записываем ответственность
}

// Метод загрузки объекта из потока (для чтения из файла)
void AdminStaff::load(std::istream& in) {
    // Чтение данных с пропуском начальных пробелов
    std::getline(in >> std::ws, fio_);
    std::getline(in, position_);
    std::getline(in, phone_);
    std::getline(in, responsibility_);
}

// Оператор присваивания - копирует данные из другого объекта
AdminStaff& AdminStaff::operator=(const AdminStaff& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        Base::operator=(other); // Вызов оператора присваивания базового класса
        
        // Копирование всех полей
        fio_ = other.fio_;
        position_ = other.position_;
        phone_ = other.phone_;
        responsibility_ = other.responsibility_;
    }
    return *this; // Возвращаем ссылку на текущий объект
}