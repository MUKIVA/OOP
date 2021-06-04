#include "CCanvas.h"
#include <math.h>

//Ñircle quality
const int STEPS = 100;
const double ANGLE = 3.1415926 * 2.f / STEPS;


void CCanvas::FillPolygon(std::vector<CPoint> const& points, const std::uint32_t fillColor)
{
	if (glfwWindowShouldClose(m_window))
	{
		return;
	}
	glBegin(GL_POLYGON);
	double r = (double)((fillColor >> 16) & 0xff) / 255;
	double g = (double)((fillColor >> 8) & 0xff) / 255;
	double b = (double)((fillColor >> 0) & 0xff) / 255;
	glColor3d(r, g, b);
	
	for (CPoint const& point : points)
	{
		glVertex2d((point.x / m_width), (point.y / m_height));
	}
	glEnd();
	return;
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to, const std::uint32_t lineColor)
{
	if (glfwWindowShouldClose(m_window))
	{
		return;
	}
	glLineWidth(4);
	glBegin(GL_LINES);

	double r = (double)((lineColor >> 16) & 0xff) / 255;
	double g = (double)((lineColor >> 8) & 0xff) / 255;
	double b = (double)((lineColor >> 0) & 0xff) / 255;
	glColor3d(r, g, b);

	glVertex2d((from.x / m_width), (from.y / m_height));
	glVertex2d((to.x / m_width), (to.y / m_height));
	glEnd();
	return;
}

void CCanvas::DrawCircle(CPoint const& center, const double radius, std::uint32_t lineColor)
{
	if (glfwWindowShouldClose(m_window))
	{
		return;
	}
	glLineWidth(4);
	glBegin(GL_LINES);
	
	const double CANVAS_CENTER_X = center.x / m_width;
	const double CANVAS_CENTER_Y = center.y / m_height;
	const double RADIUS_PROJECTION_ONTO_CANVAS_X = radius / m_width;
	const double RADIUS_PROJECTION_ONTO_CANVAS_Y = radius / m_height;

	double r = (double)((lineColor >> 16) & 0xff) / 255;
	double g = (double)((lineColor >> 8) & 0xff) / 255;
	double b = (double)((lineColor >> 0) & 0xff) / 255;
	glColor3d(r, g, b);

	double prevX = CANVAS_CENTER_X;
	double prevY = CANVAS_CENTER_Y - RADIUS_PROJECTION_ONTO_CANVAS_Y;
	for (int i = 0; i <= STEPS; i++)
	{
		double newX = RADIUS_PROJECTION_ONTO_CANVAS_X * sin(ANGLE * i) + CANVAS_CENTER_X;
		double newY = -RADIUS_PROJECTION_ONTO_CANVAS_Y * cos(ANGLE * i) + CANVAS_CENTER_Y;
		glVertex2d(prevX, prevY);
		glVertex2d(newX, newY);
		prevX = newX;
		prevY = newY;
	}
	glEnd();
	return;
}

void CCanvas::FillCircle(CPoint const& center, const double radius, std::uint32_t fillColor)
{
	if (glfwWindowShouldClose(m_window))
	{
		return;
	}
	glBegin(GL_POLYGON);

	const double CANVAS_CENTER_X = center.x / m_width;
	const double CANVAS_CENTER_Y = center.y / m_height;
	const double RADIUS_PROJECTION_ONTO_CANVAS_X = radius / m_width;
	const double RADIUS_PROJECTION_ONTO_CANVAS_Y = radius / m_height;

	double r = (double)((fillColor >> 16) & 0xff) / 255;
	double g = (double)((fillColor >> 8) & 0xff) / 255;
	double b = (double)((fillColor >> 0) & 0xff) / 255;
	glColor3d(r, g, b);

	for (int i = 0; i <= STEPS; i++)
	{
		double newX = RADIUS_PROJECTION_ONTO_CANVAS_X * sin(ANGLE * i) + CANVAS_CENTER_X;
		double newY = -RADIUS_PROJECTION_ONTO_CANVAS_Y * cos(ANGLE * i) + CANVAS_CENTER_Y;
		glVertex2d(newX, newY);
	}
	glEnd();
	return;
}

CCanvas::CCanvas()
{
	glfwInit();
	m_window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Canvas", NULL, NULL);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwMakeContextCurrent(m_window);
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

CCanvas::~CCanvas()
{
	glfwTerminate();
}

bool CCanvas::WindowShouldClose() const
{
	glfwPollEvents();
	return glfwWindowShouldClose(m_window);
}

void CCanvas::DisplayData() const
{
	glfwSwapBuffers(m_window);
	glClear(GL_COLOR_BUFFER_BIT);
}