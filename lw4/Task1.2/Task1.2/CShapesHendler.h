#pragma once
#include "CShapes.h"
#include <map>
#include <string>
#include <iostream>
#include <optional>

enum class ShapeName
{
	NONE,
	CIRCLE,
	TRIANGLE,
	RECTANGLE,
	LINESEGMENT,
};

const std::map<std::string, ShapeName> STR_TO_SHAPE({
	{ "circle", ShapeName::CIRCLE },
	{ "triangle", ShapeName::TRIANGLE },
	{ "rectangle", ShapeName::RECTANGLE },
	{ "linesegment", ShapeName::LINESEGMENT }

});

class CShapesHandler
{
public:
	CShapesHandler();
	CShapesHandler(std::istream& is, std::ostream& os);
	bool HandleOperation(std::string const& operation, Shapes& shapes);
	void Handeling(Shapes& shapes);

private:
	ShapeName ParseShapeName(std::string& name);
	bool HandleInsert(std::istream& is, ShapeName name, Shapes& shapes);
	std::istream& m_istream;
	std::ostream& m_ostream;
};