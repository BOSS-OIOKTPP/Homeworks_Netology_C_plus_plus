#include "Transport.h"

std::string GetRaceTypeName(RaceType R) {
    std::string S;
    switch (R)
    {
    case RaceType::ground:    S = "Гонка для наземного транспорта"; break;
    case RaceType::air:       S = "Гонка для воздушного транспорта"; break;
    case RaceType::combined:  S = "Гонка для наземного и воздушного транспорта"; break;
    default:                  S = "нет данных"; 
    }
    return S;
};

std::string GetTransportTypeName(TransportType TT) {
    std::string S;
    switch (TT)
    {
    case TransportType::ground: S = "Наземный транспорт"; break;
    case TransportType::air:    S = "Воздушный транспорт"; break;
    default:                    S = "нет данных"; 
    }
    return S;
};

std::string GetTransportVidName(TransportVid TV) {
    std::string S;
    switch (TV)
    {
    case TransportVid::boots:          S = "Ботинки-вездеходы"; break;
    case TransportVid::broom:          S = "Метла"; break;
    case TransportVid::camel:          S = "Верблюд"; break;
    case TransportVid::centaur:        S = "Кентавр"; break;
    case TransportVid::eagle:          S = "Орел"; break;
    case TransportVid::speed_camel:    S = "Верблюд-скороход"; break;
    case TransportVid::flying_carpet:  S = "Ковер-самолет"; break;
    default:                           S = "нет данных";
    }
    return S;
};

Transport::Transport() : tType{ TransportType::none }, tVid{ TransportVid::none }, tV{ 0 }, tDistance{ 0 }, tTime{ 0.0 } {}
void Transport::Calc(int distance) {};
TransportType Transport::Type() { return tType; }
TransportVid Transport::Vid() { return tVid; }
int Transport::V() { return tV; }
int Transport::Distance() { return tDistance; }
double Transport::Time() { return tTime; }
bool Transport::canParticipate(RaceType RT) { return tRaces.count(RT) > 0; }