#pragma once
#include <iostream>


class CRational
{
public:
    CRational();
    CRational(int value);
    CRational(int numerator, int denominator);

    friend CRational operator-(CRational const& left, CRational const& right);
    friend CRational operator*(CRational const& left, CRational const& right);
    friend CRational operator/(CRational const& left, CRational const& right);
    friend CRational operator+(CRational const& left, CRational const& right);
    friend bool operator==(CRational const& left, CRational const& right);
    friend bool operator<=(CRational const& left, CRational const& right);
    friend bool operator>=(CRational const& left, CRational const& right);
    friend bool operator<(CRational const& left, CRational const& right);
    friend bool operator>(CRational const& left, CRational const& right);
    friend bool operator!=(CRational const& left, CRational const& right);
    friend std::ostream& operator<<(std::ostream& os, CRational const& num);
    friend std::istream& operator>>(std::istream& is, CRational& num);

    CRational& operator++();
    CRational& operator--();
    CRational operator++(int);
    CRational operator--(int);
    CRational operator-() const;
    CRational operator+() const;
    CRational& operator+=(CRational const& num);
    CRational& operator-=(CRational const& num);
    CRational& operator*=(CRational const& num);
    CRational& operator/=(CRational const& num);
    CRational& operator=(CRational const& num);


    int GetNumerator() const;
    int GetDenominator() const;
    double ToDouble() const;
	std::pair<int, CRational> ToCompoundFraction() const;

private:
    void Normalize();
    int m_numerator;
    int m_denominator;
};