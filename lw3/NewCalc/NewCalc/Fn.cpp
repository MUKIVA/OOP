#include "Fn.h"

std::map<std::string, double (*)(double a, double b)> const Fn::OPERATION_MAP = {
	{ "+", Plus },
	{ "-", Minus },
	{ "*", Multiply },
	{ "/", Divide },
};

double Plus(double a, double b) { return (a && b) ? a + b : nan("1"); }
double Minus(double a, double b) { return (a && b) ? a - b : nan("1"); }
double Multiply(double a, double b) { return (a && b) ? a * b : nan("1"); }
double Divide(double a, double b) { return (a && b) ? a / b : nan("1"); }

double* Fn::GetValue() { return &m_value; }
double* Fn::GetFirst() const { return m_firstArg; }
double* Fn::GetSecond() const { return m_secondArg; }

bool Fn::SetOperation(std::string const& op)
{
	if (OPERATION_MAP.find(op) != OPERATION_MAP.end())
	{
		m_operation = OPERATION_MAP.at(op);
		return true;
	}
	return false;
}

bool Fn::CalculateValue()
{
	if (m_firstArg && m_secondArg && m_operation)
	{
		m_value = m_operation(*m_firstArg, *m_secondArg);
		return true;
	}
	if (m_firstArg && !m_operation && !m_secondArg)
	{
		m_value = *m_firstArg;
	}
	return false;
}

bool Fn::SetFirst(double& num)
{
	m_firstArg = &num;
	return true;
}

bool Fn::SetSecond(double& num)
{
	m_secondArg = &num;
	return true;
}