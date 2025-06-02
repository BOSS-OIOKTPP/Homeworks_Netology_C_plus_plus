#pragma once
#include <iostream>

class bad_CreatePolygon : public std::exception {
public:
	bad_CreatePolygon(std::string msg);
};