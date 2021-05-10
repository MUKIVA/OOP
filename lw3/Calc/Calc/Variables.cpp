#include "Calc.h"
#include <algorithm>
#include <regex>
#include <iomanip>
#include <sstream>
#include <stack>

std::string DoubleToString(double d)
{
	if (isnan(d))
	{
		return "nan";
	}
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << d;
	return oss.str();
}

void PrintMsg(std::ostream& os, std::string const& msg)
{
	os << msg << std::endl;
}

void PrintMsg(std::ostream& os, const double msg)
{
	os << std::fixed << std::setprecision(2) << msg << std::endl;
}

Variables::Variables(std::ostream& os)
	: m_oStream(os)
{
}

Variables::Variables()
	: m_oStream(std::cout){};

double Variables::GetVariableValue(std::string const& var) const
{
	if (m_variables.find(var) != m_variables.end())
	{
		return m_variables.at(var);
	}
	else
	{
		return nan("1");
	}
}

bool Variables::SetVariable(std::string const& var, const double num)
{
	if (m_functions.find(var) != m_functions.end())
	{
		PrintMsg(m_oStream, "Невозможно присвоить функции новое значение");
		return false;
	}
	if (m_variables.find(var) != m_variables.end())
	{
		m_variables.at(var) = num;
		RecalculateFns(var);
		return true;
	}
	else
	{
		CreateVariable(var);
		m_variables.at(var) = num;
		return true;
	}
}

bool Variables::RecalculateFns(std::string const& var)
{
	std::map<std::string, bool> mask;
	std::stack<std::reference_wrapper<std::pair<const std::string, Fn>>> calculationProcedure;
	for (auto& fn : m_functions)
	{
		mask[fn.first] = false;
		mask[fn.second.GetSecond()] = false;
		mask[fn.second.GetFirst()] = false;
		if (m_variables.find(fn.second.GetSecond()) != m_variables.end())
		{
			mask.at(fn.second.GetSecond()) = true;
		}
		if (m_variables.find(fn.second.GetFirst()) != m_variables.end())
		{
			mask.at(fn.second.GetFirst()) = true;
		}
		calculationProcedure.push(fn);
	}
	while (!calculationProcedure.empty())
	{
		auto& top = calculationProcedure.top();
		if (mask.at(top.get().first))
		{
			calculationProcedure.pop();
			continue;
		}
		if (mask.at(top.get().second.GetFirst()) && mask.at(top.get().second.GetSecond()))
		{
			CalculateFn(top.get().first);
			calculationProcedure.pop();
			mask.at(top.get().first) = true;
			continue;
		}
		if (!mask.at(top.get().second.GetFirst()))
		{
			calculationProcedure.push(*m_functions.find(top.get().second.GetFirst()));
		}
		if (!mask.at(top.get().second.GetSecond()))
		{
			calculationProcedure.push(*m_functions.find(top.get().second.GetSecond()));
		}
	}
	return true;
}

bool Variables::SetVariable(std::string const& var, std::string const& num)
{
	if (m_functions.find(var) != m_functions.end())
	{
		PrintMsg(m_oStream, "Невозможно присвоить функции новое значение");
		return false;
	}
	if (m_variables.find(num) != m_variables.end() 
		&& m_variables.find(var) != m_variables.end())
	{
		m_variables.at(var) = m_variables.at(num);
		return true;
	}
	if (m_functions.find(num) != m_functions.end() 
		&& m_variables.find(var) != m_variables.end())
	{
		SetVariable(var, GetFnValue(num));
		return RecalculateFns(var);
	}
	if (m_variables.find(var) == m_variables.end() 
		&& m_variables.find(num) != m_variables.end())
	{
		if (CreateVariable(var))
		{
			m_variables.at(var) = m_variables.at(num);
			return true;
		}
	}
	if (m_variables.find(var) == m_variables.end() 
		&& m_functions.find(num) != m_functions.end())
	{
		if (CreateVariable(var))
		{
			return SetVariable(var, GetFnValue(num));
		}
	}
	return false;
}

bool Variables::CreateVariable(std::string const& var)
{
	if (m_variables.find(var) == m_variables.end() 
		&& m_functions.find(var) == m_functions.end())
	{
		m_variables.insert(std::pair<std::string, double>(var, NAN));
		return true;
	}
	PrintMsg(m_oStream, "Данный идентификатор занят");
	return false;
}

double Variables::GetFnValue(std::string const& fn) const
{
	if (m_functions.find(fn) != m_functions.end())
	{
		return m_functions.at(fn).GetValue();
	}
	else
	{
		return nan("1");
	}
}

