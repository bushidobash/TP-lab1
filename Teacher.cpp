#include "Teacher.h"
#include <iostream>
#include <limits>

Teacher::Teacher() : Base('T') {
    std::cout << "[Teacher] Вызван конструктор по умолчанию\n";
}

Teacher::Teacher(const std::string& fio, const std::string& groupsCommaSeparated, const std::string& subjectsCommaSeparated)
    : Base('T'), fio_(fio), groups_(groupsCommaSeparated), subjects_(subjectsCommaSeparated)
{
    std::cout << "[Teacher] Вызван конструктор с параметрами\n";
}

Teacher::Teacher(const Teacher& other)
    : Base(other), fio_(other.fio_), groups_(other.groups_), subjects_(other.subjects_)
{
    std::cout << "[Teacher] Вызван конструктор копирования\n";
}

Teacher::~Teacher() {
    std::cout << "[Teacher] Вызван деструктор для " << fio_ << "\n";
}

void Teacher::input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "ФИО преподавателя: ";
    std::getline(std::cin, fio_);
    std::cout << "Перечислите группы через запятую: ";
    std::getline(std::cin, groups_);
    std::cout << "Перечислите предметы через запятую: ";
    std::getline(std::cin, subjects_);
}

void Teacher::display(std::ostream& os) const {
    os << "[Teacher] ФИО: " << fio_ << ", Группы: " << groups_
       << ", Предметы: " << subjects_ << '\n';
}

void Teacher::save(std::ostream& out) const {
    out << type() << '\n';
    out << fio_ << '\n';
    out << groups_ << '\n';
    out << subjects_ << '\n';
}

void Teacher::load(std::istream& in) {
    std::getline(in >> std::ws, fio_);
    std::getline(in, groups_);
    std::getline(in, subjects_);
}

Teacher& Teacher::operator=(const Teacher& other) {
    if (this != &other) {
        Base::operator=(other);
        fio_ = other.fio_;
        groups_ = other.groups_;
        subjects_ = other.subjects_;
    }
    return *this;
}