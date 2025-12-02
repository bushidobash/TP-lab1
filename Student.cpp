#include "Student.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>

Student::Student() : Person(), grades(nullptr), gradeCount(0) {
    std::cout << "[Student] Конструктор по умолчанию вызван.\n";
}

Student::Student(const std::string& fio_, int gradeCount_, const double* gradesArray)
    : Person(fio_), grades(nullptr), gradeCount(0)
{
    std::cout << "[Student] Конструктор с параметрами вызван для: " << fio << "\n";
    if (gradeCount_ > 0) {
        grades = new double[gradeCount_];
        gradeCount = gradeCount_;
        for (int i = 0; i < gradeCount; ++i) grades[i] = gradesArray[i];
    }
}

Student::Student(const Student& other) : Person(other), grades(nullptr), gradeCount(0) {
    std::cout << "[Student] Конструктор копирования вызван для: " << fio << "\n";
    if (other.gradeCount > 0) {
        grades = new double[other.gradeCount];
        gradeCount = other.gradeCount;
        for (int i = 0; i < gradeCount; ++i) grades[i] = other.grades[i];
    }
}

Student::~Student() {
    std::cout << "[Student] Деструктор вызван для: " << fio << "\n";
    delete[] grades;
}

// set/get
void Student::setGrades(int n, const double* arr) {
    delete[] grades;
    grades = nullptr;
    gradeCount = 0;
    if (n > 0) {
        grades = new double[n];
        for (int i = 0; i < n; ++i) grades[i] = arr[i];
        gradeCount = n;
    }
}

void Student::getGrades(int& n, double*& outArr) const {
    if (gradeCount == 0) {
        n = 0;
        outArr = nullptr;
        return;
    }
    outArr = new double[gradeCount];
    for (int i = 0; i < gradeCount; ++i) outArr[i] = grades[i];
    n = gradeCount;
}

int Student::getGradeCount() const { return gradeCount; }

double Student::getAverage() const {
    if (gradeCount == 0) return 0.0;
    double sum = 0;
    for (int i = 0; i < gradeCount; ++i) sum += grades[i];
    return sum / gradeCount;
}

void Student::setGradeAt(int idx, double value) {
    if (idx < 0 || idx >= gradeCount) throw std::out_of_range("Неверный индекс оценки.");
    grades[idx] = value;
}

double Student::getGradeAt(int idx) const {
    if (idx < 0 || idx >= gradeCount) throw std::out_of_range("Неверный индекс оценки.");
    return grades[idx];
}

void Student::printInfo(std::ostream& os) const {
    os << fio << " (avg=" << std::fixed << std::setprecision(2) << getAverage() << ")";
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << s.getFIO() << " | оценки:";
    if (s.gradeCount == 0) {
        os << " нет";
    } else {
        for (int i = 0; i < s.gradeCount; ++i) {
            os << " " << s.grades[i];
        }
    }
    os << " | ср=" << std::fixed << std::setprecision(2) << s.getAverage();
    return os;
}

std::istream& operator>>(std::istream& is, Student& s) {
    std::string fio;
    std::cout << "Введите фамилию и инициалы: ";
    std::getline(is >> std::ws, fio);
    s.setFIO(fio);

    int n;
    std::cout << "Сколько оценок вводите? ";
    while (!(is >> n) || n < 0) {
        std::cout << "Ошибка: введите неотрицательное целое. Попробуйте снова: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    delete[] s.grades;
    s.grades = nullptr;
    s.gradeCount = 0;
    if (n > 0) {
        s.grades = new double[n];
        s.gradeCount = n;
        for (int i = 0; i < n; ++i) {
            std::cout << "Оценка #" << (i+1) << ": ";
            while (!(is >> s.grades[i])) {
                std::cout << "Ошибка: введите число. Попробуйте снова: ";
                is.clear();
                is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return is;
}