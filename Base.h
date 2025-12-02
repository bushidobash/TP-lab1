#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <fstream>
#include <string>

/* абстрактный базовый класс для всех объектов в системе, определяет общий интерфейс для ввода/вывода и сериализации */
class Base {
public:
    // Конструкторы
    explicit Base(char type = '?') : type_{type} {} // явный конструктор с параметром типа
    Base(const Base& other) : type_{other.type_} {} // конструктор копирования
    
    // виртуальный деструктор для корректного удаления объектов-наследников
    virtual ~Base() = default;

    // получение типа объекта (доступен без выбрасывания исключений)
    char type() const noexcept { return type_; }

    // ======== ЧИСТО ВИРТУАЛЬНЫЕ МЕТОДЫ (интерфейс) ========
    virtual void input() = 0;                       // ввод данных с консоли
    virtual void display(std::ostream& os = std::cout) const = 0; // вывод в поток
    virtual void save(std::ostream& out) const = 0; // сериализация в поток
    virtual void load(std::istream& in) = 0;        // десериализация из потока

    // виртуальный метод для создания копии объекта
    virtual Base* clone() const = 0;

    // оператор присваивания с защитой от самоприсваивания
    Base& operator=(const Base& other) {
        if (this != &other) {  // проверка на самоприсваивание
            type_ = other.type_;
        }
        return *this;
    }

protected:
    char type_{'?'};  // символьный идентификатор типа объекта
};

// перегрузка оператора вывода для вывода любого объекта Base через display()
inline std::ostream& operator<<(std::ostream& os, const Base& b) {
    b.display(os);  // вызываем виртуальный метод display()
    return os;
}

#endif