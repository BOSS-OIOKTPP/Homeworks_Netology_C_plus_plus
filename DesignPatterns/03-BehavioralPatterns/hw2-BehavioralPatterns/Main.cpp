#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <memory>


// Базовый класс наблюдателя
class Observer {
public:
    virtual ~Observer() = default;

    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
};

// Предупреждения, пишем в консоль
class WarningObserver: public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "[ВНИМАНИЕ] " << message << std::endl;
    }
};

// Ошибки, пишем в файл
class ErrorObserver : public Observer {
public:
    explicit ErrorObserver(const std::string& path): path_(path) {}

    // имитируем запись в файл
    void onError(const std::string& message) override {
        std::cout << "[ОШИБКА] сохранено в файл \"" << path_ << "\": " << message << std::endl;
        //std::ofstream file(path_, std::ios::app);
        //if (file.is_open()) {
        //    file << "[ОШИБКА] сохранено в файл \"" << path_ << "\": " << message << std::endl;
        //}
    }
private:
    std::string path_;
};

// Фатальные ошибки, пишем в консоль и файл
class FatalErrorObserver : public Observer {
public:
    explicit FatalErrorObserver(const std::string& filepath): path_(filepath) {}
    void onFatalError(const std::string& message) override {
        // Пишем в консоль
        std::cout << "[КРИТИЧЕСКАЯ ОШИБКА] " << message << std::endl;  
        
        // Пишем в файл
        // имитируем запись в файл
        std::cout << "[КРИТИЧЕСКАЯ ОШИБКА] сохранено в файл \"" << path_ << "\": " << message << std::endl;

        //std::ofstream file(path_, std::ios::app);
        //if (file.is_open()) {
        //    file << "[КРИТИЧЕСКАЯ ОШИБКА] сохранено в файл \"" << path_ << "\": " << message << std::endl;
        //}
    }
private:
    std::string path_;
};


// Наблюдаемый класс
class LogFile {
public:
    // Добавляем наблюдателя с помощью не владеющего указателя
    void add_observer(std::weak_ptr<Observer> obs) {observers_.push_back(obs); }
    
    // Предупреждение
    void warning(const std::string& message) const {
        for (auto& weak_obs : observers_) {
            if (auto observer = weak_obs.lock()) {  // получаем ссылку shared_ptr, чтобы гарантировать,что объект не умер
                observer->onWarning(message);
            }
        }
    }
    // Ошибка
    void error(const std::string& message) const {
        for (auto& weak_obs : observers_) {
            if (auto observer = weak_obs.lock()) {
                observer->onError(message);
            }
        }
    }
    // Фатальная ошибка
    void fatalError(const std::string& message) const { 
        for (auto& weak_obs : observers_) {
            if (auto observer = weak_obs.lock()) {
                observer->onFatalError(message);
            }
        }
    }
private:    
    std::vector<std::weak_ptr<Observer>> observers_;
};



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Создаем наблюдаемый объект
    LogFile obs;

    // Создаем наблюдателей через shared_ptr
    auto warning_obs = std::make_shared<WarningObserver>();
    auto error_obs = std::make_shared<ErrorObserver>("errors.log");
    auto fatal_obs = std::make_shared<FatalErrorObserver>("fatal_errors.log");

     // Подписываем наблюдателей
    obs.add_observer(warning_obs);
    obs.add_observer(error_obs);
    obs.add_observer(fatal_obs);

    // Генерируем события
    //std::cout << "=== Тест 1: Все наблюдатели подписаны ===" << std::endl;
    obs.warning("Недостаточный объем памяти");
    obs.error("Файл не найден");
    obs.fatalError("Потеряно соединение с базой данных");


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;

}
