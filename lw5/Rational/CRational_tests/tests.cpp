#define CATCH_CONFIG_MAIN


#include "../../../Catch/catch.hpp"

#include "../Rational/CRational.h"

#include <sstream>

SCENARIO("Constructor tests")
{
	WHEN("Empty constructor")
	{
		CRational rNum;
		REQUIRE((rNum.GetNumerator() == 0 && rNum.GetDenominator() == 1));
	}

	WHEN("One arg constructor")
	{
		THEN("Positive")
		{
			CRational rNum(100);
			REQUIRE((rNum.GetNumerator() == 100 && rNum.GetDenominator() == 1));
		}
		THEN("Negative")
		{
			CRational rNum(-100);
			REQUIRE((rNum.GetNumerator() == -100 && rNum.GetDenominator() == 1));
		}
	}

	WHEN("Two arg constructor")
	{
		THEN("Positive Positive")
		{
			CRational rNum(10, 20);
			REQUIRE((rNum.GetNumerator() == 1 && rNum.GetDenominator() == 2));
		}

		THEN("Negative Positive")
		{
			CRational rNum(-10, 20);
			REQUIRE((rNum.GetNumerator() == -1 && rNum.GetDenominator() == 2));
		}

		THEN("Negative Negative")
		{
			REQUIRE_THROWS(CRational(-10, -20));
		}

		THEN("Positive Negative")
		{
			REQUIRE_THROWS(CRational(10, -20));
		}
	}
}

SCENARIO("Basic bool operations tests")
{
	
	GIVEN("Bool operations: == !=")
	{
		WHEN("1/2 and 1/2")
		{
			CRational r1(1, 2);
			CRational r2(1, 2);
			REQUIRE(r1 == r2);
			REQUIRE_FALSE(r1 != r2);
		}

		WHEN("1/2 and 2/4")
		{
			CRational r1(1, 2);
			CRational r2(2, 4);
			REQUIRE(r1 == r2);
			REQUIRE_FALSE(r1 != r2);
		}

		WHEN("2/2 and 4/4")
		{
			CRational r1(2, 2);
			CRational r2(4, 4);
			REQUIRE(r1 == r2);
			REQUIRE_FALSE(r1 != r2);	
		}

		WHEN("2/1 and 2")
		{
			CRational r1(2);
			REQUIRE(r1 == 2);
			REQUIRE_FALSE(r1 != 2);
		}
	}

	GIVEN("bool operations: > < >= <=")
	{
		WHEN("1/2 and 1/3")
		{
			CRational r1(1, 2);
			CRational r2(1, 3);
			REQUIRE(r1 > r2);
			REQUIRE(r1 >= r2);
			REQUIRE_FALSE(r1 < r2);
			REQUIRE_FALSE(r1 <= r2);
		}

		WHEN("3/1 and 2")
		{
			CRational r1(3, 1);
			REQUIRE(r1 > 2);
			REQUIRE(r1 >= 2);
			REQUIRE_FALSE(r1 < 2);
			REQUIRE_FALSE(r1 <= 2);
		}

		WHEN("1/2 and 7")
		{
			CRational r1(1, 7);
			REQUIRE_FALSE(r1 > 7);
			REQUIRE_FALSE(r1 >= 7);
			REQUIRE(r1 < 7);
			REQUIRE(r1 <= 7);
		}

		WHEN("7/1 and 7")
		{
			CRational r1(7, 1);
			REQUIRE_FALSE(r1 > 7);
			REQUIRE(r1 >= 7);
			REQUIRE_FALSE(r1 < 7);
			REQUIRE(r1 <= 7);
		}

		WHEN("3 and 7/2")
		{
			CRational r2(7, 2);
			REQUIRE_FALSE(3 > r2);
			REQUIRE_FALSE(3 >= r2);
			REQUIRE(3 < r2);
			REQUIRE(3 <= r2);
		}
	}
}

SCENARIO("Basic arithmetic operations test")
{
	GIVEN("Operation: +")
	{
		WHEN("1/2 and 1/6")
		{
			CRational rquire(2, 3);
			CRational left(1, 2);
			CRational right(1, 6);
			REQUIRE((left + right) == rquire);
		}

		WHEN("1/2 and 1")
		{
			CRational rquire(3, 2);
			CRational left(1, 2);
			REQUIRE((left + 1) == rquire);
		}

		WHEN("1 and 1/2")
		{
			CRational rquire(3, 2);
			CRational right(1, 2);
			REQUIRE((1 + right) == rquire);
		}
	}

	GIVEN("Operation: -")
	{
		WHEN("1/2 and 1/6")
		{
			CRational rquire(1, 3);
			CRational left(1, 2);
			CRational right(1, 6);
			REQUIRE((left - right) == rquire);
		}

		WHEN("1/2 and 1")
		{
			CRational rquire(-1, 2);
			CRational left(1, 2);
			REQUIRE((left - 1) == rquire);
		}

		WHEN("1 and 1/2")
		{
			CRational rquire(1, 2);
			CRational right(1, 2);
			REQUIRE((1 - right) == rquire);
		}
	}

	GIVEN("Operation: *")
	{
		WHEN("1/2 and 2/3")
		{
			CRational rquire(1, 3);
			CRational left(1, 2);
			CRational right(2, 3);
			REQUIRE((left * right) == rquire);
		}

		WHEN("1/2 and -3")
		{
			CRational rquire(-3, 2);
			CRational left(1, 2);
			REQUIRE((left * -3) == rquire);
		}

		WHEN("7 and 2/3")
		{
			CRational rquire(14, 3);
			CRational right(2, 3);
			REQUIRE((7 * right) == rquire);
		}
	}

	GIVEN("Operation: /")
	{
		WHEN("1/2 and 2/3")
		{
			CRational rquire(3, 4);
			CRational left(1, 2);
			CRational right(2, 3);
			REQUIRE((left / right) == rquire);
		}

		WHEN("1/2 and 5")
		{
			CRational rquire(1, 10);
			CRational left(1, 2);
			REQUIRE((left / 5) == rquire);
		}

		WHEN("7 and 2/3")
		{
			CRational rquire(21, 2);
			CRational right(2, 3);
			REQUIRE((7 / right) == rquire);
		}

		WHEN("1/2 and 0/1")
		{
			CRational left(1, 2);
			CRational right;
			REQUIRE_THROWS(left / right);
		}
	}
}

