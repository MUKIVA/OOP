#pragma once
#include "CPoint.h"
#include "IShape.h"
#include <string>
#include <cstdint>

class CLineSegment : public IShape
{
public:
	void Draw(ICanvas& canvas) override;
	std::string ToString() const override;
	double GetArea() const override { return 0; };
	double GetPerimeter() const override { return 0; };
	std::uint32_t GetOutlineColor() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	bool SetStartPoint(CPoint const& point);
	bool SetEndPoint(CPoint const& point);
	bool SetOutlineColor(const std::uint32_t color);
	CLineSegment();
	CLineSegment(CPoint start, CPoint end, std::uint32_t outlineColor);

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	std::uint32_t m_outlineColor = 0;
};
