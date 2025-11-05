#include "Student.h"
#include <iostream>
#include <limits>

Student::Student() : Base('S') {
    std::cout << "[Student] Вызван конструктор по умолчанию\n";
}

Student::Student(const std::string& fio, const std::string& group, const std::string& specialty,
                 int course, double avg)
    : Base('S'), fio_(fio), group_(group), specialty_(specialty), course_(course), average_(avg) 
{
    std::cout << "[Student] Вызван конструктор с параметрами\n";
    setCourse(course_);
    setAverage(average_);
}

Student::Student(const Student& other)
    : Base(other), fio_(other.fio_), group_(other.group_), specialty_(other.specialty_),
      course_(other.course_), average_(other.average_)
{
    std::cout << "[Student] Вызван конструктор копирования\n";
}

Student::~Student() {
    std::cout << "[Student] Вызван деструктор для " << fio_ << "\n";
}

void Student::setCourse(int c) {
    if (c <= 0) throw DemoException("Курс должен быть положительным");
    course_ = c;
}

void Student::setAverage(double a) {
    if (a < 0.0 || a > 10.0) throw DemoException("Средний балл вне допустимого диапазона (0..10)");
    average_ = a;
}

void Student::input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "ФИО студента: ";
    std::getline(std::cin, fio_);
    std::cout << "Группа: ";
    std::getline(std::cin, group_);
    std::cout << "Специальность: ";
    std::getline(std::cin, specialty_);
    std::cout << "Курс (целое): ";
    std::cin >> course_;
    setCourse(course_);
    std::cout << "Средний балл (0..10): ";
    std::cin >> average_;
    setAverage(average_);
}

void Student::display(std::ostream& os) const {
    os << "[Student] ФИО: " << fio_ << ", Группа: " << group_
       << ", Специальность: " << specialty_ << ", Курс: " << course_
       << ", Ср.балл: " << average_ << '\n';
}

void Student::save(std::ostream& out) const {
    out << type() << '\n';
    out << fio_ << '\n';
    out << group_ << '\n';
    out << specialty_ << '\n';
    out << course_ << '\n';
    out << average_ << '\n';
}

void Student::load(std::istream& in) {
    std::string tmp;
    std::getline(in >> std::ws, fio_);
    std::getline(in, group_);
    std::getline(in, specialty_);
    in >> course_;
    in >> average_;
    setCourse(course_);
    setAverage(average_);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        Base::operator=(other);
        fio_ = other.fio_;
        group_ = other.group_;
        specialty_ = other.specialty_;
        course_ = other.course_;
        average_ = other.average_;
    }
    return *this;
}