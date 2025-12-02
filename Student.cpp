#include "Student.h"
#include <iostream>
#include <limits>

// по умолчанию - вызывает конструктор базового класса с типом 'S'
Student::Student() : Base('S') {
    std::cout << "[Student] Вызван конструктор по умолчанию\n";
}

// с параметрами - инициализирует все поля класса
Student::Student(const std::string& fio, const std::string& group, const std::string& specialty,
                 int course, double avg)
    : Base('S'), fio_(fio), group_(group), specialty_(specialty), course_(course), average_(avg) 
{
    std::cout << "[Student] Вызван конструктор с параметрами\n";
    // Валидация введенных данных через сеттеры
    setCourse(course_);
    setAverage(average_);
}

// копирования - создает копию объекта other
Student::Student(const Student& other)
    : Base(other), fio_(other.fio_), group_(other.group_), specialty_(other.specialty_),
      course_(other.course_), average_(other.average_)
{
    std::cout << "[Student] Вызван конструктор копирования\n";
}

// Деструктор - вызывается при уничтожении объекта
Student::~Student() {
    std::cout << "[Student] Вызван деструктор для " << fio_ << "\n";
}

// Установка курса с проверкой валидности
void Student::setCourse(int c) {
    if (c <= 0) throw DemoException("Курс должен быть положительным");
    course_ = c;
}

// Установка среднего балла с проверкой валидности
void Student::setAverage(double a) {
    if (a < 0.0 || a > 10.0) throw DemoException("Средний балл вне допустимого диапазона (0..10)");
    average_ = a;
}

// Ввод данных студента с клавиатуры
void Student::input() {
    // Очистка буфера ввода перед чтением строк
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "ФИО студента: ";
    std::getline(std::cin, fio_);
    
    std::cout << "Группа: ";
    std::getline(std::cin, group_);
    
    std::cout << "Специальность: ";
    std::getline(std::cin, specialty_);
    
    std::cout << "Курс (целое): ";
    std::cin >> course_;
    setCourse(course_);  // Валидация курса
    
    std::cout << "Средний балл (0..10): ";
    std::cin >> average_;
    setAverage(average_);  // Валидация среднего балла
}

// Вывод информации о студенте в поток вывода
void Student::display(std::ostream& os) const {
    os << "[Student] ФИО: " << fio_ << ", Группа: " << group_
       << ", Специальность: " << specialty_ << ", Курс: " << course_
       << ", Ср.балл: " << average_ << '\n';
}

// Сохранение данных студента в файл
void Student::save(std::ostream& out) const {
    out << type() << '\n';        // Тип объекта ('S')
    out << fio_ << '\n';          // ФИО
    out << group_ << '\n';        // Группа
    out << specialty_ << '\n';    // Специальность
    out << course_ << '\n';       // Курс
    out << average_ << '\n';      // Средний балл
}

// Загрузка данных студента из файла
void Student::load(std::istream& in) {
    std::string tmp;
    std::getline(in >> std::ws, fio_);  // Чтение ФИО с пропуском начальных пробелов
    std::getline(in, group_);           // Чтение группы
    std::getline(in, specialty_);       // Чтение специальности
    in >> course_;                      // Чтение курса
    in >> average_;                     // Чтение среднего балла
    
    // Валидация загруженных данных
    setCourse(course_);
    setAverage(average_);
}

// Оператор присваивания - копирование данных из другого объекта Student
Student& Student::operator=(const Student& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        Base::operator=(other);  // Вызов оператора присваивания базового класса
        fio_ = other.fio_;
        group_ = other.group_;
        specialty_ = other.specialty_;
        course_ = other.course_;
        average_ = other.average_;
    }
    return *this;  // Возврат ссылки на текущий объект
}