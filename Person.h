#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person {
protected:
    std::string fio; // фамилия и инициалы (храним в одной строке)
public:
    Person();
    Person(const std::string& fio_);
    Person(const Person& other);
    virtual ~Person();

    void setFIO(const std::string& fio_);
    std::string getFIO() const;

    virtual void printInfo(std::ostream& os) const;
};

#endif // PERSON_H