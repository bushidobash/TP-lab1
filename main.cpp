#include <iostream>
#include <limits>
#include "GroupManager.h"
#include "utils.h"
#include <windows.h>
#include <locale>

void printMainMenu() {
    std::cout << "\n--- Главное меню ---\n";
    std::cout << "1. Добавить новую группу (интерактивно, затем сортируется по номеру группы)\n";
    std::cout << "2. Вставить группу на позицию\n";
    std::cout << "3. Удалить группу по индексу\n";
    std::cout << "4. Просмотреть кратко все группы\n";
    std::cout << "5. Просмотреть подробно все группы\n";
    std::cout << "6. Добавить студента в группу (вставка на позицию)\n";
    std::cout << "7. Удалить студента из группы\n";
    std::cout << "8. Редактировать студента\n";
    std::cout << "9. Вывести список всех студентов со средним > 4.0\n";
    std::cout << "10. Задание 2: прочитать файл и поменять каждые два соседних слова местами\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::setlocale(LC_ALL, "rus");
    
    GroupManager manager;

    while (true) {
        printMainMenu();
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Ошибка ввода. Попробуйте снова.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            if (choice == 0) {
                std::cout << "Выход. Освобождение ресурсов...\n";
                break;
            } else if (choice == 1) {
                manager.inputNewGroupInteractive();
            } else if (choice == 2) {
                std::cout << "Введите позицию для вставки (0.. " << manager.getGroupCount() << "): ";
                int pos; std::cin >> pos; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Group* g = new Group();
                std::cout << "Заполните данные новой группы:\n";
                std::cout << "Номер группы: ";
                int num; std::cin >> num; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                g->setGroupNumber(num);
                int subCount;
                std::cout << "Сколько предметов? ";
                std::cin >> subCount; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (subCount > 0) {
                    std::string* subs = new std::string[subCount];
                    for (int i = 0; i < subCount; ++i) {
                        std::cout << "Предмет #" << i+1 << ": ";
                        std::getline(std::cin, subs[i]);
                    }
                    g->setSubjects(subCount, subs);
                    delete[] subs;
                }
                manager.addGroupAt(pos, g);
            } else if (choice == 3) {
                manager.printAllBrief();
                std::cout << "Индекс группы для удаления: ";
                int idx; std::cin >> idx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Group* removed = manager.removeGroupAt(idx);
                delete removed;
                std::cout << "Группа удалена.\n";
            } else if (choice == 4) {
                manager.printAllBrief();
            } else if (choice == 5) {
                manager.printAllFull();
            } else if (choice == 6) {
                manager.printAllBrief();
                std::cout << "Выберите индекс группы для добавления студента: ";
                int gidx; std::cin >> gidx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Group* g = manager.getGroupAt(gidx);
                std::cout << "Позиция (0.." << g->getStudentCount() << "): ";
                int pos; std::cin >> pos; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Student* s = new Student();
                std::cin >> *s;
                g->addStudentAt(pos, s);
                std::cout << "Студент добавлен.\n";
            } else if (choice == 7) {
                manager.printAllBrief();
                std::cout << "Выберите индекс группы: ";int gidx; std::cin >> gidx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Group* g = manager.getGroupAt(gidx);
                g->printFull(std::cout);
                std::cout << "Индекс студента для удаления: ";
                int sidx; std::cin >> sidx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Student* removed = g->removeStudentAt(sidx);
                delete removed;
                std::cout << "Студент удалён.\n";
            } else if (choice == 8) {
                manager.printAllBrief();
                std::cout << "Выберите индекс группы: ";
                int gidx; std::cin >> gidx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Group* g = manager.getGroupAt(gidx);
                g->printFull(std::cout);
                std::cout << "Индекс студента для редактирования: ";
                int sidx; std::cin >> sidx; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                g->editStudentAt(sidx);
            } else if (choice == 9) {
                manager.listAllStudentsWithAvgGreater(4.0);
            } else if (choice == 10) {
                std::cout << "Введите имя входного файла: ";
                std::string fname;
                std::getline(std::cin, fname);
                try {
                    swapWordsInFileAndPrint(fname);
                } catch (const std::exception& ex) {
                    std::cout << "Ошибка при обработке файла: " << ex.what() << "\n";
                }
            } else {
                std::cout << "Неверный пункт меню.\n";
            }
        } catch (const std::exception& ex) {
            std::cout << "Исключение: " << ex.what() << "\n";
        }
    }

    return 0;
}