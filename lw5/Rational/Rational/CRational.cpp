#include "CRational.h"
#include <stdexcept>
#include <string>
#include <regex>


double CRational::ToDouble() const
{
    return (double)m_numerator / (double)m_denominator;
}

int CRational::GetNumerator() const { return m_numerator; }

int CRational::GetDenominator() const { return  m_denominator; }

CRational::CRational()
:m_numerator(0)
,m_denominator(1)
{
}

int GetGCD(int a, int b)
{
    for (;;)
    {
        if (a == 0) return abs(b);
        b %= a;
        if (b == 0) return abs(a);
        a %= b;
    }
}

int GetLCM(int a, int b)
{
    int temp = GetGCD(a, b);

    return temp ? (a / temp * b) : 0;
}

void CRational::Normalize() {
	const int GFC = GetGCD(m_numerator, m_denominator);

    m_denominator /= GFC;
    m_numerator /= GFC;
}

CRational::CRational(int value)
:m_numerator(value)
,m_denominator(1)
{
}

CRational::CRational(int numerator, int denominator)
{
    if (denominator <= 0)
    {
        throw std::invalid_argument("invalid denominator argument: denominator is a natural number");
    }
    m_denominator = denominator;
    m_numerator = numerator;
    Normalize();
}

void ToCommonDenominator(int& leftNum, int& leftDen, int& rightNum, int& rightDen)
{
    int lcm = GetLCM(leftDen, rightDen);
    int multiplierLeft = lcm / leftDen;
    int multiplierRight = lcm / rightDen;

    leftNum *= multiplierLeft;
    leftDen *= multiplierLeft;
    rightNum *= multiplierRight;
    rightDen *= multiplierRight;
}

std::pair<int, CRational> CRational::ToCompoundFraction() const
{
	return std::pair<int, CRational>
        (
            m_numerator / m_denominator,
            CRational(m_numerator % m_denominator, m_denominator)
        );
}

CRational operator+(CRational const& left, CRational const& right)
{
    int leftNum = left.m_numerator;
    int leftDen = left.m_denominator;
    int rightNum = right.m_numerator;
    int rightDen = right.m_denominator;

    ToCommonDenominator(leftNum, leftDen, rightNum, rightDen);

    return CRational(leftNum + rightNum, leftDen);
}

CRational operator-(CRational const& left, CRational const& right)
{
    return left+(-right);
}

CRational CRational::operator-() const
{
    return CRational(-m_numerator, m_denominator);
}

CRational CRational::operator+() const
{
    return *this;
}

CRational & CRational::operator++()
{
    *this += 1;
    return *this;
}

CRational CRational::operator++(int)
{
    CRational prev = *this;
    *this += 1;
    return prev;
}

CRational & CRational::operator--()
{
    *this -= 1;
    return *this;
}

CRational CRational::operator--(int)
{
    CRational prev = *this;
    *this -= 1;
    return prev;
}

CRational & CRational::operator=(const CRational &num)
{
    m_numerator = num.GetNumerator();
    m_denominator = num.m_denominator;
    return *this;
}

CRational & CRational::operator+=(const CRational &num)
{
    *this = *this + num;
    return *this;
}

CRational & CRational::operator-=(const CRational &num)
{
    *this = *this - num;
    return *this;
}

CRational & CRational::operator*=(const CRational &num)
{
    *this = *this * num;
    return *this;
}

CRational & CRational::operator/=(const CRational &num)
{
    *this = *this / num;
    return *this;
}

CRational operator*(CRational const& left, CRational const& right)
{
    int leftNum = left.m_numerator;
    int leftDen = left.m_denominator;
    int rightNum = right.m_numerator;
    int rightDen = right.m_denominator;

    return CRational(leftNum * rightNum, leftDen * rightDen);
}

CRational operator/(CRational const& left, CRational const& right)
{
    int leftNum = left.m_numerator;
    int leftDen = left.m_denominator;
    int rightNum = right.m_numerator;
    int rightDen = right.m_denominator;

    if (rightNum == 0)
	{
		throw std::underflow_error("Division by zero is not allowed");
	}

    return CRational(leftNum * rightDen, leftDen * rightNum);
}

bool operator==(CRational const& left, CRational const& right)
{
    return (left.m_numerator == right.m_numerator && left.m_denominator == right.m_denominator);
}

bool operator!=(CRational const& left, CRational const& right)
{
    return !(left == right);
}

bool operator<(CRational const& left, CRational const& right)
{
    return (left.m_numerator * right.m_denominator < right.m_numerator * left.m_denominator);
}

bool operator>=(CRational const& left, CRational const& right)
{
    return !(left < right);
}

bool operator>(CRational const& left, CRational const& right)
{
	return (left.m_numerator * right.m_denominator > right.m_numerator * left.m_denominator);
}

bool operator<=(CRational const& left, CRational const& right)
{
    return !(left > right);
}

std::istream& operator>>(std::istream& is, CRational& num)
{
    //В случае ошибки чтения рациональной дроби failbit 
	std::regex rationalRegex("^([+-])?"
							 "(\\d+)/(\\d+)");
	const int SIGN_INDEX = 1;
	const int NUMERATOR_INDEX = 2;
	const int DENOMINATOR_INDEX = 3;
       
	std::smatch match;
	std::string findedString;
    
    is >> findedString;
	if (!std::regex_search(findedString, match, rationalRegex))
	{
		is.setstate(std::ios::failbit);
		num = CRational();
		return is;
	}
	if (!match[NUMERATOR_INDEX].str().empty() && !match[DENOMINATOR_INDEX].str().empty())
	{
		num = CRational(std::stoi(match[NUMERATOR_INDEX].str()), std::stoi(match[DENOMINATOR_INDEX].str()));
	}
	if (!match[SIGN_INDEX].str().empty())
	{
		num *= (match[SIGN_INDEX].str() == "+") ? 1 : -1;
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, CRational const& num)
{
	os << num.m_numerator << '/' << num.m_denominator;
	return os;
}
