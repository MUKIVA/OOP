#include "Calc.h"
#include "windows.h"
#include <fstream>
#include <locale>
#include <string>

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream ifs("BigQ.txt");

	Calc c(ifs);
	c.StartCalculating();
}
