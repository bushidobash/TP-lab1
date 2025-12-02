#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector> // только для удобства токенизации в утилитарной функции; если надо, можно переписать без vector
#include <stdexcept>

void swapWordsInFileAndPrint(const std::string& filename) {
    std::ifstream fin(filename.c_str());
    if (!fin.is_open()) throw std::runtime_error("Не удалось открыть файл для чтения.");

    // Считываем весь файл в строку
    std::ostringstream ss;
    ss << fin.rdbuf();
    std::string text = ss.str();
    fin.close();

    // Токенизация по пробельным символам:
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string w;
    while (iss >> w) words.push_back(w);

    // Меняем каждые два соседних
    for (size_t i = 0; i + 1 < words.size(); i += 2) {
        std::swap(words[i], words[i+1]);
    }

    // Вывод результата в консоль, сохраняя пробелы между словами
    for (size_t i = 0; i < words.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << words[i];
    }
    std::cout << "\n";
}