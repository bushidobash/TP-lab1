#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include <string>
#include <cstddef>

class Keeper {
public:
    Keeper();
    ~Keeper();

    // запретим копирование по умолчанию (можно реализовать при необходимости)
    Keeper(const Keeper&) = delete;
    Keeper& operator=(const Keeper&) = delete;

    void addObject();               // добавить объект (выбор типа внутри)
    void removeObject(std::size_t index); // удалить по индексу
    void viewAll() const;           // вывести все
    void editObject(std::size_t index);   // редактировать по индексу

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    std::size_t size() const noexcept { return size_; }

private:
    void ensureCapacity();
    Base* createFromChar(char t) const;

    Base** items_;      // динамический массив указателей на Base
    std::size_t size_;  // текущее количество
    std::size_t cap_;   // ёмкость
    static const std::size_t INITIAL_CAP = 4;
};

#endif // KEEPER_H