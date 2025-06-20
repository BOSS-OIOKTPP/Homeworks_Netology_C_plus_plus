#include "RaceParams.h"
#include "Transport.h"


Transport::Transport() : tType{ TransportType::none }, tVid{ TransportVid::none }, tV{ 0 } {}
void Transport::Calc(int distance) {};
TransportType Transport::Type() { return tType; }
TransportVid Transport::Vid() { return tVid; }
int Transport::V() { return tV; }
int Transport::Distance() { return tDistance; }
int Transport::Time() { return tTime; }