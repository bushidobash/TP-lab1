#include "GroupManager.h"
#include <iostream>
#include <limits>
#include <stdexcept>

GroupManager::GroupManager() : groups(nullptr), groupCount(0) {
    std::cout << "[GroupManager] Создан менеджер групп.\n";
}

GroupManager::~GroupManager() {
    std::cout << "[GroupManager] Деструктор менеджера групп.\n";
    for (int i = 0; i < groupCount; ++i) delete groups[i];
    delete[] groups;
}

int GroupManager::getGroupCount() const { return groupCount; }

Group* GroupManager::getGroupAt(int idx) const {
    if (idx < 0 || idx >= groupCount) throw std::out_of_range("Неверный индекс группы.");
    return groups[idx];
}

void GroupManager::addGroupAt(int pos, Group* g) {
    if (pos < 0 || pos > groupCount) throw std::out_of_range("Неверная позиция вставки группы.");
    Group** newArr = new Group*[groupCount + 1];
    for (int i = 0; i < pos; ++i) newArr[i] = groups[i];
    newArr[pos] = g;
    for (int i = pos; i < groupCount; ++i) newArr[i+1] = groups[i];
    delete[] groups;
    groups = newArr;
    ++groupCount;
}

Group* GroupManager::removeGroupAt(int pos) {
    if (pos < 0 || pos >= groupCount) throw std::out_of_range("Неверная позиция удаления группы.");
    Group* removed = groups[pos];
    if (groupCount == 1) {
        delete[] groups;
        groups = nullptr;
        groupCount = 0;
        return removed;
    }
    Group** newArr = new Group*[groupCount - 1];
    for (int i = 0; i < pos; ++i) newArr[i] = groups[i];
    for (int i = pos+1; i < groupCount; ++i) newArr[i-1] = groups[i];
    delete[] groups;
    groups = newArr;
    --groupCount;
    return removed;
}

void GroupManager::appendGroup(Group* g) {
    addGroupAt(groupCount, g);
}

void GroupManager::sortByGroupNumber() {
    // простой пузырёк - нет STL
    for (int i = 0; i < groupCount - 1; ++i) {
        for (int j = 0; j < groupCount - 1 - i; ++j) {
            if (groups[j]->getGroupNumber() > groups[j+1]->getGroupNumber()) {
                Group* tmp = groups[j];
                groups[j] = groups[j+1];
                groups[j+1] = tmp;
            }
        }
    }
}

void GroupManager::inputNewGroupInteractive() {
    int num;
    std::cout << "Введите номер группы: ";
    while (!(std::cin >> num)) {
        std::cout << "Ошибка. Попробуйте снова: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int subCount;
    std::cout << "Сколько предметов у группы? ";
    while (!(std::cin >> subCount) || subCount < 0) {
        std::cout << "Ошибка. Введите неотрицательное целое: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string* subs = nullptr;
    if (subCount > 0) {
        subs = new std::string[subCount];
        for (int i = 0; i < subCount; ++i) {
            std::cout << "Название предмета #" << (i+1) << ": ";
            std::getline(std::cin, subs[i]);
        }
    }
    Group* g = new Group(num, subCount, subs);
    delete[] subs;

    // добавить студентов по желанию
    std::cout << "Добавить студентов сейчас? (1-да / 0-нет): ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (choice == 1) {
        Student* s = new Student();
        std::cin >> *s; // использует operator>>
        g->appendStudent(s);
        std::cout << "Добавить ещё студента? (1-да / 0-нет): ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    appendGroup(g);
    // упорядочить по возрастанию номера группы
    sortByGroupNumber();
}

void GroupManager::printAllBrief() const {
    if (groupCount == 0) {
        std::cout << "Групп нет.\n";
        return;
    }
    for (int i = 0; i < groupCount; ++i) {
        std::cout << "[" << i << "] ";
        groups[i]->printBrief(std::cout);
    }
}

void GroupManager::printAllFull() const {if (groupCount == 0) {
        std::cout << "Групп нет.\n";
        return;
    }
    for (int i = 0; i < groupCount; ++i) {
        std::cout << "=== Группа индекс " << i << " ===\n";
        groups[i]->printFull(std::cout);
    }
}

void GroupManager::listAllStudentsWithAvgGreater(double threshold) const {
    bool any = false;
    for (int i = 0; i < groupCount; ++i) {
        for (int j = 0; j < groups[i]->getStudentCount(); ++j) {
            Student* s = groups[i]->getStudentAt(j);
            if (s->getAverage() > threshold) {
                std::cout << s->getFIO() << " | группа " << groups[i]->getGroupNumber() << " | ср=" << s->getAverage() << "\n";
                any = true;
            }
        }
    }
    if (!any) std::cout << "Нет студентов со средним баллом > " << threshold << "\n";
}