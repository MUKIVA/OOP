#pragma once
#include <cstdint>
#include <string>
#include "CPoint.h"
#include "ICanvasDrawable.h"

std::string ColorToString(std::uint32_t num);

class IShape : public ICanvasDrawable
{
public:
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const { return ""; }
	virtual std::uint32_t GetOutlineColor() const = 0;
	virtual ~IShape() = default;
};
