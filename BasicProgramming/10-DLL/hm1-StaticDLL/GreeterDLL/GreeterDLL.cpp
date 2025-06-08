#include <iostream>
#include <string>
#include "GreeterDLL.h"

std::string Greeter::greet(std::string name) {
	return "Здравствуйте, " + name+ "!";
}
