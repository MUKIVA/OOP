#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../Calc/Calc.h"
#include "windows.h"
#include <locale>
#include <sstream>

SCENARIO("Map can be sized and resized")
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	GIVEN("A map with zero items")
	{
		Variables vars;
		WHEN("GetVariable x return NAN")
		{
			double res = vars.GetVariableValue("x");
			REQUIRE(isnan(res));
		}
		WHEN("CreateVariable x return true")
		{
			REQUIRE(vars.CreateVariable("x"));
			double res = vars.GetVariableValue("x");
			REQUIRE(isnan(res));
			REQUIRE_FALSE(vars.CreateVariable("x"));
		}
		WHEN("SetVariable x return true")
		{
			REQUIRE(vars.SetVariable("x", 100));
		}
	}
	GIVEN("A map with one item")
	{
		Variables vars;
		vars.CreateVariable("x");
		double res = vars.GetVariableValue("x");
		REQUIRE(isnan(res));

		WHEN("SetVariable x = 100 return true")
		{
			REQUIRE(vars.SetVariable("x", 100));
			REQUIRE(vars.GetVariableValue("x") == 100);
		}
		WHEN("SetVariable x = 100 return true")
		{
			REQUIRE(vars.SetVariable("x", 100));
		}
		WHEN("SetVariable y = 100 return true")
		{
			REQUIRE(vars.SetVariable("y", 100));
		}
	}
	GIVEN("A map with two items")
	{
		Variables vars;
		vars.CreateVariable("x");
		vars.CreateVariable("y");
		vars.SetVariable("x", 100);
		vars.SetVariable("y", 200);
		REQUIRE(vars.GetVariableValue("x") == 100);
		REQUIRE(vars.GetVariableValue("y") == 200);
		WHEN("SetVariable x = y return true")
		{
			REQUIRE(vars.SetVariable("x", "y"));
			REQUIRE(vars.GetVariableValue("x") == 200);
		}
		WHEN("SetVariable x = z return false")
		{
			REQUIRE_FALSE(vars.SetVariable("x", "z"));
		}
	}
}

SCENARIO("Create functions")
{
	Variables vars;
	REQUIRE_FALSE(vars.SetFn("XPlusY", "x+y"));
	vars.CreateVariable("x");
	REQUIRE_FALSE(vars.SetFn("XPlusY", "x+y"));
	vars.CreateVariable("y");
	GIVEN("Variable can be nan")
	{
		REQUIRE(vars.SetFn("XPlusY", "x+y"));
	}
	GIVEN("Variable can be undefined")
	{
		REQUIRE_FALSE(vars.SetFn("XPlusZ", "x+z"));
	}
	GIVEN("Variable can be only one")
	{
		REQUIRE(vars.SetFn("X", "x"));
	}
	GIVEN("All vars can be seted")
	{
		vars.SetVariable("x", 100);
		vars.SetVariable("y", 200);
		REQUIRE(vars.SetFn("XPlusY", "x+y"));
		REQUIRE(vars.SetFn("XMinusY", "x-y"));
		REQUIRE(vars.SetFn("XMultY", "x*y"));
		REQUIRE(vars.SetFn("XDivY", "x/y"));
		REQUIRE(vars.GetFnValue("XPlusY") == 300);
		REQUIRE(vars.GetFnValue("XMinusY") == -100);
		REQUIRE(vars.GetFnValue("XMultY") == 20000);
		REQUIRE(vars.GetFnValue("XDivY") == 0.5);
		REQUIRE(vars.SetVariable("x", "XPlusY"));
		REQUIRE(vars.SetVariable("z", "x"));
		REQUIRE(vars.GetVariableValue("z") == 300);
		REQUIRE(vars.SetVariable("h", "XPlusY"));
		REQUIRE(vars.GetVariableValue("h") == 500);
	}
}

