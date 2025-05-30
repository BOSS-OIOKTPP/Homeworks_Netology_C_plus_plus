#include <iostream>
#include <string>
#include "Polygon.h"


TPolygon::TPolygon() : FSides(0), FName("Фигура") {}
int TPolygon::GetSides() { return FSides; }
std::string TPolygon::GetName() { return FName; }
void TPolygon::Print() {
    std::cout << GetName() + " ( " << "cтороны" << GetSides() << " ) создан" << std::endl;
}
