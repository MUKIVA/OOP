#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../NCalc/Calc.h"
#include "windows.h"
#include <fstream>
#include <locale>
#include <optional>
#include <sstream>

SCENARIO("Variables tests")
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	GIVEN("Is empty")
	{
		Variables v;
		REQUIRE(v.CreateVar("x"));
		REQUIRE(v.SetFn("X", "x", "", nullptr));
		REQUIRE_FALSE(v.CreateVar("X"));
	}

	GIVEN("Is not empty | Set test")
	{
		Variables v;
		REQUIRE(v.CreateVar("x"));
		REQUIRE(v.CreateVar("y"));
		REQUIRE(v.SetVar("x", 100));
		REQUIRE(v.GetVarValue("x") == 100);
		REQUIRE_FALSE(v.GetVarValue("z"));
		REQUIRE(v.SetVar("y", "x"));
		REQUIRE(v.GetVarValue("y") == 100);
		REQUIRE(v.SetVar("x", 200));
		REQUIRE(v.GetVarValue("y") == 100);
		REQUIRE(v.GetVarValue("x") == 200);
		REQUIRE_FALSE(v.GetFnValue("X"));
		REQUIRE(v.SetFn("X", "x", "", nullptr));
		REQUIRE(v.GetFnValue("X") == 200);
		REQUIRE_FALSE(v.SetVar("X", 200));
		REQUIRE_FALSE(v.SetVar("X", "y"));
		REQUIRE_FALSE(v.SetVar("x", "x"));
		REQUIRE(v.SetVar("y", "X"));
		REQUIRE_FALSE(v.SetVar("y", "z"));
		REQUIRE_FALSE(v.SetFn("X", "x", "y", Plus));
		REQUIRE_FALSE(v.SetFn("XPusY", "z", "y", Plus));
		REQUIRE_FALSE(v.SetFn("XPusY", "x", "z", Plus));
		REQUIRE(v.SetFn("XPusY", "x", "y", Plus));
		REQUIRE(v.SetFn("RF", "x", "XPusY", Plus));
		REQUIRE(v.SetFn("LF", "XPusY", "y", Plus));
		REQUIRE(v.SetFn("Z", "RF", "", nullptr));
		REQUIRE(v.SetVar("x", 300));
	}

	GIVEN("Is not empty | operation check")
	{
		Variables v;
		REQUIRE(v.CreateVar("x"));
		REQUIRE(v.CreateVar("y"));
		REQUIRE(v.SetVar("x", 100));
		REQUIRE(v.SetVar("y", 200));
		REQUIRE(v.GetVarValue("x") == 100);
		REQUIRE(v.GetVarValue("y") == 200);
		REQUIRE(v.SetFn("XPusY", "x", "y", Plus));
		REQUIRE(v.SetFn("XMinusY", "x", "y", Minus));
		REQUIRE(v.SetFn("XMultY", "x", "y", Multiply));
		REQUIRE(v.SetFn("XDivY", "x", "y", Divide));
		REQUIRE(v.GetFnValue("XPusY") == 300);
		REQUIRE(v.GetFnValue("XMinusY") == -100);
		REQUIRE(v.GetFnValue("XMultY") == 20000);
		REQUIRE(v.GetFnValue("XDivY") == 0.5);
	}
}

SCENARIO("Calc tests")
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WHEN("Calc()")
	{
		Calc c;
	}

	WHEN("Calc(is, os)")
	{
		std::stringstream ss;
		Calc c(ss, std::cout);
		GIVEN("Checking basic functions")
		{
			ss << "var x\n";
			ss << "let x=42\n";
			ss << "fn X=x\n";
			ss << "fn Y=y\n";
			ss << "let y=x\n";
			ss << "printvars\n";
			ss << "printfns\n";
			ss << "print z\n";
			ss << "print x\n";
			ss << "print X\n";
			ss << "print\n";
			c.StartCalculating();
		}
	}
}

SCENARIO("Perfomance tests")
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WHEN("Fibonacci numbers");
	{
		std::ifstream ifs("Fib.txt");
		REQUIRE(ifs.is_open());
		Calc c(ifs);
		c.StartCalculating();
	}
	/*WHEN("Big queue fn")
	{
		std::ifstream ifs("BigQ.txt");
		REQUIRE(ifs.is_open());
		Calc c(ifs);
		c.StartCalculating();
	}*/
}
