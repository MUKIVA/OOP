#pragma once
#include <vector>
#include <memory>
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"

class Shapes
{
public:
	void DrawAllData(ICanvas& canvas) const;
	IShape const& FindMaxAreaShape() const;
	IShape const& FindMinPerimeterShape() const;
	bool WriteShape(std::unique_ptr<IShape>& ptr);
	std::size_t GetSize() const;

private:
	std::vector<std::unique_ptr<IShape>> m_shapes;
};