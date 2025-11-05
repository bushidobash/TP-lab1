#ifndef TEACHER_H
#define TEACHER_H

#include "Base.h"
#include "DemoException.h"
#include <string>

class Teacher : public Base {
public:
    Teacher();
    Teacher(const std::string& fio, const std::string& groupsCommaSeparated, const std::string& subjectsCommaSeparated);
    Teacher(const Teacher& other);
    ~Teacher() override;

    void input() override;
    void display(std::ostream& os = std::cout) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    Base* clone() const override { return new Teacher(*this); }

    // сеттеры/геттеры
    void setFio(const std::string& f) { fio_ = f; }
    void setGroups(const std::string& g) { groups_ = g; }
    void setSubjects(const std::string& s) { subjects_ = s; }

    const std::string& fio() const { return fio_; }
    const std::string& groups() const { return groups_; }
    const std::string& subjects() const { return subjects_; }

    Teacher& operator=(const Teacher& other);

private:
    // ƒл€ простоты Ч хранение групп и предметов как строки через зап€тую.
    std::string fio_;
    std::string groups_;
    std::string subjects_;
};

#endif // TEACHER_H