#define CATCH_CONFIG_MAIN

#include <sstream>

#include "../../fakeIt/single_header/catch/fakeit.hpp"


#include "../Task1.2/CCanvas.h"
#include "../Task1.2/CCircle.h"
#include "../Task1.2/CTriangle.h"
#include "../Task1.2/CRectangle.h"
#include "../Task1.2/CLineSegment.h"
#include "../Task1.2/CShapes.h"
#include "../Task1.2/CShapesHendler.h"
#include "windows.h"

SCENARIO("CCircle tests")
{
	GIVEN("CCircle: empty constructor")
	{
		CCircle c;
		REQUIRE(c.GetArea() == 0);
		REQUIRE(c.GetPerimeter() == 0);
		REQUIRE(c.GetFillColor() == 0);
		REQUIRE(c.GetOutlineColor() == 0);
		REQUIRE(c.GetRadius() == 0);
		REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));

		WHEN("Set new center")
		{
			REQUIRE(c.SetCenter({100, 100}));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 100 && c.GetCenter().y == 100));
		}

		WHEN("Set new radius")
		{
			REQUIRE(c.SetRadius(10));
			REQUIRE(c.GetArea() == 314.159265);
			REQUIRE(c.GetPerimeter() == 62.831853);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 10);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Set new fill color")
		{
			REQUIRE(c.SetFillColor(0x0000001));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 1);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Set new outline color")
		{
			REQUIRE(c.SetOutlineColor(0x0000001));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 1);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Get info")
		{
			std::string require("Shape name: Circle\n\tCenter: X:0.000000 Y:0.000000\n\tRadius: 0.000000\n");
			REQUIRE(c.ToString() == require);
		}
	}

	GIVEN("CCircle: set constructor")
	{
		CCircle c({0, 0}, 0, 0, 0);
		REQUIRE(c.GetArea() == 0);
		REQUIRE(c.GetPerimeter() == 0);
		REQUIRE(c.GetFillColor() == 0);
		REQUIRE(c.GetOutlineColor() == 0);
		REQUIRE(c.GetRadius() == 0);
		REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));

		WHEN("Set new center")
		{
			REQUIRE(c.SetCenter({ 100, 100 }));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 100 && c.GetCenter().y == 100));
		}

		WHEN("Set new radius")
		{
			REQUIRE(c.SetRadius(10));
			REQUIRE(c.GetArea() == 314.159265);
			REQUIRE(c.GetPerimeter() == 62.831853);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 10);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Set new fill color")
		{
			REQUIRE(c.SetFillColor(0x0000001));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 1);
			REQUIRE(c.GetOutlineColor() == 0);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Set new outline color")
		{
			REQUIRE(c.SetOutlineColor(0x0000001));
			REQUIRE(c.GetArea() == 0);
			REQUIRE(c.GetPerimeter() == 0);
			REQUIRE(c.GetFillColor() == 0);
			REQUIRE(c.GetOutlineColor() == 1);
			REQUIRE(c.GetRadius() == 0);
			REQUIRE((c.GetCenter().x == 0 && c.GetCenter().y == 0));
		}

		WHEN("Get info")
		{
			std::string require("Shape name: Circle\n\tCenter: X:0.000000 Y:0.000000\n\tRadius: 0.000000\n");
			REQUIRE(c.ToString() == require);
		}
	}
}

