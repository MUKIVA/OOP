#include <iostream>
#include <string>
#include <locale>
#include "Calc.h"
#include "windows.h"

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Calc calculator;
	calculator.StartCalculating();
}