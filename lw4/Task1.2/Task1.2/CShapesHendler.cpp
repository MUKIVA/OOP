#include "CShapesHendler.h"
#include <regex>
#include <sstream>
#include <sstream>
#include <optional>

CShapesHandler::CShapesHandler()
	: m_istream(std::cin)
	, m_ostream(std::cout)
{
}

CShapesHandler::CShapesHandler(std::istream& is, std::ostream& os)
	: m_istream(is)
	, m_ostream(os)
{
}

ShapeName CShapesHandler::ParseShapeName(std::string& name)
{
	return (STR_TO_SHAPE.find(name) != STR_TO_SHAPE.end())
		? STR_TO_SHAPE.at(name)
		: ShapeName::NONE;
}

std::optional<std::unique_ptr<IShape>> ParseRectangle(std::istream& is)
{
	CPoint leftTop;
	CPoint rightBottom;
	std::uint32_t outlineColor;
	std::uint32_t fillColor;

	if (!(is >> leftTop.x >> leftTop.y
			>> rightBottom.x >> rightBottom.y
			>> std::hex >> outlineColor
			>> std::hex >> fillColor))
	{
		return std::nullopt;
	}
	std::unique_ptr<IShape> rect(new CRectangle(
		leftTop, rightBottom, outlineColor, fillColor
	));
	return rect;
}

std::optional<std::unique_ptr<IShape>> ParseCircle(std::istream& is)
{
	CPoint center;
	double radius;
	std::uint32_t outlineColor = 0;
	std::uint32_t fillColor = 0;
	if (!(is >> center.x >> center.y
			>> radius
			>> std::hex >> outlineColor >> fillColor))
	{
		return std::nullopt;
	} 
	std::unique_ptr<IShape> circle(new CCircle(
		center, radius, outlineColor, fillColor)
	);
	return circle;
}

std::optional<std::unique_ptr<IShape>> ParseTriangle(std::istream& is)
{
	CPoint p1, p2, p3;
	std::uint32_t outlineColor = 0;
	std::uint32_t fillColor = 0;
	if (!(is >> p1.x >> p1.y
			>> p2.x >> p2.y
			>> p3.x >> p3.y
			>> std::hex >> outlineColor >> fillColor))
	{
		return std::nullopt;
	}
	std::unique_ptr<IShape> triangle(new CTriangle(
		p1, p2, p3, outlineColor, fillColor)
	);
	return triangle;
}

std::optional<std::unique_ptr<IShape>> ParseLineSegment(std::istream& is)
{
	CPoint start, end;
	std::uint32_t outlineColor;
	if (!(is >> start.x >> start.y
			>> end.x >> end.y
			>> std::hex >> outlineColor))
	{
		return std::nullopt;
	}
	std::unique_ptr<IShape> line(new CLineSegment(
		start, end, outlineColor)
	);
	return line;
}

bool CShapesHandler::HandleInsert(std::istream& is, ShapeName name, Shapes& shapes)
{
	switch (name)
	{
	case ShapeName::CIRCLE: {	
		auto circle = ParseCircle(is);
		if (circle)
		{
			shapes.WriteShape(*circle);
		}
		else
		{
			return false;
		}
	}
		break;
	case ShapeName::TRIANGLE: {
		auto triangle = ParseTriangle(is);
		if (triangle)
		{
			shapes.WriteShape(*triangle);
		}
		else
		{
			return false;
		}
	}
		break;
	case ShapeName::RECTANGLE: {
		auto rectangle = ParseRectangle(is); 
		if (rectangle)
		{
			shapes.WriteShape((*rectangle));
		}
		else
		{
			return false;
		}
	}
		break;
	case ShapeName::LINESEGMENT: {
		auto line = ParseLineSegment(is);
		if (line)
		{
			shapes.WriteShape(*line);
		}
		else
		{
			return false;
		}
	}
		break;
	default:
		break;
	}
	return true;
}

bool CShapesHandler::HandleOperation(std::string const& operation, Shapes& shapes)
{
	std::stringstream ss(operation);
	std::string shapeName;
	ss >> shapeName;
	ShapeName name = ParseShapeName(shapeName);
	if (name != ShapeName::NONE)
	{
		HandleInsert(ss, name, shapes);
		return true;
	}
	return false;
}

void CShapesHandler::Handeling(Shapes& shapes)
{
	std::string operation;
	while (getline(m_istream, operation))
	{
		HandleOperation(operation, shapes);
	}
}