SCENARIO("CTriangle tests")
{
	GIVEN("Empty constructor")
	{
		CTriangle t;
		REQUIRE(t.GetArea() == 0);
		REQUIRE(t.GetFillColor() == 0);
		REQUIRE(t.GetOutlineColor() == 0);
		REQUIRE(t.GetPerimeter() == 0);
		REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
		REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
		REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));

		WHEN("Set V1")
		{
			REQUIRE(t.SetVertex1({ 1, 1 }));
			REQUIRE(t.GetArea() == 0);
			REQUIRE(t.GetFillColor() == 0);
			REQUIRE(t.GetOutlineColor() == 0);
			REQUIRE((int)t.GetPerimeter() == 2);
			REQUIRE((t.GetVertex1().x == 1 && t.GetVertex1().y == 1));
			REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
			REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));
		}

		WHEN("Set V2")
		{
			REQUIRE(t.SetVertex2({ 1, 1 }));
			REQUIRE(t.GetArea() == 0);
			REQUIRE(t.GetFillColor() == 0);
			REQUIRE(t.GetOutlineColor() == 0);
			REQUIRE((int)t.GetPerimeter() == 2);
			REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
			REQUIRE((t.GetVertex2().x == 1 && t.GetVertex2().y == 1));
			REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));
		}

		WHEN("Set V3")
		{
			REQUIRE(t.SetVertex3({ 1, 1 }));
			REQUIRE(t.GetArea() == 0);
			REQUIRE(t.GetFillColor() == 0);
			REQUIRE(t.GetOutlineColor() == 0);
			REQUIRE((int)t.GetPerimeter() == 2);
			REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
			REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
			REQUIRE((t.GetVertex3().x == 1 && t.GetVertex3().y == 1));
		}

		WHEN("Set new fill color")
		{
			REQUIRE(t.SetFillColor(0x000001));
			REQUIRE(t.GetArea() == 0);
			REQUIRE(t.GetFillColor() == 1);
			REQUIRE(t.GetOutlineColor() == 0);
			REQUIRE(t.GetPerimeter() == 0);
			REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
			REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
			REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));
		}

		WHEN("Set new outline color")
		{
			REQUIRE(t.SetOutlineColor(0x000001));
			REQUIRE(t.GetArea() == 0);
			REQUIRE(t.GetFillColor() == 0);
			REQUIRE(t.GetOutlineColor() == 1);
			REQUIRE(t.GetPerimeter() == 0);
			REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
			REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
			REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));
		}

		WHEN("Get info")
		{
			std::string require("Shape name: Triangle\n");
			require.append("\tP1: X:0.000000 Y:0.000000\n");
			require.append("\tP2: X:0.000000 Y:0.000000\n");
			require.append("\tP3: X:0.000000 Y:0.000000\n");
			REQUIRE(t.ToString() == require);
		}
	}

	GIVEN("Triangle with constructor")
	{
		CTriangle t({ 0, 0 }, { 0, 0 }, { 0, 0 }, 0, 0);
		REQUIRE(t.GetArea() == 0);
		REQUIRE(t.GetFillColor() == 0);
		REQUIRE(t.GetOutlineColor() == 0);
		REQUIRE(t.GetPerimeter() == 0);
		REQUIRE((t.GetVertex1().x == 0 && t.GetVertex1().y == 0));
		REQUIRE((t.GetVertex2().x == 0 && t.GetVertex2().y == 0));
		REQUIRE((t.GetVertex3().x == 0 && t.GetVertex3().y == 0));
	}
}

