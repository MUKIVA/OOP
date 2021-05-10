#include "Calc.h"

std::map<std::string, Operation> const Fn::OPERATION_MAP = {
	{ "+", Operation::PLUS },
	{ "-", Operation::MINUS },
	{ "*", Operation::MULTIPLY },
	{ "/", Operation::DIVIDE },
};

bool Fn::SetFirst(std::string const& arg)
{
	m_firstArg = arg;
	return true;
}

bool Fn::SetSecond(std::string const& arg)
{
	m_secondArg = arg;
	return true;
}

bool Fn::SetOperation(std::string const& op)
{
	if (OPERATION_MAP.find(op) != OPERATION_MAP.end())
	{
		m_operation = OPERATION_MAP.at(op);
		return true;
	}
	return false;
}

Operation Fn::GetOperation() const
{
	return m_operation;
}
std::string Fn::GetFirst() const
{
	return m_firstArg;
}
std::string Fn::GetSecond() const
{
	return m_secondArg;
}

double Fn::GetValue() const
{
	return m_value;
}

bool Fn::SetValue(double num)
{
	m_value = num;
	return true;
}