#ifndef STUDENT_H
#define STUDENT_H

#include "Base.h"
#include "DemoException.h"
#include <string>

class Student : public Base {
public:
    Student();
    Student(const std::string& fio, const std::string& group, const std::string& specialty,
            int course, double avg);
    Student(const Student& other);
    ~Student() override;

    void input() override;
    void display(std::ostream& os = std::cout) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    // clone
    Base* clone() const override { return new Student(*this); }

    // сеттеры/геттеры
    void setFio(const std::string& f) { fio_ = f; }
    void setGroup(const std::string& g) { group_ = g; }
    void setSpecialty(const std::string& s) { specialty_ = s; }
    void setCourse(int c);
    void setAverage(double a);

    const std::string& fio() const { return fio_; }
    const std::string& group() const { return group_; }
    const std::string& specialty() const { return specialty_; }
    int course() const { return course_; }
    double average() const { return average_; }

    Student& operator=(const Student& other);

private:
    std::string fio_;
    std::string group_;
    std::string specialty_;
    int course_{1};
    double average_{0.0};
};

#endif // STUDENT_H