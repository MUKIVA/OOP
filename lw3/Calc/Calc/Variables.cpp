#include "Calc.h"


int Variables::GetVariable(std::string const& var) const
{
	if (m_variables.find(var) != m_variables.end())
	{
		return m_variables.at(var);
	}
	else
	{
		return NAN;
	}	
}

bool Variables::SetVariable(std::string const& var, const double num)
{
	m_variables.at(var) = num;
	return true;
}

bool Variables::SetVariable(std::string const& var, std::string const& num)
{
	if (m_variables.find(num) != m_variables.end())
	{
		m_variables.at(var) = m_variables.at(num);
		return true;
	}
	return false;
}

bool Variables::CreateVariable(std::string const& var)
{
	if (m_variables.find(var) == m_variables.end())
	{
		m_variables.insert(std::pair<std::string, double>(var, NAN));
		return true;
	}
	return false;
}