#include <iostream>
#include <locale>
#include <map>
#include "windows.h"
#include "Calc.h"


int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	Calc calc;
	calc.StartCalculating();

	return 0;
}