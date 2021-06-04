#pragma once
#include "ICanvas.h"
// Для чего нужен виртуальный диструктор
// Метод Draw должен быть константным
class ICanvasDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;
	virtual ~ICanvasDrawable() = default;
};