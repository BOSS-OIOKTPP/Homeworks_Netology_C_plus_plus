#include <iostream>
#include <string>
#include "Polygon.h"


TPolygon::TPolygon() : FSides(0), FName("������") {}
int TPolygon::GetSides() { return FSides; }
std::string TPolygon::GetName() { return FName; }
void TPolygon::Print() {
    std::cout << GetName() + " :" << std::endl;
    std::cout << "���������� ������ : " << GetSides() << std::endl;
    std::cout << std::endl;    
}
