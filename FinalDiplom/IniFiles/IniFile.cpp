#include "IniFile.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <filesystem>
#include <charconv> // C++17+, но нормально в C++20

// Конструктор
IniFile::IniFile(const std::string& fileName) : m_fileName(fileName) {
    load();
}

// Загрудаем файл
void IniFile::load() {
    // Очищаем данные
    m_data.clear();

    // Если файла нет, то выходим
    if (!std::filesystem::exists(m_fileName)) {
        return;
    }

    // Открываем файл на чтение
    std::ifstream file(m_fileName);
    if (!file.is_open()) {
        throw IniFileException("Не удалось открыть INI-файл: " + m_fileName);
    }

    // Читаем в файле каждую строку и сохраняем результат в память
    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        // Обязательно первой командой вызываем очистку от символов: пробел, таб, возврат корректки " \t\r".
        std::string trimmed = trim(line);

        // Проверяем, если строка пустая или это комментарий, то пропускаем
        // Если файл будет перезаписан, то комментарии сотрутся
        if (trimmed.empty() || trimmed[0] == ';' || trimmed[0] == '#') {
            continue; 
        }

        // Секция: [Section]
        if (trimmed.front() == '[' && trimmed.back() == ']') {
            currentSection = trim(trimmed.substr(1, trimmed.size() - 2));
            // Создаем пустую секцию, одинаковые секции не добавляются
            m_data.try_emplace(currentSection, std::map<std::string, std::string>{});            
            continue;
        }

        // Ключ = Значение        
        auto eqPos = trimmed.find('=');
        if (eqPos != std::string::npos) {
            std::string key   = trim(trimmed.substr(0, eqPos));
            std::string value = trim(trimmed.substr(eqPos + 1));

            // Удаляем кавычки, если есть: "value" или 'value'
            if (value.size() >= 2) {
                char first = value.front();
                char last = value.back();
                if ((first == '"' && last == '"') || 
                    (first == '\'' && last == '\'')) {
                    value = value.substr(1, value.size() - 2);
                }
            }

            // Если текущая секция выбрана, то запоминаем ключ=значение
            if (!currentSection.empty()) {
                m_data[currentSection][key] = value;
            }
        }        
    }
}

void IniFile::updateFile() {
    save();
}

void IniFile::save() const {
    // Открываем файл на запись
    std::ofstream file(m_fileName);
    if (!file.is_open()) {
        throw IniFileException("Не удалось записать INI-файл: " + m_fileName);
    }

    // Сохраняем в чистом UTF-8 (без BOM!)
    for (const auto& [section, keys] : m_data) {
        file << "[" << section << "]\n";
        for (const auto& [key, value] : keys) {
            file << key << " = " << value << "\n";
        }
        file << "\n";
    }
}

// Читаем строковое значение
std::string IniFile::readString(const std::string& section, const std::string& key, const std::string& def) const {
    auto secIt = m_data.find(section);
    if (secIt != m_data.end()) {
        auto keyIt = secIt->second.find(key);
        if (keyIt != secIt->second.end()) {
            return keyIt->second;
        }
    }
    return def;
}
// Записываем строковое значение
void IniFile::writeString(const std::string& section, const std::string& key, const std::string& value) {
    m_data[section][key] = value;
}

// Читаем целое значение
int IniFile::readInteger(const std::string& section, const std::string& key, int def) const {
    std::string str = readString(section, key);
    if (str.empty()) return def;
    try {
        size_t pos;
        int val = std::stoi(str, &pos);
        if (pos == str.size()) return val;
    }
    catch (...) {
        // если ошибка преобразования,то ничего не делаем
    }
    return def;
}
// Сохраняем целое значение
void IniFile::writeInteger(const std::string& section, const std::string& key, int value) {
    writeString(section, key, std::to_string(value));
}

// Читаем булевский тип
bool IniFile::readBool(const std::string& section, const std::string& key, bool def) const {
    std::string str = readString(section, key);
    if (str.empty()) return def;
    std::string lower = str;
    // Переводим в нижний регистр, на всякий случай
    std::transform(lower.begin(), lower.end(), lower.begin(),
        [](unsigned char c) { return static_cast<unsigned char>(std::tolower(c)); });
    // Выдаем результат
    return (lower == "1") || (lower == "true") || (lower == "yes") || (lower == "on");
}
// Сохраняем булевский тип
void IniFile::writeBool(const std::string& section, const std::string& key, bool value) {
    writeString(section, key, value ? "1" : "0");
}

// Читаем вещественное число
double IniFile::readFloat(const std::string& section, const std::string& key, double def) const {
    std::string str = readString(section, key);
    double result;
    if (stringToFloat(str, result)) {
        return result;
    }
    return def;
}
// Сохраняем вещественное число
void IniFile::writeFloat(const std::string& section, const std::string& key, double value) {
    writeString(section, key, floatToString(value));
}

// Функция получает список всех секций INI-файла и записывает их в переданный вектор
void IniFile::readSections(std::vector<std::string>& out) const {
    out.clear();
    for (const auto& sec : m_data) {
        out.push_back(sec.first);
    }
}

// Читаем все ключи секции
//[User]
//Name = Иван
//Age = 25
//Active = 1
// то команда 
//      std::vector<std::string> keys;
//      ini.readSection("User", keys);
// заполнит keys: {"Name", "Age", "Active"}
void IniFile::readSection(const std::string& section, std::vector<std::string>& out) const {
    out.clear();
    auto it = m_data.find(section);
    if (it != m_data.end()) {
        for (const auto& kv : it->second) {
            out.push_back(kv.first);
        }
    }
}

// Удаляем секцию
void IniFile::eraseSection(const std::string& section) {
    m_data.erase(section);
}

// Удаляем поле key со значением из секции section 
void IniFile::deleteKey(const std::string& section, const std::string& key) {
    auto secIt = m_data.find(section);
    if (secIt != m_data.end()) {
        secIt->second.erase(key);
        if (secIt->second.empty()) {
            m_data.erase(secIt);
        }
    }
}


// Вспомогательные функции

// Удаляем пробел и спецсимволы в начале и конце строки
std::string IniFile::trim(const std::string& s) {
    if (s.empty()) return s;
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

// Конвертируем вещественное число в строку
std::string IniFile::floatToString(double value) {
    std::ostringstream oss;
    oss.imbue(std::locale::classic());   // точка как разделитель
    oss.precision(10);                   // точность, количество знаков после запятой
    oss << std::fixed << value;          // фиксированная нотация (без экспоненты)
    std::string s = oss.str();

    // Удаляем конечные нули
    if (s.find('.') != std::string::npos) {
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        if (s.back() == '.') {           // Если после точки нет символов, то удаляем точку
            s.pop_back();
        }
    }
    return s;
    
    
    /*
        std::ostringstream oss;
        oss.imbue(std::locale::classic()); // точка как разделитель
        oss.precision(17);                 // достаточно для double
        oss << value;
        return oss.str();
    */
}

// Конвертируем строку в вещественное число
bool IniFile::stringToFloat(const std::string& str, double& out) {
    if (str.empty()) return false;
    double val;
    const char* begin = str.c_str();
    const char* end = begin + str.size();
    auto result = std::from_chars(begin, end, val);
    if (result.ec == std::errc{} && result.ptr == end) {
        out = val;
        return true;
    }
    return false;
}