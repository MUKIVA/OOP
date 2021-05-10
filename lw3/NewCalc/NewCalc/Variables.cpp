#include "Variables.h"
#include <iomanip>
#include <sstream>
#include <regex>
#include <algorithm>
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
	: m_oStream(os){};

Variables::Variables()
	: m_oStream(std::cout){};

bool IsSetInVars(Vars const& v, std::string const& name)
{
	return (v.find(name) != v.end());
}

bool IsSetInFns(Fns const& f, std::string const& name)
{
	return (f.find(name) != f.end());
}

bool Variables::CreateVariable(std::string const& var)
{
	if (IsSetInFns(m_fns, var) || IsSetInVars(m_vars, var))
	{
		PrintMsg(m_oStream, "Идентификатор занят");
		return false;
	}
	m_vars.insert(std::pair<std::string, double>(var, nan("1")));
	return true;
}

bool RecalculateFns(Fns& fns)
{
	std::map<double* const, Fn* const> valueFromFn;
	std::map<Fn* const, bool> fnMask;
	std::stack<std::reference_wrapper<Fn>> calculationProcedure;
	for (auto& fn : fns)
	{
		valueFromFn.insert(std::pair<double* const, Fn* const>(fn.second.GetValue(), &fn.second));
		fnMask.insert(std::pair<Fn* const, bool>(&fn.second, false));
		calculationProcedure.push(fn.second);
	}
	while (!calculationProcedure.empty())
	{
		Fn& top = calculationProcedure.top().get();
		if (valueFromFn.find(top.GetFirst()) == valueFromFn.end()
			&& valueFromFn.find(top.GetSecond()) == valueFromFn.end())
		{
			top.CalculateValue();
			fnMask.at(&top) = true;
			calculationProcedure.pop();
			continue;
		}
		if (top.GetFirst() && valueFromFn.find(top.GetFirst()) != valueFromFn.end() 
			&& !fnMask.at(valueFromFn.at(top.GetFirst())))
		{
			calculationProcedure.push(*valueFromFn.at(top.GetFirst()));
		}
		if (top.GetSecond() && valueFromFn.find(top.GetSecond()) != valueFromFn.end() 
			&& !fnMask.at(valueFromFn.at(top.GetSecond())))
		{
			calculationProcedure.push(*valueFromFn.at(top.GetSecond()));
		}
		if (valueFromFn.find(top.GetFirst()) == valueFromFn.end() || fnMask.at(valueFromFn.at(top.GetFirst()))
			&& !top.GetSecond())
		{
			top.CalculateValue();
			fnMask.at(&top) = true;
			calculationProcedure.pop();
			continue;
		}
		if (valueFromFn.find(top.GetFirst()) == valueFromFn.end() || fnMask.at(valueFromFn.at(top.GetFirst())) 
			&& (top.GetSecond() && (valueFromFn.find(top.GetSecond()) == valueFromFn.end() || fnMask.at(valueFromFn.at(top.GetSecond())))))
		{
			top.CalculateValue();
			fnMask.at(&top) = true;
			calculationProcedure.pop();
			continue;
		}
	}
	return true;
}

bool Variables::SetVariable(std::string const& var, const double num)
{
	if (IsSetInFns(m_fns, var))
	{
		PrintMsg(m_oStream, "Нельзя присвоить функции новое значение");
		return false;
	}
	if (!IsSetInVars(m_vars, var))
	{
		CreateVariable(var);
	}
	m_vars.at(var) = num;
	RecalculateFns(m_fns);
	return true;
}

bool Variables::SetVariable(std::string const& var, std::string const& num)
{
	if (IsSetInFns(m_fns, var))
	{
		PrintMsg(m_oStream, "Нельзя присвоить функции новое значение");
		return false;
	}
	if (!IsSetInFns(m_fns, num) && !IsSetInVars(m_vars, num))
	{
		std::string msg;
		msg.append("Идентификатор ").append(num).append(" не найден");
		PrintMsg(m_oStream, msg);
		return false;
	}
	if (!IsSetInVars(m_vars, var))
	{
		CreateVariable(var);
	}
	if (IsSetInFns(m_fns, num))
	{
		m_vars.at(var) = *m_fns.at(num).GetValue();
	}
	if (IsSetInVars(m_vars, num))
	{
		m_vars.at(var) = m_vars.at(num);
	}
	RecalculateFns(m_fns);
	return true;
}

