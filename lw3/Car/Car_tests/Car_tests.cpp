#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN

#include "../../../Catch/catch.hpp"

#include "../Car/Car.h"

SCENARIO("Engine is off")
{
	Car lamba;
	REQUIRE(lamba.IsTurnedOn() == false);
	REQUIRE(lamba.SetSpeed(-1) == false);
	
}

SCENARIO("Turn on and Engine is on")
{
	Car lamba;
	REQUIRE(lamba.TurnOnEngine() == true);
	REQUIRE(lamba.IsTurnedOn() == true);
}

SCENARIO("Set gear with engine off")
{
	Car lamba;
	REQUIRE(lamba.SetGear(1) == false);
}

SCENARIO("Set gear with engine on")
{
	Car lamba;
	REQUIRE(lamba.TurnOnEngine() == true);
	REQUIRE(lamba.SetGear(1) == true);
}

SCENARIO("Get Info")
{
	Car lamba;
	REQUIRE(lamba.GetDirection() == 0);
	REQUIRE(lamba.GetGear() == 0);
	REQUIRE(lamba.GetSpeed() == 0);
}

SCENARIO("SetGear EngineOn SetSpeed")
{
	Car lamba;
	REQUIRE(lamba.TurnOnEngine() == true);
	REQUIRE(lamba.SetGear(1) == true);
	REQUIRE(lamba.SetSpeed(30) == true);
	REQUIRE(lamba.TurnOffEngine() == false);
	REQUIRE(lamba.SetGear(5) == false);
	REQUIRE(lamba.SetGear(0) == true);
	REQUIRE(lamba.SetSpeed(0) == true);
	REQUIRE(lamba.TurnOffEngine() == true);
}

SCENARIO("Turn Off Engine")
{
	Car lamba;
	REQUIRE(lamba.TurnOffEngine() == true);
}

SCENARIO("Try reverse")
{
	Car lamba;
	REQUIRE(lamba.TurnOnEngine() == true);
	REQUIRE(lamba.SetGear(-1) == true);
	REQUIRE(lamba.SetSpeed(20) == true);
	REQUIRE(lamba.SetSpeed(150) == false);
}