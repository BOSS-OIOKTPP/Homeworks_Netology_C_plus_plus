#include <iostream>
#include <string>
#include "Polygon.h"


TPolygon::TPolygon() : FSides(0), FName("Фигура") {}
int TPolygon::GetSides() { return FSides; }
std::string TPolygon::GetName() { return FName; }
bool TPolygon::Check(std::string& Err) { Err = ""; return true; }
void TPolygon::Print() {
    std::cout << GetName() + " ( " << "cтороны" << GetSides() << " ) создан" << std::endl;
}
