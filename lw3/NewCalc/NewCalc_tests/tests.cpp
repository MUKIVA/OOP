#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../NewCalc/Calc.h"
#include "windows.h"
#include <string>
#include <locale>
#include <sstream>

SCENARIO("S")
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::stringstream ss;
	Calc c(ss, std::cout);
	ss << "x=1\n";
	ss << "x2=x+x\n";
	c.HandleAction(CalcAction::LET);
	c.HandleAction(CalcAction::FN);
	for (int i = 3; i <= 1000000; i++)
	{
		ss << "x" << i << "=x" << i - 1 << "+x\n";
		c.HandleAction(CalcAction::FN);
	}
	ss << "x1000000\n";
	c.HandleAction(CalcAction::PRINT);
}