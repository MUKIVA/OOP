#pragma once
#include "CPoint.h"
#include "ISolidShape.h"
#include <string>
#include <cstdint>

class CRectangle : public ISolidShape
{
public:
	void Draw(ICanvas& canvas) override;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	std::uint32_t GetFillColor() const override;
	std::uint32_t GetOutlineColor() const override;
	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	bool SetLeftTop(CPoint const& point);
	bool SetRightBottom(CPoint const& point);
	bool SetOutlineColor(const std::uint32_t color);
	bool SetFillColor(const std::uint32_t color);
	CRectangle(CPoint leftTop, CPoint rightBottom, std::uint32_t outlineColor, std::uint32_t fillColor);
	CRectangle();

private:
	CPoint m_leftTop;
	CPoint m_rightBottom;
	std::uint32_t m_outlineColor = 0;
	std::uint32_t m_fillColor = 0;
};
