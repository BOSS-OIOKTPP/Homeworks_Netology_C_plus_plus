#include "Transport.h"

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

Transport::Transport() : tType{ TransportType::none }, tVid{ TransportVid::none }, tV{ 0 }, tDistance{ 0 }, tTime{ 0.0 } {}
void Transport::Calc(int distance) {};
TransportType Transport::Type() { return tType; }
TransportVid Transport::Vid() { return tVid; }
int Transport::V() { return tV; }
int Transport::Distance() { return tDistance; }
double Transport::Time() { return tTime; }
bool Transport::canParticipate(RaceType RT) { return tRaces.count(RT) > 0; }