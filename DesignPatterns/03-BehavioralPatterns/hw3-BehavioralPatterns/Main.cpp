#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <stdexcept>

enum class Type { 
    tWARNING,           // Предупреждение
    tERROR,             // Ошибка
    tFATAL_ERROR,       // Фатальная ошибка
    tUNKNOWN };         // Неизвестное сообщение


// Сообщение
class LogMessage {
public:
    LogMessage(Type t, const std::string& msg) : type_(t), message_(msg) {}
    Type type() const { 
        return type_; 
    }
    const std::string& message() const { 
        return message_; 
    }
private:
    Type type_;
    std::string message_;
};

// Базовый обработчик
class HandlerBase {
public:
    virtual ~HandlerBase() = default;

    virtual void handler_request(const LogMessage& msg) = 0;
    virtual void set_next_handler(HandlerBase* next) = 0;
};

// Обработчик предупреждения
class WarningHandler : public HandlerBase {    
public:
    void set_next_handler(HandlerBase* next) {
        next_handler = next;
    }
    void handler_request(const LogMessage& msg) {
        if (msg.type() == Type::tWARNING) {
            std::cout << "[ВНИМАНИЕ]: " << msg.message() << std::endl;
        }
        else if (next_handler != nullptr) {
            next_handler->handler_request(msg);
        }        
    }
private:
    HandlerBase* next_handler = nullptr;
};

// Обработчик ошибки
class ErrorHandler : public HandlerBase {
public:
    ErrorHandler(const std::string& path) : path_(path) {}

    void set_next_handler(HandlerBase* next) {
        next_handler = next;
    }
    void handler_request(const LogMessage& msg) {
        if (msg.type() == Type::tERROR) {
            // Пишем в файл
            // Имитируем запись в файл
            std::cout << "[ОШИБКА] сохранено в файл \"" << path_ << "\": " << msg.message() << std::endl;

            //std::ofstream file(path_, std::ios::app);
            //if (file.is_open()) {
            //    file << "[ОШИБКА] сохранено в файл \"" << path_ << "\": " << msg.message() << std::endl;
            //}            
        }
        else if (next_handler != nullptr) {
            next_handler->handler_request(msg);
        }
    }    
private:
    HandlerBase* next_handler = nullptr;
    std::string path_;
};

// Обработчик фатальной ошибки
class FatalErrorHandler : public HandlerBase {
public:
    void set_next_handler(HandlerBase* next) {
        next_handler = next;
    }
    void handler_request(const LogMessage& msg) {
        if (msg.type() == Type::tFATAL_ERROR) {
            throw std::runtime_error("[КРИТИЧЕСКАЯ ОШИБКА]: " + msg.message());            
        }
        else if (next_handler != nullptr) {
            next_handler->handler_request(msg);
        }
    }    
private:
    HandlerBase* next_handler = nullptr;
};

// Обработчик неизвестного сообщения
class UnknownHandler : public HandlerBase {
public:
    void set_next_handler(HandlerBase* next) {
        next_handler = next;
    }
    void handler_request(const LogMessage& msg) {
        if (msg.type() == Type::tUNKNOWN) {
            throw std::runtime_error("[НЕИЗВЕСТНАЯ ОШИБКА]: " + msg.message());
        }
        else if (next_handler != nullptr) {
            next_handler->handler_request(msg);
        }
    }
private:
    HandlerBase* next_handler = nullptr;
};

int main() {

    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Строим цепочку из задания:
    // 1. Фатальные ошибки
    // 2. Ошибки
    // 3. Предупреждения
    // 4. Неизвестные сообщения

    FatalErrorHandler fErr;
    ErrorHandler eErr("app.log");
    WarningHandler wErr;
    UnknownHandler uErr;

    fErr.set_next_handler(&eErr);
    eErr.set_next_handler(&wErr);
    wErr.set_next_handler(&uErr);

    // Указатель на начало цепочки
    HandlerBase* h = &fErr;
       
    // Тесты
    // 1
    std::cout << "Тест 1: ";
    LogMessage msgWARNING(Type::tWARNING, "Недостаточно памяти");
    h->handler_request(msgWARNING);
    std::cout << std::endl;

    // 2
    std::cout << "Тест 2: ";
    LogMessage msgERROR(Type::tERROR, "Деление на 0");
    h->handler_request(msgERROR);
    std::cout << std::endl;

    // 3
    std::cout << "Тест 3: ";
    LogMessage msgFATAL_ERROR(Type::tFATAL_ERROR, "Сбой системы");
    try {
        h->handler_request(msgFATAL_ERROR);
    }
    catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;

    // 4
    std::cout << "Тест 4: ";
    LogMessage msgUNKNOWN(Type::tUNKNOWN, "Команда не обработана");
    try {
        h->handler_request(msgUNKNOWN);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << std::endl;


    
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}