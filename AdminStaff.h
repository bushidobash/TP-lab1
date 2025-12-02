#ifndef ADMINSTAFF_H
#define ADMINSTAFF_H

#include "Base.h"
#include "DemoException.h"
#include <string>

// Класс административного сотрудника, наследуется от базового класса Base
class AdminStaff : public Base {
public:
    // Конструкторы
    AdminStaff(); // Конструктор по умолчанию
    AdminStaff(const std::string& fio, const std::string& position, 
               const std::string& phone, const std::string& responsibility); // Параметризованный конструктор
    AdminStaff(const AdminStaff& other); // Конструктор копирования
    ~AdminStaff() override; // Виртуальный деструктор

    // Переопределенные методы базового класса
    void input() override; // Ввод данных с консоли
    void display(std::ostream& os = std::cout) const override; // Вывод данных в поток
    void save(std::ostream& out) const override; // Сохранение в поток
    void load(std::istream& in) override; // Загрузка из потока

    // Фабричный метод для создания копии объекта
    Base* clone() const override { return new AdminStaff(*this); }

    // Сеттеры (установка значений)
    void setFio(const std::string& f) { fio_ = f; }
    void setPosition(const std::string& p) { position_ = p; }
    void setPhone(const std::string& ph) { phone_ = ph; }
    void setResponsibility(const std::string& r) { responsibility_ = r; }

    // Геттеры (получение значений)
    const std::string& fio() const { return fio_; }
    const std::string& position() const { return position_; }
    const std::string& phone() const { return phone_; }
    const std::string& responsibility() const { return responsibility_; }

    // Оператор присваивания
    AdminStaff& operator=(const AdminStaff& other);

private:
    // Приватные поля класса
    std::string fio_; // ФИО сотрудника
    std::string position_; // Должность
    std::string phone_; // Телефон
    std::string responsibility_; // Обязанности
};

#endif // ADMINSTAFF_H