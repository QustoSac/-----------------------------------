#include <iostream>
#include <dlfcn.h>

int main() {
    void* handle = dlopen("./libmystring.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "Ошибка загрузки библиотеки: " << dlerror() << std::endl;
        return 1;
    }

    typedef std::string (*removeChar_t)(const std::string&, char);
    removeChar_t removeChar = (removeChar_t)dlsym(handle, "removeChar");
    if (!removeChar) {
        std::cerr << "Ошибка при получении указателя на функцию: " << dlerror() << std::endl;
        return 1;
    }

    std::string filename = "./input.txt";
     char symbol;
     
    std::cout << "Введите символ для замены: ";
    std::cin >> symbol;

    std::string result = removeChar(filename, symbol);

    std::cout << "Обработанный текст: " << result << std::endl;

    dlclose(handle);
    return 0;
}