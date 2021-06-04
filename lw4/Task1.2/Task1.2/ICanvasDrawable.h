#pragma once
#include "ICanvas.h"
// ��� ���� ����� ����������� ����������
// ����� Draw ������ ���� �����������
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;
	virtual ~ICanvasDrawable() = default;
};