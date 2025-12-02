#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <iostream>

class Student : public Person {
private:
    double* grades;    // динамический массив оценок
    int gradeCount;
public:
    Student(); // по умолчанию
    Student(const std::string& fio_, int gradeCount_, const double* gradesArray);
    Student(const Student& other);
    ~Student();

    // set/get
    void setGrades(int n, const double* arr);
    void getGrades(int& n, double*& outArr) const; // копирует данные в outArr (который выделен вызывающим) - но будем возвращать через new
    int getGradeCount() const;
    double getAverage() const;

    // edit single grade
    void setGradeAt(int idx, double value);
    double getGradeAt(int idx) const;

    // переопределение печати
    virtual void printInfo(std::ostream& os) const override;

    // операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

#endif // STUDENT_H