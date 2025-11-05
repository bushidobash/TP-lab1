#include "Keeper.h"
#include "DemoException.h"

#include <iostream>
#include <limits>
#include <string>

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1251 > nul");
    Keeper keeper;

    while (true) {
        std::cout << "\nМеню:\n"
                  << "1. Добавить объект\n"
                  << "2. Удалить объект\n"
                  << "3. Показать все\n"
                  << "4. Изменить объект\n"
                  << "5. Сохранить в файл\n"
                  << "6. Загрузить из файла\n"
                  << "7. Выход\n"
                  << "Выберите опцию: ";

        int op{};
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Повторите.\n";
            continue;
        }

        try {
            switch (op) {
                case 1:
                    keeper.addObject();
                    break;
                case 2: {
                    std::cout << "Введите индекс для удаления: ";
                    std::size_t idx{};
                    std::cin >> idx;
                    keeper.removeObject(idx);
                    break;
                }
                case 3:
                    keeper.viewAll();
                    break;
                case 4: {
                    std::cout << "Введите индекс для редактирования: ";
                    std::size_t idx{};
                    std::cin >> idx;
                    keeper.editObject(idx);
                    break;
                }
                case 5: {
                    std::cout << "Имя файла для сохранения: ";
                    std::string fname; std::cin >> fname;
                    keeper.saveToFile(fname);
                    std::cout << "Сохранено в " << fname << '\n';
                    break;
                }
                case 6: {
                    std::cout << "Имя файла для загрузки: ";
                    std::string fname; std::cin >> fname;
                    keeper.loadFromFile(fname);
                    std::cout << "Загружено из " << fname << '\n';
                    break;
                }
                case 7:
                    return 0;
                default:
                    std::cout << "Неверная опция, попробуйте снова.\n";
            }
        } catch (const DemoException& ex) {
            std::cout << "Ошибка: " << ex.what() << '\n';
        } catch (const std::exception& ex) {
            std::cout << "std::exception: " << ex.what() << '\n';
        } catch (...) {
            std::cout << "Неизвестная ошибка.\n";
        }
    }

    return 0;
}