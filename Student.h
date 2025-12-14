#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"
#include "DemoException.h"
#include <string>

/*Класс Student представляет студента и наследует базовый класс Base. Содержит основные данные о студенте и методы для работы с ними.*/
class Student : public Base {
public:
    Student(); //конструктор по умол.
    Student(const std::string& fio, const std::string& group, const std::string& specialty,
            int course, double avg); //конструктор с параметрами
    Student(const Student& other); //конструктор копирования
    ~Student() override; //деструктор

    // Основные методы для ввода, вывода, сохранения и загрузки данных
    void input() override; // Ввод данных с клавиатуры
    void display(std::ostream& os = std::cout) const override; // Вывод данных
    void save(std::ostream& out) const override; // Сохранение в поток
    void load(std::istream& in) override; // Загрузка из потока

    // Создание копии объекта (паттерн "Прототип")
    Base* clone() const override { return new Student(*this); }

    // сеттеры с проверкой входных данных
    void setFio(const std::string& f) { fio_ = f; }
    void setGroup(const std::string& g) { group_ = g; }
    void setSpecialty(const std::string& s) { specialty_ = s; }
    void setCourse(int c); // Проверяет корректность курса
    void setAverage(double a); // Проверяет корректность средней оценки

    //геттеры для доступа к данным
    const std::string& fio() const { return fio_; }
    const std::string& group() const { return group_; }
    const std::string& specialty() const { return specialty_; }
    int course() const { return course_; }
    double average() const { return average_; }
    
    // Оператор присваивания
    Student& operator=(const Student& other);

private:
    // Поля класса
    std::string fio_;
    std::string group_;
    std::string specialty_;
    int course_{1};
    double average_{0.0};
};

#endif // STUDENT_H