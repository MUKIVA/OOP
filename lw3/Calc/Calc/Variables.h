#include "Fn.h"

typedef std::map<std::string, Fn> Fns;
typedef std::map<std::string, double> Var;
void PrintMsg(std::ostream& os, std::string const& msg);
void PrintMsg(std::ostream& os, const double msg);

class Variables
{
public:
	double GetVariableValue(std::string const& var) const;
	double GetFnValue(std::string const& fn) const;
	bool CalculateFn(std::string const& fn);
	bool SetFn(std::string const& fnName, std::string const& args);
	bool SetVariable(std::string const& var, const double num);
	bool SetVariable(std::string const& var, std::string const& num);
	bool CreateVariable(std::string const& var);
	bool RecalculateFns(std::string const& var);
	void PrintVars();
	void PrintFns();
	void Print(std::string const& id);
	Variables(std::ostream& os);
	Variables();

private:
	Var m_variables;
	Fns m_functions;
	std::ostream& m_oStream;
};
