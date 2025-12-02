#include "Teacher.h"
#include <iostream>
#include <limits>

// по умолчанию - вызывает конструктор базового класса с типом 'T'
Teacher::Teacher() : Base('T') {
    std::cout << "[Teacher] Вызван конструктор по умолчанию\n";
}

// с параметрами - инициализирует поля объекта переданными значениями
Teacher::Teacher(const std::string& fio, const std::string& groupsCommaSeparated, const std::string& subjectsCommaSeparated)
    : Base('T'), fio_(fio), groups_(groupsCommaSeparated), subjects_(subjectsCommaSeparated)
{
    std::cout << "[Teacher] Вызван конструктор с параметрами\n";
}

// копирования - создает глубокую копию другого объекта Teacher
Teacher::Teacher(const Teacher& other)
    : Base(other), fio_(other.fio_), groups_(other.groups_), subjects_(other.subjects_)
{
    std::cout << "[Teacher] Вызван конструктор копирования\n";
}

// Деструктор - освобождает ресурсы, выводит отладочное сообщение
Teacher::~Teacher() {
    std::cout << "[Teacher] Вызван деструктор для " << fio_ << "\n";
}

// Метод ввода данных преподавателя с клавиатуры
void Teacher::input() {
    // Очистка буфера ввода перед чтением строковых данных
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Ввод ФИО
    std::cout << "ФИО преподавателя: ";
    std::getline(std::cin, fio_);
    
    // Ввод групп ("ПИ-101, ПИ-102")
    std::cout << "Перечислите группы через запятую: ";
    std::getline(std::cin, groups_);
    
    // Ввод предметов ("Математика, Физика")
    std::cout << "Перечислите предметы через запятую: ";
    std::getline(std::cin, subjects_);
}

// Метод вывода информации о преподавателе в указанный поток
void Teacher::display(std::ostream& os) const {
    os << "[Teacher] ФИО: " << fio_ << ", Группы: " << groups_
       << ", Предметы: " << subjects_ << '\n';
}

// Метод сохранения данных преподавателя в файл
void Teacher::save(std::ostream& out) const {
    out << type() << '\n';      // Сохр тип объекта ('T')
    out << fio_ << '\n';        // Сохр ФИО
    out << groups_ << '\n';     // Сохр список групп
    out << subjects_ << '\n';   // Сохр список предметов
}

// Метод загрузки данных преподавателя из файла
void Teacher::load(std::istream& in) {
    // Чтение ФИО (std::ws пропускает лишние пробелы)
    std::getline(in >> std::ws, fio_);
    // Чтение списка групп
    std::getline(in, groups_);
    // Чтение списка предметов
    std::getline(in, subjects_);
}

// Оператор присваивания для копирования данных между объектами Teacher
Teacher& Teacher::operator=(const Teacher& other) {
    // Проверка на самоприсваивание (защита от a = a)
    if (this != &other) {
        // Вызов оператора присваивания базового класса
        Base::operator=(other);
        // Копирование полей текущего класса
        fio_ = other.fio_;
        groups_ = other.groups_;
        subjects_ = other.subjects_;
    }
    // Возврат ссылки на текущий объект для поддержки цепочки присваиваний
    return *this;
}