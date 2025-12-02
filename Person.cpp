#include "Person.h"
#include <iostream>

Person::Person() : fio("") {
    std::cout << "[Person] Конструктор по умолчанию вызван.\n";
}

Person::Person(const std::string& fio_) : fio(fio_) {
    std::cout << "[Person] Конструктор с параметром вызван для: " << fio << "\n";
}

Person::Person(const Person& other) : fio(other.fio) {
    std::cout << "[Person] Конструктор копирования вызван для: " << fio << "\n";
}

Person::~Person() {
    std::cout << "[Person] Деструктор вызван для: " << fio << "\n";
}

void Person::setFIO(const std::string& fio_) { fio = fio_; }
std::string Person::getFIO() const { return fio; }

void Person::printInfo(std::ostream& os) const {
    os << fio;
}