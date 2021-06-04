#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <cstdint>
#include <string>

class CCircle : public ISolidShape
{
public:
	void Draw(ICanvas& canvas) override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::uint32_t GetFillColor() const override;
	std::uint32_t GetOutlineColor() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	bool SetCenter(const CPoint& point);
	bool SetRadius(const double radius);
	bool SetOutlineColor(const std::uint32_t color);
	bool SetFillColor(const std::uint32_t color); 
	CCircle();
	CCircle(CPoint center, double radius, std::uint32_t outlineColor, std::uint32_t fillColor);

private:
	double m_radius = 0;
	CPoint m_center;
	std::uint32_t m_outlineColor = 0;
	std::uint32_t m_fillColor = 0;
};