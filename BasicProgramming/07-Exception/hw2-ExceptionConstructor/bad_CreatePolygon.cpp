#include <iostream>
#include "bad_CreatePolygon.h"

bad_CreatePolygon::bad_CreatePolygon(std::string msg): std::exception(msg.c_str()) {};

//const char* bad_CreatePolygon::what() const { return "Ошибка создания фигуры! "; }


