#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>


class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

// Вывод в консоль
class ConsoleLogCommand : public LogCommand {
public:    
    void print(const std::string& message) override {
        std::cout << "[CONSOLE] " << message << std::endl;
    }
};

// Вывод в файл
class FileLogCommand : public LogCommand {
public:
    explicit FileLogCommand(const std::string& path): path_(path) {}

    void print(const std::string& message) override {
        std::ofstream f (path_, std::ios::app);  // открываем для дописывания
        if (f.is_open()) {
            f << "[FILE] " << message << std::endl;
            f.close();
        }
        else {
            std::cerr << "ОШИБКА: Не удалось открыть файл " << path_ << std::endl;
        }
    }
private:
    std::string path_;
};

// Функция, которая выполняет команды
void print(LogCommand& command) {
    command.print("Hello, World!");
}




int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // 1. Вывод в консоль
    ConsoleLogCommand console_command;
    print(console_command);  // Вывод: [CONSOLE] Hello, World!

    // 2. Вывод в файл
    //std::cout << "Запись в файл log.txt" << std::endl;
    FileLogCommand file_command("log.txt");
    print(file_command);  // Запись в файл log.txt



    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;

}
