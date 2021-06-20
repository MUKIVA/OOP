#include <iostream>
#include "CMyArray.h"
#include <string>
#include <vector>

CMyArray<int> GetArray()
{
	CMyArray<int> result;
	result.Append(3);
	result.Append(4);
	result.Append(5);
	result.Append(6);
	return result;
}

int main()
{
	CMyArray<int> arr;
	CMyArray<int> arr2;
	arr2.Append(1);
	arr2.Append(2);
	arr2.Append(3);
	int size1 = arr.GetSize();
	int size2 = arr2.GetSize();
	arr = arr2;
	size1 = arr.GetSize();
	size2 = arr2.GetSize();
	std::vector<int> s;
	s.back();
	arr = GetArray();
	size1 = arr.GetSize();
//	int back = arr.GetBack();
    return 0;
}