bool Variables::SetFn(std::string const& fnName, std::string const& args)
{
	if (IsSetInFns(m_fns, fnName) || IsSetInVars(m_vars, fnName))
	{
		std::string msg("Идентификатор ");
		msg.append(fnName).append(" занят");
		PrintMsg(m_oStream, msg);
		return false;
	}
	std::string argWithoutSpaces = args;
	argWithoutSpaces.erase(std::remove_if(argWithoutSpaces.begin(), argWithoutSpaces.end(), isspace), argWithoutSpaces.end());
	std::regex argsReg("(\\w+\\d*\\w*)"
					   "([+-/\\*])?"
					   "(\\w+\\d*\\w*)?");
	std::smatch argsMatch;
	if (std::regex_match(argWithoutSpaces, argsMatch, argsReg))
	{
		if (!((!argsMatch[1].str().empty() && argsMatch[2].str().empty() && argsMatch[3].str().empty())
			|| (!argsMatch[1].str().empty() && !argsMatch[2].str().empty() && !argsMatch[3].str().empty())))
		{
			PrintMsg(m_oStream, "Неверный формат выражения");
			return false;
		}
		Fn newFn;
		if (!IsSetInFns(m_fns, argsMatch[1].str()) && !IsSetInVars(m_vars, argsMatch[1].str()))
		{
			std::string msg("Идентификатор ");
			msg.append(argsMatch[1].str()).append(" не определён");
			PrintMsg(m_oStream, msg);
			return false;
		}
		if (IsSetInFns(m_fns, argsMatch[1].str()))
		{
			newFn.SetFirst(*m_fns.at(argsMatch[1].str()).GetValue());
		}
		if (IsSetInVars(m_vars, argsMatch[1].str()))
		{
			newFn.SetFirst(m_vars.at(argsMatch[1].str()));
		}
		if (!argsMatch[2].str().empty())
		{
			newFn.SetOperation(argsMatch[2].str());
			if (!IsSetInFns(m_fns, argsMatch[3].str()) && !IsSetInVars(m_vars, argsMatch[3].str()))
			{
				std::string msg("Идентификатор ");
				msg.append(argsMatch[3].str()).append(" не определён");
				PrintMsg(m_oStream, msg);
				return false;
			}
			if (IsSetInFns(m_fns, argsMatch[3].str()))
			{
				newFn.SetSecond(*m_fns.at(argsMatch[3].str()).GetValue());
			}
			if (IsSetInVars(m_vars, argsMatch[3].str()))
			{
				newFn.SetSecond(m_vars.at(argsMatch[3].str()));
			}
		}
		newFn.CalculateValue();
		m_fns.insert(std::pair<std::string, Fn>(fnName, newFn));
	}
	return true;
}


bool Variables::Print(std::string const& id)
{
	if (!IsSetInFns(m_fns, id) && !IsSetInVars(m_vars, id))
	{
		std::string msg = "Идентификатор ";
		msg.append(id).append(" не объявлен");
		PrintMsg(m_oStream, msg);
		return false;	
	}
	if (IsSetInFns(m_fns, id))
	{
		PrintMsg(m_oStream, *m_fns.at(id).GetValue());
	}
	if (IsSetInVars(m_vars, id))
	{
		PrintMsg(m_oStream, m_vars.at(id));
	}
	return true;
}

bool Variables::PrintFns()
{
	for (auto& fn : m_fns)
	{
		std::string msg;
		msg.append(fn.first).append(":").append(DoubleToString(*fn.second.GetValue()));
		PrintMsg(m_oStream, msg);
	}
	return true;
}

bool Variables::PrintVars()
{
	for (auto& var : m_vars)
	{
		std::string msg;
		msg.append(var.first).append(":").append(DoubleToString(var.second));
		PrintMsg(m_oStream, msg);
	}
	return true;
}