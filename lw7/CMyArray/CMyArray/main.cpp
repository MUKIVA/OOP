#include <iostream>
#include "CMyArray.h"
#include <string>
#include <vector>

int main()
{
	CMyArray<int> arr;
	CMyArray<int> arr2;
	// ���������� ��������� � ����� �������
	arr.Append(10);
	arr.Append(20);
	arr.Append(30);
	//arr = arr2;
	// ��������� ���������� ���������
	size_t size = arr.GetSize();
	// ��������� �������� ��� ������ []
		// �����������
	int el2 = arr[2];
		// ��������������
	arr[2] = 40;
	int el2_40 = arr[2];
	//Resize
	arr.Resize(10);
	size = arr.GetSize();
	arr[2];
	arr[4];
	// Clear
	arr.Clear();
	size = arr.GetSize();
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.clear();

    return 0;
}