bool Variables::CalculateFn(std::string const& fn)
{
	Fn& currFn = m_functions.at(fn);
	double first = nan("1"), second = nan("1");
	if (m_variables.find(currFn.GetFirst()) != m_variables.end())
	{
		first = m_variables.at(currFn.GetFirst());
	}
	if (m_variables.find(currFn.GetSecond()) != m_variables.end())
	{
		second = m_variables.at(currFn.GetSecond());
	}
	if (m_functions.find(currFn.GetFirst()) != m_functions.end())
	{
		first = GetFnValue(currFn.GetFirst());
	}
	if (m_functions.find(currFn.GetSecond()) != m_functions.end())
	{
		second = GetFnValue(currFn.GetSecond());
	}
	if (currFn.GetOperation() == Operation::NONE && currFn.GetSecond().empty())
	{
		currFn.SetValue(first);
		return true;
	}
	switch (currFn.GetOperation())
	{
	case Operation::PLUS:
		currFn.SetValue(first + second);
		return true;
		break;
	case Operation::MINUS:
		currFn.SetValue(first - second);
		return true;
		break;
	case Operation::MULTIPLY:
		currFn.SetValue(first * second);
		return true;
		break;
	case Operation::DIVIDE:
		currFn.SetValue(first / second);
		return true;
		break;
	default:
		break;
	}
	currFn.SetValue(nan("1"));
	return true;
}

bool Variables::SetFn(std::string const& fnName, std::string const& args)
{
	if (m_functions.find(fnName) != m_functions.end()
		|| m_variables.find(fnName) != m_variables.end())
	{
		PrintMsg(m_oStream, "Данный идентификатор занят");
		return false;
	}
	Fn newFn;
	std::string argWithoutSpaces = args;
	argWithoutSpaces.erase(std::remove_if(argWithoutSpaces.begin(), argWithoutSpaces.end(), isspace), argWithoutSpaces.end());
	std::regex argsReg("(\\w+\\d*\\w*)"
					   "([+-/\\*])?"
					   "(\\w+\\d*\\w*)?");
	std::smatch argsMatch;
	if (std::regex_match(argWithoutSpaces, argsMatch, argsReg))
	{
		if (m_variables.find(argsMatch[1].str()) == m_variables.end()
			&& m_functions.find(argsMatch[1].str()) == m_functions.end())
		{
			std::string msg = "Переменная ";
			msg.append(argsMatch[1].str()).append(" не объявлена");
			PrintMsg(m_oStream, msg);
			return false;
		}
		newFn.SetFirst(argsMatch[1].str());
		if (!(argsMatch[2].str().empty()) && !(argsMatch[3].str().empty()))
		{
			if (m_variables.find(argsMatch[3].str()) == m_variables.end()
				&& m_functions.find(argsMatch[3].str()) == m_functions.end())
			{
				std::string msg = "Переменная ";
				msg.append(argsMatch[3].str()).append(" не объявлена");
				PrintMsg(m_oStream, msg);
				return false;
			}
			newFn.SetSecond(argsMatch[3].str());
			newFn.SetOperation(argsMatch[2].str());
		}
		m_functions.insert(std::pair<std::string, Fn>(fnName, newFn));
		CalculateFn(fnName);
		return true;
	}
	return false;
}

void Variables::Print(std::string const& id)
{
	double value = nan("1");
	if (m_functions.find(id) == m_functions.end()
		&& m_variables.find(id) == m_variables.end())
	{
		std::string msg = "Идентификатор ";
		msg.append(id).append(" не объявлен");
		PrintMsg(m_oStream, msg);
		return;
	}
	if ((value = GetFnValue(id)) && !isnan(value))
	{
		PrintMsg(m_oStream, value);
		return;
	}
	if ((value = GetVariableValue(id)) && !isnan(value))
	{
		PrintMsg(m_oStream, value);
		return;
	}
	PrintMsg(m_oStream, "nan");
}

void Variables::PrintFns()
{
	for (auto const& fn : m_functions)
	{
		std::string msg;
		msg.append(fn.first).append(":").append(DoubleToString(GetFnValue(fn.first)));
		PrintMsg(m_oStream, msg);
	}
}

void Variables::PrintVars()
{
	for (auto const& var : m_variables)
	{
		std::string msg;
		msg.append(var.first).append(":").append(DoubleToString(var.second));
		PrintMsg(m_oStream, msg);
	}
}
