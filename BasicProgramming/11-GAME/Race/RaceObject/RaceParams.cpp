#include<string>
#include <iostream>
#include "RaceParams.h"
#include "Transport.h"
#include "Boots.h"
#include "Broom.h"
#include "Camel.h"
#include "Centaur.h"
#include "Eagle.h"
#include "SpeedCamel.h"
#include "FlyingCarpet.h"




// Подготовка объекта к работе
void Game::InitGame() {
    Race = RaceType::none;  // Убираем Тип гонки
    RaceDistance = 0;       // Стираем дистанцию гонки
    ClearGame();                // Очищаем список транспортных средств
};

// Очищаем список транспортных средств
void Game::ClearGame() {
    for (Transport* T : Transports) {
        delete T;  // Удаляем каждый объект
    }
    Transports.clear();    // Очищаем вектор
};

// Деструктор
Game::~Game() {
    // Удаляем все объекты
    ClearGame();
}

// Создаем транспортное средство нужного вида
Transport* Game::CreateTransport(TransportVid TV) {
    switch (TV) {
        case TransportVid::boots:           return new Boots();         // Ботинки-вездеходы
        case TransportVid::broom:           return new Broom();         // Метла
        case TransportVid::camel:           return new Camel();         // Верблюд
        case TransportVid::centaur:         return new Centaur();       // Кентавр
        case TransportVid::eagle:           return new Eagle();         // Орел
        case TransportVid::speed_camel:     return new SpeedCamel();    // Верблюд-скороход
        case TransportVid::flying_carpet:   return new FlyingCarpet();  // Ковер-самолет
        default: return nullptr;
    }
};

// Добавляем транспорт
void Game::AddTransport(Transport* T) { Transports.push_back(T); }

// Определяем количество зарегистрированных транспортных средств
size_t Game::GetTransportCount() { return Transports.size(); };

// Записываем тип гонки
void Game::SetRace(RaceType R) {
    Race = R;
};

// Записываем дистанцию гонки
void Game::SetRaceDistance(int D) {
    RaceDistance = D;
};
// Прочитали тип гонки
RaceType Game::GetRace() {
    return Race;
};

// Прочитали дистанцию гонки
int Game::GetRaceDistance() {
    return RaceDistance;
};

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

bool Game::IsTransportValidForRegistration(TransportVid TV) {
    for (Transport* F : Transports) {
        if (F->Vid() == TV) { return false; }
    }
    return true;
};

// Печать состояния игры
void Game::PrintState() {
    std::cout << GetRaceTypeName(GetRace()) << ". Расстояние: " << GetRaceDistance() << std::endl;
    std::string t;
    for (Transport* TS : Transports) {
        if (t == "") {
            t = GetTransportVidName(TS->Vid());
        } 
        else {
            t = t + ", " + GetTransportVidName(TS->Vid());
        }
    }  
    if (t == "") {
        std::cout << "Зарегистрированные транспортные средства: - " << std::endl;
    }
    else {
        std::cout << "Зарегистрированные транспортные средства: " << t << std::endl;
    }
};

// Печать результатов игры
void Game::PrintResult() {
    std::cout << "Результаты гонки:" << std::endl;
    for (size_t i = 0; i < Transports.size() - 1; i++) {
        std::cout << i+1 << ".  " << GetTransportVidName(Transports[i]->Vid()) << ".  Время: " << Transports[i]->Time() << std::endl;
    }
};

// Запускаем гонку
void Game::Run() {
    // Вычисляем время прохождения дистанции транспортными средствами
    for (Transport* T : Transports) { T->Calc(GetRaceDistance()); }
    // Выполняем сортировку объектов по возрастанию времени 
    Sort();
};

// Сортировка транспортных средств по времени прохождения дистанции. Самые быстрые на первом месте
void Game::Sort() {
    bool sorted;
    for (size_t i = 0; i < Transports.size() - 1; i++) {
        sorted = false;
        for (size_t j = 0; j < Transports.size() - i - 1; j++) {
            // Сравниваем значения времени 
            if (Transports[j]->Time() > Transports[j + 1]->Time()) {
                // Перестановка указателей
                Transport* temp = Transports[j];
                Transports[j] = Transports[j + 1];
                Transports[j + 1] = temp;
                sorted = true;
            }
        }
        if (!sorted) { 
            break; 
        }
    }
}