#pragma once
#include <cstdint>
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual std::uint32_t GetFillColor() const = 0;
	virtual ~ISolidShape() = default;
};
