#include "Calc.h"

std::map<std::string, CalcAction> const Calc::ParseAction = {
	{ "print", CalcAction::PRINT },
	{ "printfns", CalcAction::PRINT_FNS },
	{ "printvars", CalcAction::PRINT_VARS },
	{ "fn", CalcAction::FN },
	{ "var", CalcAction::VAR },
	{ "let", CalcAction::LET }
};

Calc::Calc()
	: m_is(std::cin)
	, m_os(std::cout)
{
}

Calc::Calc(std::istream& is)
	: m_is(is)
	, m_os(std::cout)
{
}

Calc::Calc(std::ostream& os)
	: m_is(std::cin)
	, m_os(os)
{
}

Calc::Calc(std::istream& is, std::ostream& os)
	: m_is(is)
	, m_os(os)
{
}

bool HandlePrintAct(Variables& v, std::istream& is)
{
	std::string id;
	is >> id;
	v.Print(id);
	return true;
}

bool HandleFnAct(Variables& v, std::istream& is)
{
	std::string valueAssignmentStr;
	is >> valueAssignmentStr;
	size_t delimiter = valueAssignmentStr.find('=');
	if (delimiter == std::string::npos)
	{
		PrintMsg(std::cout, "Неверный формат записи.\nИспользуйте <Имя функции>=<Идентификатор>[<Оператор><Идентификатор>]");
		return false;
	}
	std::string id = valueAssignmentStr.substr(0, delimiter);
	std::string value = valueAssignmentStr.substr(delimiter + 1);
	return v.SetFn(id, value);
}

bool HandleLetAct(Variables& v, std::istream& is)
{
	std::string valueAssignmentStr;
	is >> valueAssignmentStr;
	size_t delimiter = valueAssignmentStr.find('=');
	if (delimiter == std::string::npos)
	{
		PrintMsg(std::cout, "Неверный формат записи.\nИспользуйте <Имя переменной>=<Идентификатор> | <Имя переменной>=<Число>");
		return false;
	}
	std::string id = valueAssignmentStr.substr(0, delimiter);
	std::string value = valueAssignmentStr.substr(delimiter + 1);
	try
	{
		double dValue = std::stod(value);
		return v.SetVariable(id, dValue);
	}
	catch (const std::exception&)
	{
		return v.SetVariable(id, value);
	}
}

bool HandleVarAct(Variables& v, std::istream& is)
{
	std::string id;
	is >> id;
	return v.CreateVariable(id);
}

bool Calc::HandleAction(CalcAction const& act)
{
	switch (act)
	{
	case CalcAction::VAR:
		return HandleVarAct(m_vars, m_is);
		break;
	case CalcAction::LET:
		return HandleLetAct(m_vars, m_is);
		break;
	case CalcAction::FN:
		return HandleFnAct(m_vars, m_is);
		break;
	case CalcAction::PRINT:
		return HandlePrintAct(m_vars, m_is);
		break;
	case CalcAction::PRINT_VARS:
		m_vars.PrintVars();
		return true;
		break;
	case CalcAction::PRINT_FNS:
		m_vars.PrintFns();
		return true;
		break;
	default:
		break;
	}
	return false;
}

bool Calc::StartCalculating()
{
	std::string userCommand;
	while (m_is >> userCommand)
	{
		if (ParseAction.find(userCommand) != ParseAction.end())
		{
			HandleAction(ParseAction.at(userCommand));
		}
		else
		{
			m_os << "Неизвестная команда\n";
		}
	}
	return true;
}