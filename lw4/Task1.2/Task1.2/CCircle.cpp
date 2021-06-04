#include "CCircle.h"
#include <iomanip>
#include <sstream>

const double PI = 3.14159265;



double CCircle::GetRadius() const { return m_radius; }

CPoint CCircle::GetCenter() const { return m_center; }

std::uint32_t CCircle::GetOutlineColor() const { return m_outlineColor; }

std::uint32_t CCircle::GetFillColor() const { return m_fillColor; }

std::string CCircle::ToString() const 
{
	std::string info;
	info.append("Shape name: ").append("Circle\n");
	info.append("\tCenter: ")
		.append("X:").append(std::to_string(m_center.x))
		.append(" Y:").append(std::to_string(m_center.y))
		.append("\n");
	info.append("\tRadius: ").append(std::to_string(m_radius)).append("\n");
	return info;
}

double CCircle::GetPerimeter() const
{
	return 2 * PI * m_radius;
}

double CCircle::GetArea() const
{
	return PI * m_radius * m_radius;
}

bool CCircle::SetCenter(CPoint const& point)
{
	m_center = point;
	return true;
}

bool CCircle::SetRadius(const double radius)
{
	m_radius = radius;
	return true;
}

bool CCircle::SetFillColor(const std::uint32_t color)
{
	m_fillColor = color;
	return true;
}

bool CCircle::SetOutlineColor(const std::uint32_t color)
{
	m_outlineColor = color;
	return true;
}

CCircle::CCircle()
{
}

CCircle::CCircle(CPoint center, double radius, std::uint32_t outlineColor, std::uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

void CCircle::Draw(ICanvas& canvas)
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}