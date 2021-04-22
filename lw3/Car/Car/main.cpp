/*
	Исправить ошибку, при которой машина, двигаясь назад, может переключиться на 1 передачу
	Вынести управление машиной в отдельный класс
	Не использовать целочисленные переменные в качестве булевских переменных
	Переименовать состояние двигателя на вопросительную переменную

*/

#include "Car.h"
#include "windows.h"
#include <iostream>
#include <locale>
#include <sstream>
#include <string>

void PrintMsg(std::ostream& os, std::string const& msg)
{
	os << msg << std::endl;
}

enum class Action
{
	INFO,
	ENGINE_ON,
	ENGINE_OFF,
	SET_GEAR,
	SET_SPEED,
};

const std::map<std::string, Action> RequestToAction{
	{ "Info", Action::INFO },
	{ "EngineOn", Action::ENGINE_ON },
	{ "EngineOff", Action::ENGINE_OFF },
	{ "SetGear", Action::SET_GEAR },
	{ "SetSpeed", Action::SET_SPEED },
};

std::string GetEngineStatus(Car& car)
{
	return car.IsTurnedOn() ? "Включен" : "Выключен";
}

std::string GetCarDirection(Car& car)
{
	switch (car.GetDirection())
	{
	case -1:
		return "Назад";
		break;
	case 0:
		return "Стоит на месте";
		break;
	case 1:
		return "Вперед";
		break;
	default:
		break;
	}
}

void PrintCarInfo(std::ostream& os, Car& car)
{
	os << "Speed: " << car.GetSpeed() << std::endl
	   << "Engine status: " << GetEngineStatus(car) << std::endl
	   << "Direction: " << GetCarDirection(car) << std::endl
	   << "Gear: " << car.GetGear() << std::endl;
}

void EngineOn(Car& car)
{
	car.TurnOnEngine();
	PrintMsg(std::cout, "Двигатель включен");
}

void EngineOff(Car& car)
{
	if (!car.GetSpeed() && !car.GetGear())
	{
		car.TurnOffEngine();
		PrintMsg(std::cout, "Двигатель выключен");
	}
	else
	{
		PrintMsg(std::cout, "Скорость и передача должны быть нейтральными");
	}
}

void SetGear(Car& car, int gear)
{
	if (!car.IsTurnedOn())
	{
		PrintMsg(std::cout, "Двигатель выключен");
		return;
	}
	if (gear < MIN_GEAR || gear > MAX_GEAR)
	{
		PrintMsg(std::cout, "Передача вне диапазона от -1 до 5");
		return;
	}
	if (!car.SetGear(gear))
	{
		PrintMsg(std::cout, "Неподходящая скорость");
		return;
	}
	PrintMsg(std::cout, "Переключение удалось");
}

void SetSpeed(Car& car, int speed)
{
	if ((!car.IsTurnedOn() || !car.GetGear()) && speed > car.GetSpeed())
	{
		PrintMsg(std::cout, "На нейтральной передаче или с выключенным двигателем вы можете только тормозить");
		return;
	}
	if (!car.SetSpeed(speed))
	{
		PrintMsg(std::cout, "Неподходящая скорость для текущей передачи");
		return;
	}
	PrintMsg(std::cout, "Изменение скорости удалось");
}

void RequestHandle(Car& car, std::string const& request)
{
	std::istringstream iss(request);
	std::string action;
	iss >> action;
	if (RequestToAction.find(action) == RequestToAction.end())
	{
		PrintMsg(std::cout, "Неизвестная команда");
		return;
	}
	switch (RequestToAction.at(action))
	{
	case Action::INFO:
		PrintCarInfo(std::cout, car);
		break;
	case Action::ENGINE_ON:
		EngineOn(car);
		break;
	case Action::ENGINE_OFF:
		EngineOff(car);
		break;
	case Action::SET_GEAR:
		int gear;
		if (!(iss >> gear))
		{
			PrintMsg(std::cout, "Отсутствует номер передачи");
			break;
		}
		SetGear(car, gear);
		break;
	case Action::SET_SPEED:
		int speed;
		if (!(iss >> speed))
		{
			PrintMsg(std::cout, "Отсутствует значение скорости");
			break;
		}
		SetSpeed(car, speed);
		break;
	default:
		break;
	}
}

void ControllACar(Car& car)
{
	std::string userRequest;
	while (std::getline(std::cin, userRequest))
	{
		RequestHandle(car, userRequest);
	}
}

int main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Car lamba;
	ControllACar(lamba);
	return 0;
}
