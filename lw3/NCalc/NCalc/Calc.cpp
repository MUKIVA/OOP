#include "Calc.h"
#include <regex>

std::map<std::string, double (*)(double a, double b)> const Calc::OPERATION_MAP = {
	{ "+", Plus },
	{ "-", Minus },
	{ "*", Multiply },
	{ "/", Divide },
};

std::map<std::string, CalcAction> const Calc::ParseAction = {
	{ "print", CalcAction::PRINT },
	{ "printfns", CalcAction::PRINT_FNS },
	{ "printvars", CalcAction::PRINT_VARS },
	{ "fn", CalcAction::FN },
	{ "var", CalcAction::VAR },
	{ "let", CalcAction::LET }
};

double Plus(double a, double b) { return (!isnan(a) && !isnan(b)) ? a + b : DOUBLE_NAN; }
double Minus(double a, double b) { return (!isnan(a) && !isnan(b)) ? a - b : DOUBLE_NAN; }
double Multiply(double a, double b) { return (!isnan(a) && !isnan(b)) ? a * b : DOUBLE_NAN; }
double Divide(double a, double b) { return (!isnan(a) && !isnan(b)) ? a / b : DOUBLE_NAN; }

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

void Calc::MakePrintAction()
{
	std::string id;
	if (!(m_is >> id))
	{
		PrintMsg(m_os, "Неверный формат\n Используйте \"print <id>\"");
		return;
	}
	auto var = m_variables.GetVarValue(id);
	auto fn = m_variables.GetFnValue(id);
	if (var)
	{
		PrintMsg(m_os, var.value());
		return;
	}
	if (fn)
	{
		PrintMsg(m_os, fn.value());
		return;
	}
	std::string msg("Идентификатор ");
	msg.append(id).append(" не задан");
	PrintMsg(m_os, msg);
}

void Calc::MakePrintVarsAction()
{
	Vars v = m_variables.GetAllVars();
	for (auto& pair : v)
	{
		std::string msg(pair.first);
		msg.append(":").append(DoubleToString(pair.second));
		PrintMsg(m_os, msg);
	}
}

void Calc::MakePrintFnsAction()
{
	Fns f = m_variables.GetAllFns();
	for (auto& pair : f)
	{
		std::string msg(pair.first);
		msg.append(":").append(DoubleToString(pair.second.result));
		PrintMsg(m_os, msg);
	}
}

bool Calc::CommitVarAction()
{
	std::string id;
	if (!(m_is >> id))
	{
		PrintMsg(m_os, "Неверный формат\n Используйте \"var <id>\"");
		return false;
	}
	return m_variables.CreateVar(id);
}

bool Calc::CommitLetAction()
{
	std::string expression;
	size_t delimiterPos;
	if (!(m_is >> expression && !((delimiterPos = expression.find("=")) == std::string::npos)))
	{
		PrintMsg(m_os, "Неверный формат\n Используйте \"let <id1>=<id2> | <id1>=<num>\"");
		return false;
	}

	std::string id = expression.substr(0, delimiterPos);
	std::string value = expression.substr(delimiterPos + 1);
	try
	{
		double dValue = std::stod(value);
		return m_variables.SetVar(id, dValue);
	}
	catch (const std::exception&)
	{
		return m_variables.SetVar(id, value);
	}
}

bool Calc::CommitFnAction()
{
	std::string expression;
	if (!(m_is >> expression))
	{
		PrintMsg(m_os, "Неверный формат\n Используйте \"fn <id1>=<id2>[<operation><id3>]\"");
		return false;
	}
	std::regex argsReg("([a-zA-Z]\\w*)"
					   "(=)"
					   "([a-zA-Z]\\w*)"
					   "(([+-/\\*])([a-zA-Z]\\w*))?");
	const int ID_INDEX = 1;
	const int FIRST_INDEX = 3;
	const int OPERATION_INDEX = 5;
	const int SECOND_INDEX = 6;
	std::smatch argsMatch;
	if (std::regex_match(expression, argsMatch, argsReg))
	{
		std::string id = argsMatch[ID_INDEX].str();
		std::string first = argsMatch[FIRST_INDEX].str();
		std::string second;
		double (*operation)(double, double) = nullptr;
		if (!argsMatch[OPERATION_INDEX].str().empty() && !argsMatch[SECOND_INDEX].str().empty())
		{
			operation = OPERATION_MAP.at(argsMatch[OPERATION_INDEX].str());
			second = argsMatch[SECOND_INDEX].str();
		}
		m_variables.SetFn(id, first, second, operation);
		return true;
	}
	PrintMsg(m_os, "Неверный формат\n Используйте \"fn <id1>=<id2>[<operation><id3>]\"");
	return false;
}

void Calc::HandleAction(CalcAction act)
{
	switch (act)
	{
	case CalcAction::VAR:
		CommitVarAction();
		break;
	case CalcAction::LET:
		CommitLetAction();
		break;
	case CalcAction::FN:
		CommitFnAction();
		break;
	case CalcAction::PRINT:
		MakePrintAction();
		break;
	case CalcAction::PRINT_VARS:
		MakePrintVarsAction();
		break;
	case CalcAction::PRINT_FNS:
		MakePrintFnsAction();
		break;
	default:
		PrintMsg(m_os, "Неизвестная команда");
		break;
	}
}

void Calc::StartCalculating()
{
	std::string userCommand;
	while (m_is >> userCommand)
	{
		(ParseAction.find(userCommand) != ParseAction.end())
			? HandleAction(ParseAction.at(userCommand))
			: HandleAction(CalcAction::UNDEFINED);
	}
}
