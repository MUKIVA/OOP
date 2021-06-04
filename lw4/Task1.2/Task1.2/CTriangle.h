#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <string>

class CTriangle : public ISolidShape
{
public:
	void Draw(ICanvas& canvas) override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;
	std::uint32_t GetFillColor() const override;
	std::uint32_t GetOutlineColor() const override;
	bool SetOutlineColor(const std::uint32_t color);
	bool SetFillColor(const std::uint32_t color);
	bool SetVertex1(CPoint const& point);
	bool SetVertex2(CPoint const& point);
	bool SetVertex3(CPoint const& point);
	CTriangle();
	CTriangle(CPoint p1, CPoint p2, CPoint p3, std::uint32_t outlineColor, std::uint32_t fillColor);

private:
	CPoint m_p1;
	CPoint m_p2;
	CPoint m_p3;
	std::uint32_t m_outlineColor = 0;
	std::uint32_t m_fillColor = 0;
};