SCENARIO("Unar operations test")
{
	WHEN("Unar +")
	{
		CRational require(-1, 2);
		CRational r(-1, 2);
		REQUIRE(+r == require);
	}

	WHEN("Unar -")
	{
		CRational require(-1, 2);
		CRational r(1, 2);
		REQUIRE(-r == require);
	}
}

SCENARIO("Abbreviated notation")
{
	GIVEN("Operation: +=")
	{
		WHEN("1/2 and 1/6")
		{
			CRational rquire(2, 3);
			CRational r1(1, 2);
			CRational r2(1, 6);
			REQUIRE((r1 += r2) == rquire);
		}

		WHEN("1/2 and 1")
		{
			CRational rquire(3, 2);
			CRational r1(1, 2);
			REQUIRE(((r1 += 1) == rquire));
		}
	}

	GIVEN("Operation: -=")
	{
		WHEN("1/2 and 1/6")
		{
			CRational rquire(1, 3);
			CRational r1(1, 2);
			CRational r2(1, 6);
			REQUIRE((r1 -= r2) == rquire);
		}

		WHEN("1/2 and 1")
		{
			CRational rquire(-1, 2);
			CRational r1(1, 2);
			REQUIRE(((r1 -= 1) == rquire));
		}
	}

	GIVEN("Operation: *=")
	{
		WHEN("1/2 and 2/3")
		{
			CRational rquire(1, 3);
			CRational r1(1, 2);
			CRational r2(2, 3);
			REQUIRE((r1 *= r2) == rquire);
		}

		WHEN("1/2 and 3")
		{
			CRational rquire(3, 2);
			CRational r1(1, 2);
			REQUIRE(((r1 *= 3) == rquire));
		}
	}

	GIVEN("Operation: /=")
	{
		WHEN("1/2 and 2/3")
		{
			CRational rquire(3, 4);
			CRational r1(1, 2);
			CRational r2(2, 3);
			REQUIRE((r1 /= r2) == rquire);
		}

		WHEN("1/2 and 3")
		{
			CRational rquire(1, 6);
			CRational r1(1, 2);
			REQUIRE(((r1 /= 3) == rquire));
		}

		WHEN("3/4 and 3/8")
		{
			CRational rquire(2, 1);
			CRational r1(3, 4);
			CRational r2(3, 8);
			REQUIRE(((r1 /= r2) == rquire));
		}
	}

	GIVEN("Operation: ++a a++ --a a--")
	{
		WHEN("Op: ++a a++")
		{
			THEN("++a")
			{
				CRational r(1, 2);
				REQUIRE(++r == CRational(3, 2));
			}

			THEN("a++")
			{
				CRational r(1, 2);
				REQUIRE(r++ == CRational(1, 2));
				REQUIRE(r == CRational(3, 2));
			}
		}

		WHEN("Op: --a a--")
		{
			THEN("--a")
			{
				CRational r(1, 2);
				REQUIRE(--r == CRational(-1, 2));
			}

			THEN("a--")
			{
				CRational r(1, 2);
				REQUIRE(r-- == CRational(1, 2));
				REQUIRE(r == CRational(-1, 2));
			}
		}
	}
}

SCENARIO("I/O test")
{
	GIVEN("input test")
	{
		WHEN("stream is empty")
		{
			CRational r, require;
			std::istringstream iss("");
			iss >> r;

			REQUIRE(r == require);
		}

		WHEN("stream is one number")
		{
			CRational r;
			CRational require(-1, 2);
			std::istringstream iss(" -10/20");
			iss >> r;
			REQUIRE(r == require);
		}

		WHEN("Sequential reading")
		{
			CRational r;
			CRational require1(1, 2);
			CRational require2(1, 2);
			std::istringstream iss("10/20 2/4");
			iss >> r;
			REQUIRE(r == require1);
			iss >> r;
			REQUIRE(r == require2);
		}

		WHEN("Sequential reading with trash")
		{
			CRational r;
			CRational require1;
			CRational require2(-1, 2);
			CRational require3(3, 4);
			CRational require4(1, 2);
			std::istringstream iss("asasdasdasd -10/20 asdasda 3/4 sdasdadasd 2/4 asdasdasdasd ");
			iss >> r;
			REQUIRE(r == require1);
			REQUIRE(iss.failbit);
		}
	}

	GIVEN("output test")
	{
		std::ostringstream oss;
		oss << CRational(10, 20);
		REQUIRE(oss.str() == "1/2");
	}

	WHEN("number is invalid")
	{
		std::istringstream s("abc-1/3");
		CRational r;
		s >> r;
		REQUIRE(r == 0);
	}
}

SCENARIO("give CompoundFraction number")
{
	std::pair<int, CRational> require(4, CRational());
	std::pair<int, CRational> require2(-1, CRational(-1, 3));
	CRational r( 4, 1);
	CRational r2(-4, 3);
	REQUIRE(r.ToCompoundFraction() == require);
	REQUIRE(r2.ToCompoundFraction() == require2 );
}