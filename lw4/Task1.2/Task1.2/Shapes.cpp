#include "CShapes.h"
#include <algorithm>

IShape const& Shapes::FindMaxAreaShape() const
{
	if (m_shapes.size() == 0)
	{
		return CLineSegment();
	}
	auto const el = std::max_element(m_shapes.begin(), m_shapes.end(), 
	[](std::unique_ptr<IShape> const& a, std::unique_ptr<IShape> const& b)
	{
		return (*a).GetArea() < (*b).GetArea();
	});
	return **el;
}

IShape const& Shapes::FindMinPerimeterShape() const
{
	if (m_shapes.size() == 0)
	{
		return CLineSegment();
	}
	auto el = std::min_element(m_shapes.begin(), m_shapes.end(), 
	[](std::unique_ptr<IShape> const& a, std::unique_ptr<IShape> const& b) 
	{
		ISolidShape const* solidShapeA = dynamic_cast<ISolidShape const*>(&*a);
		ISolidShape const* solidShapeB = dynamic_cast<ISolidShape const*>(&*b);
		if (!solidShapeA || !solidShapeB)
		{
			return false;
		}
		return (*a).GetPerimeter() < (*b).GetPerimeter();
	});
	return **el;
}

bool Shapes::WriteShape(std::unique_ptr<IShape>& ptr)
{
	m_shapes.resize(m_shapes.size() + 1);
	m_shapes.at(m_shapes.size() - 1).swap(ptr);
	return true;
}

void Shapes::DrawAllData(ICanvas& canvas) const
{
	for (auto& ptr : m_shapes)
	{
		ptr.get()->Draw(canvas);
	}
}

std::size_t Shapes::GetSize() const
{
	return m_shapes.size();
}