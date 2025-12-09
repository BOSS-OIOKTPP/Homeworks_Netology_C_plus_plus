#include <iostream>
#include <windows.h>
#include <string>
#include <map>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept {
        return "Value";
        //return "Very Big Data String: " + key;
    }
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB (VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        if (cache_.find(key) == cache_.end()) {
            std::cout << "Get from real object\n";
            cache_[key] = real_db_->GetData(key);
        } else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key);
    }
private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class TestDB : VeryHeavyDatabase {
public:
    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {}
    std::string GetData(const std::string& key) noexcept {
        return "test_data\n";
    }
private:
    VeryHeavyDatabase* real_db_;
};

// Новый класс
class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : real_db_(real_object), shots_left_(shots) {}
    std::string GetData(const std::string& key) noexcept {
        if (shots_left_ > 0) {
            shots_left_--;
            return real_db_->GetData(key);
        }
        else {
            return "error";
        }
    }
private:
    VeryHeavyDatabase* real_db_;
    size_t shots_left_;  // сколько вызовов осталось
};



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    auto real_db = VeryHeavyDatabase();    
    auto limit_db = OneShotDB(std::addressof(real_db), 2);

    std::cout << "1: " << limit_db.GetData("key") << std::endl;
    std::cout << "2: " << limit_db.GetData("key") << std::endl;
    std::cout << "3: " << limit_db.GetData("key") << std::endl;



    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;

}
