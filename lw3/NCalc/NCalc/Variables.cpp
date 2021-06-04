#include "Variables.h"
#include <algorithm>
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
	: m_oStream(os){};

Variables::Variables()
	: m_oStream(std::cout){};

bool Variables::IsSetInVars(std::string const& id) const
{
	return m_vars.find(id) != m_vars.end();
}

bool Variables::IsSetInFns(std::string const& id) const
{
	return m_fns.find(id) != m_fns.end();
}

bool Variables::CreateVar(std::string const& id)
{
	if (IsSetInVars(id) || IsSetInFns(id))
	{
		PrintMsg(m_oStream, "Идентификатор занят");
		return false;
	}
	m_vars.insert(std::pair<std::string, double>(id, DOUBLE_NAN));
	return true;
}

bool Variables::SetVar(std::string const& id, double const num)
{
	if (IsSetInFns(id))
	{
		PrintMsg(m_oStream, "Нельзя переопределить функцию");
		return false;
	}
	if (IsSetInVars(id))
	{
		m_vars.at(id) = num;
		RecalculateFns();
	}
	m_vars[id] = num;
	return true;
}

bool Variables::SetVar(std::string const& id, std::string const& anotherId)
{
	if (IsSetInFns(id))
	{
		PrintMsg(m_oStream, "Нельзя переопределить функцию");
		return false;
	}
	if (id == anotherId)
	{
		PrintMsg(m_oStream, "Нельзя приравнять переменной саму себя");
		return false;
	}
	if (IsSetInFns(anotherId))
	{
		m_vars[id] = m_fns.at(anotherId).result;
		if (IsSetInVars(id))
		{
			RecalculateFns();
		}
		return true;
	}
	if (IsSetInVars(anotherId))
	{
		m_vars[id] = m_vars.at(anotherId);
		if (IsSetInVars(id))
		{
			RecalculateFns();
		}
		return true;
	}
	std::string msg("Идентификатор ");
	msg.append(anotherId).append(" не задан");
	PrintMsg(m_oStream, msg);
	return false;
}

double* Variables::FindVarOrFnPtr(std::string const& id)
{
	if (IsSetInVars(id))
	{
		return &m_vars.at(id);
	}

	if (IsSetInFns(id))
	{
		return &m_fns.at(id).result;
	}

	return nullptr;
}

bool Variables::CalculateFn(Fn& fn)
{
	if (fn.first && fn.second)
	{
		fn.result = fn.operation(*fn.first, *fn.second);
		return true;
	}
	if (fn.first && !fn.second)
	{
		fn.result = *fn.first;
		return true;
	}
	return false;
}

bool Variables::SetFn(std::string const& id, std::string const& first, std::string const& second, double (*Operation)(double, double))
{
	if (IsSetInVars(id) || IsSetInFns(id))
	{
		PrintMsg(m_oStream, "Идентификатор занят");
		return false;
	}
	Fn newFn;
	if (IsSetInFns(first) || IsSetInVars(first))
	{
		newFn.first = FindVarOrFnPtr(first);
	}
	else
	{
		std::string msg("Идентификатор ");
		msg.append(first).append(" не задан");
		PrintMsg(m_oStream, msg);
		return false;
	}
	if (Operation)
	{
		if (!(IsSetInFns(second) || IsSetInVars(second)))
		{
			std::string msg("Идентификатор ");
			msg.append(second).append(" не задан");
			PrintMsg(m_oStream, msg);
			return false;
		}
		newFn.second = FindVarOrFnPtr(second);
		newFn.operation = Operation;
	}
	CalculateFn(newFn);
	m_fns.insert(std::pair<std::string, Fn>(id, newFn));
	return true;
}

bool Variables::RecalculateFns()
{
	std::map<double const*, Fn*> IsFunction;
	std::map<double const*, bool> functionsPassed;
	std::stack<std::reference_wrapper<Fn>> recalculationProcedure;
	for (auto& pair : m_fns)
	{
		IsFunction.insert(std::pair<double* const, Fn* const>(&pair.second.result, &pair.second));
		functionsPassed.insert(std::pair<double* const, bool>(&pair.second.result, false));
		recalculationProcedure.push(pair.second);
	}
	for (auto& pair : m_vars)
	{
		functionsPassed.insert(std::pair<double* const, bool>(&pair.second, true));
	}
	while (!recalculationProcedure.empty())
	{
		Fn& top = recalculationProcedure.top().get();
		if (top.first && top.second)
		{
			if (functionsPassed.at(top.first) && functionsPassed.at(top.second))
			{
				CalculateFn(top);
				functionsPassed.at(&top.result) = true;
				recalculationProcedure.pop();
				continue;
			}
			if (!functionsPassed.at(top.second))
			{
				recalculationProcedure.push(*IsFunction.at(top.second));
			}
		}

		if (top.first && !top.second)
		{
			if (functionsPassed.at(top.first))
			{
				CalculateFn(top);
				functionsPassed.at(&top.result) = true;
				recalculationProcedure.pop();
				continue;
			}
		}
		if (!functionsPassed.at(top.first))
		{
			recalculationProcedure.push(*IsFunction.at(top.first));
		}
	}
	return true;
}

std::optional<double> Variables::GetVarValue(std::string const& id) const
{
	if (IsSetInVars(id))
	{
		return m_vars.at(id);
	}
	return std::nullopt;
}

std::optional<double> Variables::GetFnValue(std::string const& id) const
{
	if (IsSetInFns(id))
	{
		return m_fns.at(id).result;
	}
	return std::nullopt;
}

Vars const& Variables::GetAllVars() const { return m_vars; }
Fns const& Variables::GetAllFns() const { return m_fns; }
