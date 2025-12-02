#include "Group.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>

Group::Group() : groupNumber(0), subjects(nullptr), subjectCount(0), students(nullptr), studentCount(0) {
    std::cout << "[Group] Конструктор по умолчанию вызван.\n";
}

Group::Group(int groupNumber_, int subjectCount_, const std::string* subjectsArr)
    : groupNumber(groupNumber_), subjects(nullptr), subjectCount(0), students(nullptr), studentCount(0)
{
    std::cout << "[Group] Конструктор с параметрами вызван для группы " << groupNumber << "\n";
    if (subjectCount_ > 0) {
        subjects = new std::string[subjectCount_];
        for (int i = 0; i < subjectCount_; ++i) subjects[i] = subjectsArr[i];
        subjectCount = subjectCount_;
    }
}

Group::Group(const Group& other)
    : groupNumber(other.groupNumber), subjects(nullptr), subjectCount(0), students(nullptr), studentCount(0)
{
    std::cout << "[Group] Конструктор копирования вызван для группы " << groupNumber << "\n";
    if (other.subjectCount > 0) {
        subjects = new std::string[other.subjectCount];
        subjectCount = other.subjectCount;
        for (int i = 0; i < subjectCount; ++i) subjects[i] = other.subjects[i];
    }
    if (other.studentCount > 0) {
        students = new Student*[other.studentCount];
        studentCount = other.studentCount;
        for (int i = 0; i < studentCount; ++i) {
            students[i] = new Student(*other.students[i]); // копирование студентов
        }
    }
}

Group::~Group() {
    std::cout << "[Group] Деструктор вызван для группы " << groupNumber << "\n";
    for (int i = 0; i < studentCount; ++i) delete students[i];
    delete[] students;
    delete[] subjects;
}

void Group::setGroupNumber(int num) { groupNumber = num; }
int Group::getGroupNumber() const { return groupNumber; }

void Group::setSubjects(int n, const std::string* arr) {
    delete[] subjects;
    subjects = nullptr;
    subjectCount = 0;
    if (n > 0) {
        subjects = new std::string[n];
        for (int i = 0; i < n; ++i) subjects[i] = arr[i];
        subjectCount = n;
    }
}

void Group::getSubjects(int& n, std::string*& arr) const {
    if (subjectCount == 0) { n = 0; arr = nullptr; return; }
    arr = new std::string[subjectCount];
    for (int i = 0; i < subjectCount; ++i) arr[i] = subjects[i];
    n = subjectCount;
}

int Group::getStudentCount() const { return studentCount; }

double Group::getGroupAverage() const {
    if (studentCount == 0) return 0.0;
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < studentCount; ++i) {
        sum += students[i]->getAverage();
        ++cnt;
    }
    return cnt == 0 ? 0.0 : sum / cnt;
}

void Group::addStudentAt(int pos, Student* s) {
    if (pos < 0 || pos > studentCount) throw std::out_of_range("Неверная позиция вставки студента.");
    Student** newArr = new Student*[studentCount + 1];
    for (int i = 0; i < pos; ++i) newArr[i] = students[i];
    newArr[pos] = s;
    for (int i = pos; i < studentCount; ++i) newArr[i+1] = students[i];
    delete[] students;
    students = newArr;
    ++studentCount;
}

void Group::appendStudent(Student* s) {
    addStudentAt(studentCount, s);
}

Student* Group::removeStudentAt(int pos) {
    if (pos < 0 || pos >= studentCount) throw std::out_of_range("Неверная позиция удаления студента.");
    Student* removed = students[pos];
    if (studentCount == 1) {
        delete[] students;
        students = nullptr;
        studentCount = 0;
        return removed;
    }
    Student** newArr = new Student*[studentCount - 1];
    for (int i = 0; i < pos; ++i) newArr[i] = students[i];
    for (int i = pos+1; i < studentCount; ++i) newArr[i-1] = students[i];
    delete[] students;
    students = newArr;
    --studentCount;
    return removed;
}

Student* Group::getStudentAt(int pos) const {
    if (pos < 0 || pos >= studentCount) throw std::out_of_range("Неверная позиция доступа к студенту.");
    return students[pos];
}

void Group::editStudentAt(int pos) {if (pos < 0 || pos >= studentCount) throw std::out_of_range("Неверная позиция для редактирования студента.");
    Student* s = students[pos];
    std::cout << "Редактирование студента #" << pos << " (текущее: " << s->getFIO() << ")\n";
    std::cout << "1) Изменить ФИО\n2) Изменить оценки\n3) Изменить отдельную оценку\n0) Выход\nВыберите действие: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (choice == 1) {
        std::string newfio;
        std::cout << "Новое ФИО: ";
        std::getline(std::cin, newfio);
        s->setFIO(newfio);
    } else if (choice == 2) {
        int n;
        std::cout << "Сколько оценок: ";
        while (!(std::cin >> n) || n < 0) {
            std::cout << "Введите неотрицательное целое: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        double* arr = nullptr;
        if (n > 0) {
            arr = new double[n];
            for (int i = 0; i < n; ++i) {
                std::cout << "Оценка #" << i+1 << ": ";
                while (!(std::cin >> arr[i])) {
                    std::cout << "Ошибка ввода. Попробуйте снова: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        s->setGrades(n, arr);
        delete[] arr;
    } else if (choice == 3) {
        int idx;
        double val;
        std::cout << "Индекс оценки (1.." << s->getGradeCount() << "): ";
        while (!(std::cin >> idx) || idx < 1 || idx > s->getGradeCount()) {
            std::cout << "Неверный индекс. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Новое значение: ";
        while (!(std::cin >> val)) {
            std::cout << "Ошибка ввода. Попробуйте снова: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        s->setGradeAt(idx-1, val);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        std::cout << "Выход из редактирования.\n";
    }
}

void Group::printBrief(std::ostream& os) const {
    os << "Группа " << groupNumber << " | студентов: " << studentCount << " | ср=" << std::fixed << std::setprecision(2) << getGroupAverage() << "\n";
}

void Group::printFull(std::ostream& os) const {
    os << "Группа " << groupNumber << ":\n";
    if (subjectCount > 0) {
        os << "  Предметы: ";
        for (int i = 0; i < subjectCount; ++i) os << subjects[i] << (i+1<subjectCount? ", ":"");
        os << "\n";
    }
    os << "  Студенты (" << studentCount << "):\n";
    for (int i = 0; i < studentCount; ++i) {
        os << "   [" << i << "] " << *students[i] << "\n";
    }
}

void Group::listStudentsWithAvgGreater(double threshold, std::ostream& os) const {
    bool any = false;
    for (int i = 0; i < studentCount; ++i) {
        if (students[i]->getAverage() > threshold) {
            os << students[i]->getFIO() << " | группа " << groupNumber << " | ср=" << students[i]->getAverage() << "\n";
            any = true;
        }
    }
    if (!any) os << "В группе " << groupNumber << " нет студентов со средним баллом > " << threshold << "\n";
}