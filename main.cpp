#include "Keeper.h"
#include "DemoException.h"

#include <iostream>
#include <limits>
#include <string>

int main() {
    // Устанавливаю локаль для корректной работы с русскими символами
    setlocale(LC_ALL, "");
    // Меняю кодировку 1251
    system("chcp 1251 > nul");
    
    // Создаю объект Keeper для хранения и управления данными
    Keeper keeper;

    // Основной бесконечный цикл меню
    while (true) {
        // Вывод меню
        std::cout << "\nМеню:\n"
                  << "1. Добавить объект\n"
                  << "2. Удалить объект\n"
                  << "3. Показать все\n"
                  << "4. Изменить объект\n"
                  << "5. Сохранить в файл\n"
                  << "6. Загрузить из файла\n"
                  << "7. Выход\n"
                  << "Выберите опцию: ";

        int op{};  /*Переменная для выбора опции, чтение выбора пользователя с проверкой на корректность ввода */ 

        if (!(std::cin >> op)) {
            // Если ввод был некорректным (не число), очищаем состояние потока
            std::cin.clear();
            // Игнорируем оставшиеся в потоке символы до конца строки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // Сообщаем об ошибке и возвращаемся к началу цикла
            std::cout << "Неверный ввод. Повторите.\n";
            continue;
        }

        // Блок try-catch для обработки исключений при выполнении операций
        try {
            // Обработка выбранной пользователем опции
            switch (op) {
                case 1:  // Добавление нового объекта
                    keeper.addObject();
                    break;
                case 2: {  // Удаление объекта по индексу
                    std::cout << "Введите индекс для удаления: ";
                    std::size_t idx{};
                    std::cin >> idx;
                    keeper.removeObject(idx);
                    break;
                }
                case 3:  // Просмотр всех объектов
                    keeper.viewAll();
                    break;
                case 4: {  // Редактирование объекта по индексу
                    std::cout << "Введите индекс для редактирования: ";
                    std::size_t idx{};
                    std::cin >> idx;
                    keeper.editObject(idx);
                    break;
                }
                case 5: {  // Сохранение всех объектов в файл
                    std::cout << "Имя файла для сохранения: ";
                    std::string fname; 
                    std::cin >> fname;  // Чтение имени файла
                    keeper.saveToFile(fname);
                    std::cout << "Сохранено в " << fname << '\n';
                    break;
                }
                case 6: {  // Загрузка объектов из файла
                    std::cout << "Имя файла для загрузки: ";
                    std::string fname; 
                    std::cin >> fname;  // Чтение имени файла
                    keeper.loadFromFile(fname);
                    std::cout << "Загружено из " << fname << '\n';
                    break;
                }
                case 7:  // Выход из программы
                    return 0;
                default:  // Обработка недопустимого выбора
                    std::cout << "Неверная опция, попробуйте снова.\n";
            }
        } 
        // Обработка пользовательских исключений DemoException
        catch (const DemoException& ex) {
            std::cout << "Ошибка: " << ex.what() << '\n';
        } 
        // Обработка стандартных исключений C++
        catch (const std::exception& ex) {
            std::cout << "std::exception: " << ex.what() << '\n';
        } 
        // Обработка любых других исключений
        catch (...) {
            std::cout << "Неизвестная ошибка.\n";
        }
    }

    return 0;
}