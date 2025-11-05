#ifndef DEMO_EXCEPTION_H
#define DEMO_EXCEPTION_H

#include <stdexcept>
#include <string>

class DemoException : public std::runtime_error {
public:
    explicit DemoException(const std::string& msg) : std::runtime_error(msg) {}
};

class DemoExceptionBadIndex : public DemoException {
public:
    DemoExceptionBadIndex() : DemoException("Неверный индекс объекта") {}
};

#endif // DEMO_EXCEPTION_H