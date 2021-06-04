#include "CRectangle.h"

CPoint CRectangle::GetLeftTop() const { return m_leftTop; }

CPoint CRectangle::GetRightBottom() const { return m_rightBottom; }

std::uint32_t CRectangle::GetOutlineColor() const { return m_outlineColor; }

std::uint32_t CRectangle::GetFillColor() const { return m_fillColor; }

std::string CRectangle::ToString() const
{
	std::string info;
	info.append("Shape name: ").append("Rectangle\n");
	info.append("\tLeft top: ")
		.append("X:").append(std::to_string(m_leftTop.x))
		.append(" Y:").append(std::to_string(m_leftTop.y))
		.append("\n");
	info.append("\tRight bottom: ")
		.append("X:").append(std::to_string(m_rightBottom.x))
		.append(" Y:").append(std::to_string(m_rightBottom.y))
		.append("\n");
	return info;
}

double CRectangle::GetHeight() const
{
	return abs(m_leftTop.y - m_rightBottom.y);
}

double CRectangle::GetWidth() const
{
	return abs(m_rightBottom.x - m_leftTop.x);
}

double CRectangle::GetArea() const
{
	return GetHeight() * GetWidth();
}

double CRectangle::GetPerimeter() const
{
	return (GetHeight() + GetWidth()) * 2;
}

bool CRectangle::SetFillColor(const std::uint32_t color)
{
	m_fillColor = color;
	return true;
}

bool CRectangle::SetOutlineColor(const std::uint32_t color)
{
	m_outlineColor = color;
	return true;
}

bool CRectangle::SetLeftTop(CPoint const& point)
{
	m_leftTop = point;
	return true;
}

bool CRectangle::SetRightBottom(CPoint const& point)
{
	m_rightBottom = point;
	return true;
}

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, std::uint32_t outlineColor, std::uint32_t fillColor)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)

{
}

CRectangle::CRectangle() {}

void CRectangle::Draw(ICanvas& canvas)
{
	std::vector<CPoint> points;
	points.push_back({ m_leftTop.x, m_leftTop.y });
	points.push_back({ m_rightBottom.x, m_leftTop.y });
	points.push_back({ m_rightBottom.x, m_rightBottom.y });
	points.push_back({ m_leftTop.x, m_rightBottom.y });
	canvas.FillPolygon(points, m_fillColor);
}