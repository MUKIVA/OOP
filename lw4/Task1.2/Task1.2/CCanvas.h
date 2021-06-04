#pragma once
#include "ICanvas.h"

const int DEFAULT_HEIGHT = 1600;
const int DEFAULT_WIDTH = 1600;
//const char* TITLE_NAME = "Canvas";

class CCanvas : public ICanvas
{
public:
	bool WindowShouldClose() const;
	void DisplayData() const;
	void DrawLine(CPoint const& from, CPoint const& to, const std::uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> const& points, const std::uint32_t fillColor) override;
	void DrawCircle(CPoint const& center, const double radius, std::uint32_t lineColor) override;
	void FillCircle(CPoint const& center, const double radius, std::uint32_t fillColor) override;
	CCanvas();
	~CCanvas();

private:
	GLFWwindow* m_window;
	int m_width;
	int m_height;
};