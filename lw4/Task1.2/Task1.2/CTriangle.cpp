#include "CTriangle.h"

std::uint32_t CTriangle::GetOutlineColor() const { return m_outlineColor; }

std::uint32_t CTriangle::GetFillColor() const { return m_fillColor; }

CPoint CTriangle::GetVertex1() const { return m_p1; }

CPoint CTriangle::GetVertex2() const { return m_p2; }

CPoint CTriangle::GetVertex3() const { return m_p3; }

std::string CTriangle::ToString() const
{
	std::string info;
	info.append("Shape name: ").append("Triangle\n");
	info.append("\tP1: ")
		.append("X:").append(std::to_string(m_p1.x))
		.append(" Y:").append(std::to_string(m_p1.y))
		.append("\n");
	info.append("\tP2: ")
		.append("X:").append(std::to_string(m_p2.x))
		.append(" Y:").append(std::to_string(m_p2.y))
		.append("\n");
	info.append("\tP3: ")
		.append("X:").append(std::to_string(m_p3.x))
		.append(" Y:").append(std::to_string(m_p3.y))
		.append("\n");
	return info;
}

double CTriangle::GetArea() const
{
	return abs(0.5 * (((m_p1.x - m_p3.x) * (m_p2.y - m_p3.y)) - ((m_p2.x - m_p3.x) * (m_p1.y - m_p3.y))));
}

double CTriangle::GetPerimeter() const
{
	return sqrt(pow(m_p1.x - m_p2.x, 2) + pow(m_p1.y - m_p2.y, 2))
		+ sqrt(pow(m_p2.x - m_p3.x, 2) + pow(m_p2.y - m_p3.y, 2))
		+ sqrt(pow(m_p3.x - m_p1.x, 2) + pow(m_p3.y - m_p1.y, 2));
}

bool CTriangle::SetFillColor(const std::uint32_t color)
{
	m_fillColor = color;
	return true;
}

bool CTriangle::SetOutlineColor(const std::uint32_t color)
{
	m_outlineColor = color;
	return true;
}

bool CTriangle::SetVertex1(CPoint const& point)
{
	m_p1 = point;
	return true;
}

bool CTriangle::SetVertex2(CPoint const& point)
{
	m_p2 = point;
	return true;
}

bool CTriangle::SetVertex3(CPoint const& point)
{
	m_p3 = point;
	return true;
}

CTriangle::CTriangle()
{
}

CTriangle::CTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outlineColor, std::uint32_t fillColor)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

void CTriangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> points;
	points.push_back({ m_p1.x, m_p1.y });
	points.push_back({ m_p2.x, m_p2.y });
	points.push_back({ m_p3.x, m_p3.y });
	canvas.FillPolygon(points, m_fillColor);
}