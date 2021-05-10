#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "Variables.h"

enum class CalcAction
{
	VAR,
	LET,
	FN,
	PRINT,
	PRINT_VARS,
	PRINT_FNS,
};

class Calc
{
public:
	Calc();
	Calc(std::istream& is);
	Calc(std::ostream& os);
	Calc(std::istream& is, std::ostream& os);
	bool HandleAction(CalcAction const& act);
	bool StartCalculating();

private:
	Variables m_vars;
	std::istream& m_is;
	std::ostream& m_os;
	static std::map<std::string, CalcAction> const ParseAction;
};
