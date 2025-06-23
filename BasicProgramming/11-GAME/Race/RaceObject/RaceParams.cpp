#include<string>
#include "RaceParams.h"
#include "Transport.h"




// Очищаем список транспортных средств
void Game::Clear() {
    for (Transport* T : Transports) {
        delete T;  // Удаляем каждый объект
    }
    Transports.clear();    // Очищаем вектор
};

// Деструктор
Game::~Game() {
    // Удаляем все объекты
    Clear();
}

// Добавляем транспорт
void Game::AddTransport(Transport* T) { Transports.push_back(T); }

// Проверка транспорта на соответствие типу гонке
// true - транспорт соответствует выбранной гонке
bool Game::IsTransportValidForRaceType(Transport& T, std::string& E) {
    if (!T.canParticipate(Race)) {
        E = "Попытка зарегистрировать неправильный тип транспортного средства!";
        return false;
    }
    return true;
}

// Проверка транспорта на регистрацию, зарегистрировать транспорт можно только 1 раз
// true - транспорт еще не зарегистрирован на гонку
bool Game::IsTransportValidForRegistration(Transport& T, std::string& E) {
    for (Transport* F : Transports) {
        if (F->Vid() == T.Vid()) {
            E = GetTransportVidName(T.Vid()) + " уже зарегистрирован!";
            return false;
        }
    }
    return true;
};