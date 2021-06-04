#pragma once
#include "CPoint.h"
#include <string>
#include <cstdint>
#include <vector>
#include <math.h>
#include <GLFW/glfw3.h>
// Добавить виртуальный диструктор


class ICanvas
{
public:
	virtual void DrawLine(CPoint const& from, CPoint const& to, const std::uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> const& points, const std::uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint const& center, const double radius, std::uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint const& center, const double radius, std::uint32_t fillColor) = 0;
};