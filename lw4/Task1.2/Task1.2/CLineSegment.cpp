#include "CLineSegment.h"
#include <iostream>

std::uint32_t CLineSegment::GetOutlineColor() const { return m_outlineColor; }

CPoint CLineSegment::GetStartPoint() const { return m_startPoint; }

CPoint CLineSegment::GetEndPoint() const { return m_endPoint; }

bool CLineSegment::SetStartPoint(CPoint const& point)
{
	m_startPoint = point;
	return true;
}

bool CLineSegment::SetEndPoint(CPoint const& point)
{
	m_endPoint = point;
	return true;
}

bool CLineSegment::SetOutlineColor(const std::uint32_t color)
{
	m_outlineColor = color;
	return true;
}

CLineSegment::CLineSegment()
{
}

CLineSegment::CLineSegment(CPoint start, CPoint end, std::uint32_t outlineColor)
	: m_startPoint(start)
	, m_endPoint(end)
	, m_outlineColor(outlineColor)
{
}

void CLineSegment::Draw(ICanvas& canvas)
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}

std::string CLineSegment::ToString() const
{
	std::string info;
	info.append("Shape name: ").append("Line segment\n");
	info.append("\tStart point: ")
		.append("X:").append(std::to_string(m_startPoint.x))
		.append(" Y:").append(std::to_string(m_startPoint.y))
		.append("\n");
	info.append("\tEnd point: ")
		.append("X:").append(std::to_string(m_endPoint.x))
		.append(" Y:").append(std::to_string(m_endPoint.y))
		.append("\n");
	return info;
}