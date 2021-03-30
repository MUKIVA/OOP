#include <vector>
#include <algorithm>
#include "MultiplyByMinimum.h"

FloatVector MultiplyByMinimum(FloatVector& v)
{
	if (v.empty()) 
	{
		return v;
	}
	VectorIterator it;
	float min = *std::min_element(v.begin(), v.end());
	std::transform(v.begin(), v.end(), v.begin(),
		[min](float c) -> float { return c * min; });
	return v;
}