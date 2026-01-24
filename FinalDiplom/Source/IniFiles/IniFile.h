#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// Исключение
class IniFileException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Класс для работы с INI файлом
class IniFile {
public:
    explicit IniFile(const std::string& fileName);
    ~IniFile() = default;

    // Чтение/запись значений
    std::string readString(const std::string& section, const std::string& key, const std::string& def = "") const;
    void writeString(const std::string& section, const std::string& key, const std::string& value);

    int readInteger(const std::string& section, const std::string& key, int def = 0) const;
    void writeInteger(const std::string& section, const std::string& key, int value);

    bool readBool(const std::string& section, const std::string& key, bool def = false) const;
    void writeBool(const std::string& section, const std::string& key, bool value);

    double readFloat(const std::string& section, const std::string& key, double def = 0.0) const;
    void writeFloat(const std::string& section, const std::string& key, double value);

    // Работа с секциями
    void readSection(const std::string& section, std::vector<std::string>& out) const;
    void readSections(std::vector<std::string>& out) const;    

    void eraseSection(const std::string& section);
    void deleteKey(const std::string& section, const std::string& key);

    // Сохранение на диск
    void updateFile();

    // Имя файла
    const std::string& fileName() const noexcept { return m_fileName; }

private:
    std::string m_fileName;
    std::map<std::string, std::map<std::string, std::string>> m_data;

    void load();
    void save() const;

    // Вспомогательные методы
    static std::string trim(const std::string& s);
    static std::string floatToString(double value);
    static bool stringToFloat(const std::string& str, double& out);
    
};