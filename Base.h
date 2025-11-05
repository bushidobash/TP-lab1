#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <string>

class Base {
public:
    explicit Base(char type = '?') : type_{type} {}
    Base(const Base& other) : type_{other.type_} {}
    virtual ~Base() = default;

    char type() const noexcept { return type_; }

    // Интерфейс, реализуемый в наследниках
    virtual void input() = 0;
    virtual void display(std::ostream& os = std::cout) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

    virtual Base* clone() const = 0; // для возможности копирования при необходимости

    Base& operator=(const Base& other) {
        if (this != &other) {
            type_ = other.type_;
        }
        return *this;
    }

protected:
    char type_{'?'};
};

inline std::ostream& operator<<(std::ostream& os, const Base& b) {
    b.display(os);
    return os;
}

#endif // BASE_H