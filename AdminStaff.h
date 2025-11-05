#ifndef ADMINSTAFF_H
#define ADMINSTAFF_H

#include "Base.h"
#include "DemoException.h"
#include <string>

class AdminStaff : public Base {
public:
    AdminStaff();
    AdminStaff(const std::string& fio, const std::string& position, const std::string& phone, const std::string& responsibility);
    AdminStaff(const AdminStaff& other);
    ~AdminStaff() override;

    void input() override;
    void display(std::ostream& os = std::cout) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    Base* clone() const override { return new AdminStaff(*this); }

    // сеттеры/геттеры
    void setFio(const std::string& f) { fio_ = f; }
    void setPosition(const std::string& p) { position_ = p; }
    void setPhone(const std::string& ph) { phone_ = ph; }
    void setResponsibility(const std::string& r) { responsibility_ = r; }

    const std::string& fio() const { return fio_; }
    const std::string& position() const { return position_; }
    const std::string& phone() const { return phone_; }
    const std::string& responsibility() const { return responsibility_; }

    AdminStaff& operator=(const AdminStaff& other);

private:
    std::string fio_;
    std::string position_;
    std::string phone_;
    std::string responsibility_;
};

#endif // ADMINSTAFF_H