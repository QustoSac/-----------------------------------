## Задание по теме: Динамически подключаемые библиотеки

### Цель

1. Создать динамическую библиотеку (в Linux - .so), реализующую функцию обработки файла.
2. Разработать программу, использующую эту библиотеку для обработки файла.

### Описание

В этом задании мы изучим концепцию динамически подключаемых библиотек, которые позволяют:

* Модульность: Разбивать программы на отдельные модули, повышая читаемость, удобство разработки и поддержки.
* Экономия памяти: Общие компоненты могут использоваться многими программами без дублирования кода.
* Обновление: Можно обновлять библиотеки без необходимости перекомпилировать все программы, использующие их.
* Переносимость: Библиотеки могут использоваться на разных платформах.

### Реализация

#### 1. Библиотека  libmystring.so

Файл mystring.cpp:#include <string>
#include <fstream>
#include <iostream>

extern "C" {

std::string removeChar(const std::string& filename, char symbol) {
    std::ifstream file(filename);
    std::string content, result;

    if (file.is_open()) {
        while (std::getline(file, content)) {
            for (char& c : content) {
                if (c == symbol) {
                    c = ' '; 
                }
            }
            result += content + "\n";
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }

    return result;
}

}
Компиляция:g++ -fPIC -c mystring.cpp -o mystring.o
g++ -shared -o libmystring.so mystring.o
#### 2. Программа main

Файл main.cpp:#include <iostream>
#include <dlfcn.h>

int main() {
    void* handle = dlopen("libmystring.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }

    typedef std::string (*removeChar_t)(const std::string&, char);
    removeChar_t removeChar = (removeChar_t)dlsym(handle, "removeChar");
    if (!removeChar) {
        std::cerr << "Error getting function pointer: " << dlerror() << std::endl;
        return 1;
    }

    std::string filename = "input.txt";
    char symbol;

    std::cout << "Введите символ для замены: ";
    std::cin >> symbol;

    std::string result = removeChar(filename, symbol);

    std::cout << "Обработанный текст: " << result << std::endl;

    dlclose(handle);
    return 0;
}
Компиляция:g++ -o main main.cpp -L. -lmystring
#### 3. Запуск./main
Ввод: Введите символ, который хотите удалить из файла input.txt.

Вывод: Программа выведет обработанный текст, в котором удален заданный символ.

### Дополнительные замечания

* В данном примере функция removeChar удаляет символ из файла. 
* Вы можете модифицировать mystring.cpp для реализации другой функции обработки файлов.
* Убедитесь, что файл input.txt находится в той же директории, что и программа main.

### Ресурсы

* [Создание динамических библиотек в Linux](https://www.geeksforgeeks.org/shared-libraries-in-linux/)
* [Введение в динамические библиотеки](https://en.wikipedia.org/wiki/Dynamic-link_library)
