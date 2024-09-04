#include <string>
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