SCENARIO("fun can use another fun")
{
	Variables vars;
	vars.SetVariable("x", 100);
	vars.SetVariable("y", 200);
	GIVEN("fun can't use undefined func")
	{
		REQUIRE_FALSE(vars.SetFn("XPlusFun", "x+XPlusY"));
	}
	GIVEN("fun can use defined func")
	{
		REQUIRE(vars.SetFn("XPlusY", "x+y"));
		REQUIRE(vars.SetFn("XPlusFun", "x+XPlusY"));
		REQUIRE_FALSE(vars.SetFn("XPlusFun", "x+XPlusY"));
		REQUIRE(vars.SetFn("FunPlusX", "XPlusY+x"));
		REQUIRE_FALSE(vars.SetVariable("XPlusY", 100));
		REQUIRE_FALSE(vars.SetVariable("XPlusY", "x"));
		REQUIRE(vars.GetFnValue("XPlusFun") == 400);
		REQUIRE(vars.GetFnValue("FunPlusX") == 400);
	}
}

SCENARIO("Print vars test")
{
	Variables vars(std::cout);
	vars.CreateVariable("x");
	vars.CreateVariable("y");
	vars.SetFn("XPlusY", "x+y");
	vars.Print("XPlusY");
	vars.SetVariable("x", 100);
	vars.SetVariable("y", 200);
	vars.Print("XPlusY");
	vars.SetFn("XPlusFun", "x+XPlusY");
	vars.SetFn("FunPlusX", "XPlusY+x");
	vars.Print("x");
	vars.Print("z");
	vars.PrintFns();
	vars.PrintVars();
}

SCENARIO("User exp test")
{
	GIVEN("Camman may be unknown")
	{
		std::istringstream iss("asdasd");
		Calc calculator(iss);
		calculator.StartCalculating();
	}
	GIVEN("ќбъ€вление, присваивание и вывод значений переменных")
	{
		std::istringstream iss("var x\nprint x\nlet x=42\nprint x\nlet x=1,234\nlet y=x\nlet x=99\nprintvars");
		Calc calculator(iss);
		calculator.StartCalculating();
	}
	GIVEN("ќбъ€вление функций")
	{
		std::string commands;
		commands.append("var x\n");
		commands.append("var y\n");
		commands.append("fn XPlusY=x+y\n");
		commands.append("print XPlusY\n");
		commands.append("let x=3\n");
		commands.append("let y=4\n");
		commands.append("print XPlusY\n");
		commands.append("let x=10\n");
		commands.append("print XPlusY\n");
		commands.append("let z=3,5\n");
		commands.append("fn XPlusYDivZ=XPlusY/z\n");
		commands.append("printfns\n");
		std::istringstream iss(commands);
		Calc calculator(iss);
		calculator.StartCalculating();
	}
	GIVEN("Ќеверные форматы")
	{
		std::string commands;
		commands.append("fn x\n");
		commands.append("let x\n");
		commands.append("print\n");
		std::istringstream iss(commands);
		Calc calculator(iss);
		calculator.StartCalculating();
	}
	GIVEN("фибоначчи")
	{
		std::string commands;
		commands.append("let v0=0\n");
		commands.append("let v1=1\n");
		commands.append("fn fib0=v0\n");
		commands.append("fn fib1=v1\n");
		commands.append("fn fib2=fib1+fib0\n");
		commands.append("fn fib3=fib2+fib1\n");
		commands.append("fn fib4=fib3+fib2\n");
		commands.append("fn fib5=fib4+fib3\n");
		commands.append("fn fib6=fib5+fib4\n");
		commands.append("fn fib7=fib6+fib5\n");
		commands.append("fn fib8=fib7+fib6\n");
		commands.append("fn fib9=fib8+fib7\n");
		commands.append("fn fib10=fib9+fib8\n");
		commands.append("fn fib11=fib10+fib9\n");
		commands.append("fn fib12=fib11+fib10\n");
		commands.append("fn fib13=fib12+fib11\n");
		commands.append("fn fib14=fib13+fib12\n");
		commands.append("fn fib15=fib14+fib13\n");
		commands.append("fn fib16=fib15+fib14\n");
		commands.append("fn fib17=fib16+fib15\n");
		commands.append("fn fib18=fib17+fib16\n");
		commands.append("fn fib19=fib18+fib17\n");
		commands.append("fn fib20=fib19+fib18\n");
		commands.append("fn fib21=fib20+fib19\n");
		commands.append("fn fib22=fib21+fib20\n");
		commands.append("printfns\n");
		commands.append("let v0=1\n");
		commands.append("let v1=1\n");
		commands.append("printfns\n");
		std::istringstream iss(commands);
		Calc calculator(iss);
		calculator.StartCalculating();
	}
}