SCENARIO("CRectangle tests")
{
	GIVEN("Default constructor")
	{
		CRectangle r;
		REQUIRE(r.GetArea() == 0);
		REQUIRE(r.GetPerimeter() == 0);
		REQUIRE(r.GetFillColor() == 0);
		REQUIRE(r.GetOutlineColor() == 0);
		REQUIRE(r.GetHeight() == 0);
		REQUIRE(r.GetWidth() == 0);
		REQUIRE((r.GetLeftTop().x == 0 && r.GetLeftTop().y == 0));
		REQUIRE((r.GetRightBottom().x == 0 && r.GetRightBottom().y == 0));

		WHEN("Set new fill color")
		{
			REQUIRE(r.SetFillColor(0x000001));
			REQUIRE(r.GetArea() == 0);
			REQUIRE(r.GetPerimeter() == 0);
			REQUIRE(r.GetFillColor() == 1);
			REQUIRE(r.GetOutlineColor() == 0);
			REQUIRE(r.GetHeight() == 0);
			REQUIRE(r.GetWidth() == 0);
			REQUIRE((r.GetLeftTop().x == 0 && r.GetLeftTop().y == 0));
			REQUIRE((r.GetRightBottom().x == 0 && r.GetRightBottom().y == 0));
		}

		WHEN("Set new outline color")
		{
			REQUIRE(r.SetOutlineColor(0x000001));
			REQUIRE(r.GetArea() == 0);
			REQUIRE(r.GetPerimeter() == 0);
			REQUIRE(r.GetFillColor() == 0);
			REQUIRE(r.GetOutlineColor() == 1);
			REQUIRE(r.GetHeight() == 0);
			REQUIRE(r.GetWidth() == 0);
			REQUIRE((r.GetLeftTop().x == 0 && r.GetLeftTop().y == 0));
			REQUIRE((r.GetRightBottom().x == 0 && r.GetRightBottom().y == 0));
		}

		WHEN("Set new Left top point")
		{
			REQUIRE(r.SetLeftTop({10, 10}));
			REQUIRE(r.GetArea() == 100);
			REQUIRE(r.GetPerimeter() == 40);
			REQUIRE(r.GetFillColor() == 0);
			REQUIRE(r.GetOutlineColor() == 0);
			REQUIRE(r.GetHeight() == 10);
			REQUIRE(r.GetWidth() == 10);
			REQUIRE((r.GetLeftTop().x == 10 && r.GetLeftTop().y == 10));
			REQUIRE((r.GetRightBottom().x == 0 && r.GetRightBottom().y == 0));
		}

		WHEN("Set new Right bottom point")
		{
			REQUIRE(r.SetRightBottom({ 10, 10 }));
			REQUIRE(r.GetArea() == 100);
			REQUIRE(r.GetPerimeter() == 40);
			REQUIRE(r.GetFillColor() == 0);
			REQUIRE(r.GetOutlineColor() == 0);
			REQUIRE(r.GetHeight() == 10);
			REQUIRE(r.GetWidth() == 10);
			REQUIRE((r.GetLeftTop().x == 0 && r.GetLeftTop().y == 0));
			REQUIRE((r.GetRightBottom().x == 10 && r.GetRightBottom().y == 10));
		}

		WHEN("Get info")
		{
			std::string require("Shape name: Rectangle\n");
			require.append("\tLeft top: X:0.000000 Y:0.000000\n");
			require.append("\tRight bottom: X:0.000000 Y:0.000000\n");
			REQUIRE(r.ToString() == require);
		}
	}

	GIVEN("With constructor")
	{
		CRectangle r({ 0, 0 }, {10, 10}, 1, 1);
		REQUIRE(r.GetArea() == 100);
		REQUIRE(r.GetPerimeter() == 40);
		REQUIRE(r.GetFillColor() == 1);
		REQUIRE(r.GetOutlineColor() == 1);
		REQUIRE(r.GetHeight() == 10);
		REQUIRE(r.GetWidth() == 10);
		REQUIRE((r.GetLeftTop().x == 0 && r.GetLeftTop().y == 0));
		REQUIRE((r.GetRightBottom().x == 10 && r.GetRightBottom().y == 10));	
	}
}

SCENARIO("CLineSegment tests")
{
	GIVEN("With empty constructor")
	{
		CLineSegment l;
		REQUIRE(l.GetArea() == 0);
		REQUIRE(l.GetPerimeter() == 0);
		REQUIRE(l.GetOutlineColor() == 0);
		REQUIRE((l.GetEndPoint().x == 0 && l.GetEndPoint().y == 0));
		REQUIRE((l.GetStartPoint().x == 0 && l.GetStartPoint().y == 0));

		WHEN("Set new outline color")
		{
			REQUIRE(l.SetOutlineColor(0x000001));
			REQUIRE(l.GetPerimeter() == 0);
			REQUIRE(l.GetOutlineColor() == 1);
			REQUIRE((l.GetEndPoint().x == 0 && l.GetEndPoint().y == 0));
			REQUIRE((l.GetStartPoint().x == 0 && l.GetStartPoint().y == 0));
		}

		WHEN("Set new start point")
		{
			REQUIRE(l.SetStartPoint({10, 10}));
			REQUIRE(l.GetPerimeter() == 0);
			REQUIRE(l.GetOutlineColor() == 0);
			REQUIRE((l.GetEndPoint().x == 0 && l.GetEndPoint().y == 0));
			REQUIRE((l.GetStartPoint().x == 10 && l.GetStartPoint().y == 10));
		}

		WHEN("Set new end point")
		{
			REQUIRE(l.SetEndPoint({ 10, 10 }));
			REQUIRE(l.GetPerimeter() == 0);
			REQUIRE(l.GetOutlineColor() == 0);
			REQUIRE((l.GetEndPoint().x == 10 && l.GetEndPoint().y == 10));
			REQUIRE((l.GetStartPoint().x == 0 && l.GetStartPoint().y == 0));
		}

		WHEN("Get info")
		{
			std::string require("Shape name: Line segment\n\tStart point: X:0.000000 Y:0.000000\n\tEnd point: X:0.000000 Y:0.000000\n");
			REQUIRE(l.ToString() == require);
		}
	}

	GIVEN("With constructor")
	{
		CLineSegment l({ 0, 0 }, {10, 10}, 1);
		REQUIRE(l.GetPerimeter() == 0);
		REQUIRE(l.GetOutlineColor() == 1);
		REQUIRE((l.GetEndPoint().x == 10 && l.GetEndPoint().y == 10));
		REQUIRE((l.GetStartPoint().x == 0 && l.GetStartPoint().y == 0));		
	}
}

