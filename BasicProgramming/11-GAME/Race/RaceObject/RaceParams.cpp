#include<string>
#include "RaceParams.h"

std::string GetRaceTypeName(RaceType R) {
    switch (R) 
    {
        case RaceType::ground:    return "Гонка для наземного транспорта";
        case RaceType::air:       return "Гонка для воздушного транспорта";
        case RaceType::combined:  return "Гонка для наземного и воздушного транспорта";
        default:                  return "Гонка не выбрана";            
    }
};

std::string GetTransportTypeName(TransportType T) {
    switch (T)
    {
        case TransportType::boots:          return "Ботинки-вездеходы";
        case TransportType::broom:          return "Метла";
        case TransportType::camel:          return "Верблюд";
        case TransportType::centaur:        return "Кентавр";
        case TransportType::eagle:          return "Орел";
        case TransportType::speed_camel:    return "Верблюд-скороход";
        case TransportType::flying_carpet:  return "Ковер-самолет";
        default:                            return "Транспорт не выбран";
    }
};