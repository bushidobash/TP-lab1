#ifndef GROUP_H
#define GROUP_H

#include "Student.h"
#include <string>

class Group {
private:
    int groupNumber;
    std::string* subjects; // массив предметов
    int subjectCount;

    Student** students; // динамический массив указателей на Student
    int studentCount;

public:
    Group();
    Group(int groupNumber_, int subjectCount_, const std::string* subjectsArr);
    Group(const Group& other);
    ~Group();

    // set/get
    void setGroupNumber(int num);
    int getGroupNumber() const;

    void setSubjects(int n, const std::string* arr);
    void getSubjects(int& n, std::string*& arr) const;

    int getStudentCount() const;

    double getGroupAverage() const;

    // управление студентами
    void addStudentAt(int pos, Student* s); // вставка (pos: 0..studentCount)
    void appendStudent(Student* s); // добавить в конец
    Student* removeStudentAt(int pos); // удаление и возвращение указателя (caller должен удалить)
    Student* getStudentAt(int pos) const;
    void editStudentAt(int pos); // интерактивное редактирование в консоли

    // вывод
    void printBrief(std::ostream& os) const; // краткий вывод (номер группы и кол-во студентов)
    void printFull(std::ostream& os) const;

    // вспомогательное
    void listStudentsWithAvgGreater(double threshold, std::ostream& os) const;
};

#endif // GROUP_H