SCENARIO("CShapes tests")
{
	GIVEN("data is empty")
	{
		Shapes data;
		auto find = dynamic_cast<CLineSegment const*>(&data.FindMaxAreaShape());
		REQUIRE(find);
		find = dynamic_cast<CLineSegment const*>(&data.FindMinPerimeterShape());
		REQUIRE(find);
	}

	GIVEN("data is one obj")
	{
		Shapes data;
		std::unique_ptr<IShape> r(new CRectangle({ 0, 0 }, { 10, 10 }, 0, 0));
		data.WriteShape(r);
		auto find = dynamic_cast<ISolidShape const*>(&data.FindMaxAreaShape());
		REQUIRE(find);
		find = dynamic_cast<ISolidShape const*>(&data.FindMinPerimeterShape());
		REQUIRE(find);
	}

	GIVEN("data is some obj")
	{
		Shapes data;
		std::unique_ptr<IShape> r1(new CRectangle({ 0, 0 }, { 10, 10 }, 0, 0));
		std::unique_ptr<IShape> r2(new CRectangle({ 0, 0 }, { 10, 10 }, 0, 0));
		std::unique_ptr<IShape> r3(new CRectangle({ 0, 0 }, { 10, 10 }, 0, 0));

		data.WriteShape(r1);
		data.WriteShape(r2);
		data.WriteShape(r3);
		auto find = dynamic_cast<ISolidShape const*>(&data.FindMaxAreaShape());
		REQUIRE(find);
		find = dynamic_cast<ISolidShape const*>(&data.FindMinPerimeterShape());
		REQUIRE(find);
	}
}

SCENARIO("CShapesHendler tests")
{
	GIVEN("standart constructor")
	{
		Shapes s; 
		CShapesHandler handler;
		REQUIRE(handler.HandleOperation("rectangle -300.0 -500.0 300.0 -700.0 000066 000066", s));
		REQUIRE(handler.HandleOperation("circle 0.0 500.0 1045.0 7c4e32 7c4e32", s));
		REQUIRE(handler.HandleOperation("triangle -480.0 -450.0 -350.0 -100.0 -350.0 -450.0 7c4e32 7c4e32", s));
		REQUIRE(handler.HandleOperation("linesegment -250.0 -200.0 -400.0 -500.0 000000", s));
		REQUIRE(s.GetSize() == 4);
			
	}

	GIVEN("in out constructor")
	{
		Shapes s; 
		std::stringstream ss;
		ss << "rectangle -300.0 -500.0 300.0 -700.0 000066 000066\n";
		ss << "circle 0.0 500.0 1045.0 7c4e32 7c4e32\n";
		ss << "triangle -480.0 -450.0 -350.0 -100.0 -350.0 -450.0 7c4e32 7c4e32\n";
		ss << "linesegment -250.0 -200.0 -400.0 -500.0 000000\n";
		std::istringstream iss(ss.str());
		std::ostringstream oss;
		CShapesHandler handler(iss, oss);
		handler.Handeling(s);
		REQUIRE(s.GetSize() == 4);
	}
}

SCENARIO("CCanvas tests")
{
	std::stringstream ss;
	ss << "rectangle -300.0 -500.0 300.0 -700.0 000066 000066\n";
	ss << "circle 0.0 500.0 1045.0 7c4e32 7c4e32\n";
	ss << "triangle -480.0 -450.0 -350.0 -100.0 -350.0 -450.0 7c4e32 7c4e32\n";
	ss << "linesegment -250.0 -200.0 -400.0 -500.0 000000\n";
	std::istringstream iss(ss.str());
	std::ostringstream oss;
	Shapes s;
	CShapesHandler handler(iss, oss);
	REQUIRE(handler.HandleOperation("rectangle -300.0 -500.0 300.0 -700.0 000066 000066", s));
	REQUIRE(handler.HandleOperation("circle 0.0 500.0 1045.0 7c4e32 7c4e32", s));
	REQUIRE(handler.HandleOperation("triangle -480.0 -450.0 -350.0 -100.0 -350.0 -450.0 7c4e32 7c4e32", s));
	REQUIRE(handler.HandleOperation("linesegment -250.0 -200.0 -400.0 -500.0 000000", s));
	REQUIRE(s.GetSize() == 4);
	CCanvas canvas;
	CPoint center;
	s.DrawAllData(canvas);

	canvas.~CCanvas();
}

