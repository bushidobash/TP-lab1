#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include "Group.h"

class GroupManager {
private:
    Group** groups;
    int groupCount;

    void sortByGroupNumber(); // сортировка при вводе
public:
    GroupManager();
    ~GroupManager();

    int getGroupCount() const;
    Group* getGroupAt(int idx) const;

    void addGroupAt(int pos, Group* g); // вставка
    Group* removeGroupAt(int pos); // удаление, возвращает указатель (caller удаляет)

    void appendGroup(Group* g);

    void inputNewGroupInteractive(); // ввод новой группы пользователем (вставка упорядоченно)
    void printAllBrief() const;
    void printAllFull() const;

    void listAllStudentsWithAvgGreater(double threshold) const;
};

#endif // GROUPMANAGER_H