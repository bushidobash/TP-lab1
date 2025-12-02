#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"
#include "DemoException.h"
#include <string>

// Класс Teacher, наследуемый от абстрактного базового класса Base
class Teacher : public Base {
public:
    // Конструкторы
    Teacher();  // Конструктор по умолчанию
    Teacher(const std::string& fio, const std::string& groupsCommaSeparated, const std::string& subjectsCommaSeparated);  // Конструктор с параметрами
    Teacher(const Teacher& other);  // Конструктор копирования
    ~Teacher() override;  // Виртуальный деструктор

    // Переопределение виртуальных методов базового класса
    void input() override;  // Ввод данных с клавиатуры
    void display(std::ostream& os = std::cout) const override;  // Вывод в поток
    void save(std::ostream& out) const override;  // Сохранение в файл
    void load(std::istream& in) override;  // Загрузка из файла

    // Метод для создания копии объекта
    Base* clone() const override { return new Teacher(*this); }

    // Сеттеры (методы установки значений)
    void setFio(const std::string& f) { fio_ = f; }
    void setGroups(const std::string& g) { groups_ = g; }
    void setSubjects(const std::string& s) { subjects_ = s; }

    // Геттеры (методы получения значений)
    const std::string& fio() const { return fio_; }
    const std::string& groups() const { return groups_; }
    const std::string& subjects() const { return subjects_; }

    // Оператор присваивания
    Teacher& operator=(const Teacher& other);

private:
    // Приватные поля класса
    
    // ФИО
    std::string fio_;
    
    // Список групп, которые ведет (строки с разделителем-запятой)
    std::string groups_;
    
    // Список предметов, которые ведет (строки с разделителем-запятой)
    std::string subjects_;
};

#endif