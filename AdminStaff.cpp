#include "AdminStaff.h"
#include <iostream>
#include <limits>

AdminStaff::AdminStaff() : Base('A') {
    std::cout << "[AdminStaff] Вызван конструктор по умолчанию\n";
}

AdminStaff::AdminStaff(const std::string& fio, const std::string& position, const std::string& phone, const std::string& responsibility)
    : Base('A'), fio_(fio), position_(position), phone_(phone), responsibility_(responsibility)
{
    std::cout << "[AdminStaff] Вызван конструктор с параметрами\n";
}

AdminStaff::AdminStaff(const AdminStaff& other)
    : Base(other), fio_(other.fio_), position_(other.position_), phone_(other.phone_), responsibility_(other.responsibility_)
{
    std::cout << "[AdminStaff] Вызван конструктор копирования\n";
}

AdminStaff::~AdminStaff() {
    std::cout << "[AdminStaff] Вызван деструктор для " << fio_ << "\n";
}

void AdminStaff::input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "ФИО сотрудника: ";
    std::getline(std::cin, fio_);
    std::cout << "Должность: ";
    std::getline(std::cin, position_);
    std::cout << "Телефон: ";
    std::getline(std::cin, phone_);
    std::cout << "Область ответственности: ";
    std::getline(std::cin, responsibility_);
}

void AdminStaff::display(std::ostream& os) const {
    os << "[Admin] ФИО: " << fio_ << ", Должность: " << position_
       << ", Телефон: " << phone_ << ", Ответственность: " << responsibility_ << '\n';
}

void AdminStaff::save(std::ostream& out) const {
    out << type() << '\n';
    out << fio_ << '\n';
    out << position_ << '\n';
    out << phone_ << '\n';
    out << responsibility_ << '\n';
}

void AdminStaff::load(std::istream& in) {
    std::getline(in >> std::ws, fio_);
    std::getline(in, position_);
    std::getline(in, phone_);
    std::getline(in, responsibility_);
}

AdminStaff& AdminStaff::operator=(const AdminStaff& other) {
    if (this != &other) {
        Base::operator=(other);
        fio_ = other.fio_;
        position_ = other.position_;
        phone_ = other.phone_;
        responsibility_ = other.responsibility_;
    }
    return *this;
}