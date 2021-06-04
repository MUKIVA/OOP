#include <iostream>
#include <locale>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "CCanvas.h"
#include "CShapes.h"
#include "CShapesHendler.h"
#include "windows.h"
#include <optional>

bool DisplayShapeData(Shapes const& data)
{
	CCanvas canvas;
	data.DrawAllData(canvas);
	canvas.DisplayData();
	while (!canvas.WindowShouldClose()) { }
	return true;
}

std::string PrintMaxAreaShapeInfo(std::ostream& os, Shapes const& data)
{
	if (data.GetSize() == 0)
	{
		return "";
	}
	IShape const& shape = data.FindMaxAreaShape();
	ISolidShape const* solidShape = dynamic_cast<ISolidShape const*>(&shape);
	std::string msg;
	msg.append(shape.ToString());
	if (solidShape)
	{
		msg.append("\tPerimeter: ")
			.append(std::to_string(solidShape->GetPerimeter()))
			.append("\n");
		msg.append("\tArea: ")
			.append(std::to_string(solidShape->GetArea()))
			.append("\n");
		msg.append("\tFill color: ")
			.append(ColorToString(solidShape->GetFillColor()))
			.append("\n");
	}
	msg.append("\tOutline color: ")
		.append(ColorToString(shape.GetOutlineColor()))
		.append("\n");
	os << msg; 
	return msg;
}

std::string PrintMinPerimeterShapeInfo(std::ostream& os, Shapes const& data)
{
	if (data.GetSize() == 0)
	{
		return "";
	}
	IShape const& shape = data.FindMinPerimeterShape();
	ISolidShape const* solidShape = dynamic_cast<ISolidShape const*>(&shape);
	std::string msg;
	msg.append(shape.ToString());
	if (solidShape)
	{
		msg.append("\tPerimeter: ")
			.append(std::to_string(solidShape->GetPerimeter()))
			.append("\n");
		msg.append("\tArea: ")
			.append(std::to_string(solidShape->GetArea()))
			.append("\n");
		msg.append("\tFill color: ")
			.append(ColorToString(solidShape->GetFillColor()))
			.append("\n");
	}
	msg.append("\tOutline color: ")
		.append(ColorToString(shape.GetOutlineColor()))
		.append("\n");
	os << msg;
	return msg;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CShapesHandler handler;
	Shapes data;
	std::string operation;
	while (getline(std::cin, operation))
	{
		handler.HandleOperation(operation, data);
	}
	PrintMaxAreaShapeInfo(std::cout, data);
	PrintMinPerimeterShapeInfo(std::cout, data);
	DisplayShapeData(data);
	return 0;
}