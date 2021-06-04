#include "Variables.h"

double Plus(double a, double b);
double Minus(double a, double b);
double Multiply(double a, double b);
double Divide(double a, double b);

enum class CalcAction
{
	VAR,
	LET,
	FN,
	PRINT,
	PRINT_VARS,
	PRINT_FNS,
	UNDEFINED,
};

class Calc
{
public:
	bool CommitVarAction();
	bool CommitLetAction();
	bool CommitFnAction();
	void MakePrintAction();
	void MakePrintVarsAction();
	void MakePrintFnsAction();
	void StartCalculating();
	void HandleAction(CalcAction act);

	Calc();
	Calc(std::istream& is);
	Calc(std::ostream& os);
	Calc(std::istream& is, std::ostream& os);

private:
	static std::map<std::string, double (*)(double, double)> const OPERATION_MAP;
	static std::map<std::string, CalcAction> const ParseAction;
	std::istream& m_is;
	std::ostream& m_os;
	Variables m_variables;
};
