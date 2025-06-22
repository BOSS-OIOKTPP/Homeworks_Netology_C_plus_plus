#include<string>
#include "RaceParams.h"

std::string GetRaceTypeName(RaceType R) {
    switch (R) 
    {
        case RaceType::ground:    return "Гонка для наземного транспорта";
        case RaceType::air:       return "Гонка для воздушного транспорта";
        case RaceType::combined:  return "Гонка для наземного и воздушного транспорта";
        default:                  return "нет данных";            
    }
};

std::string GetTransportTypeName(TransportType TT) {
    switch (TT)
    {
        case TransportType::ground: return "Наземный транспорт";
        case TransportType::air:    return "Воздушный транспорт";
        default:                    return "нет данных";
    }
};

std::string GetTransportVidName(TransportVid TV) {
    switch (TV)
    {
        case TransportVid::boots:          return "Ботинки-вездеходы";
        case TransportVid::broom:          return "Метла";
        case TransportVid::camel:          return "Верблюд";
        case TransportVid::centaur:        return "Кентавр";
        case TransportVid::eagle:          return "Орел";
        case TransportVid::speed_camel:    return "Верблюд-скороход";
        case TransportVid::flying_carpet:  return "Ковер-самолет";
        default:                           return "нет данных";
    }
};


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
// Проверка транспорта на соответствие гонке
int Game::CheckTransportRace(Transport& T, std::string & errName) {


}



//int Game::CheckTransport(TransportVid TV, std::string& errName) {
//    int err{0};
//    errName = "";
//    switch (TV)
//    {
//        // Ботинки-вездеходы - наземный транспорт
//        case TransportVid::boots:  
//            if (transport.boots == 1)         { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::air)  { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }            
//            break;
//        // Метла - воздушный транспорт
//        case TransportVid::broom:  
//            if (transport.broom == 1)          { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::ground) { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//        // Верблюд - наземный транспорт   
//        case TransportVid::camel:          
//            if (transport.camel == 1)          { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::air)    { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//        // Кентавр - наземный транспорт
//        case TransportVid::centaur:        
//            if (transport.centaur == 1)        { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::air)    { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//        // Орел - воздушный транспорт
//        case TransportVid::eagle:          
//            if (transport.eagle == 1)          { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::ground) { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//        // Верблюд-скороход - наземный транспорт
//        case TransportVid::speed_camel:    
//            if (transport.speed_camel == 1)    { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::air)    { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//        // Ковер-самолет - воздушный транспорт
//        case TransportVid::flying_carpet: 
//            if (transport.flying_carpet == 1)  { err = 1; errName = GetTransportVidName(TV) + " уже зарегистрирован!"; }
//            else if (race == RaceType::ground) { err = 1; errName = "Попытка зарегистрировать неправильный тип транспортного средства!"; }
//            break;
//    }
//    return err;
//};