#include "Fn.h"
#include <map>
#include <iostream>

typedef std::map<std::string, double> Vars;
typedef std::map<std::string, Fn> Fns;
void PrintMsg(std::ostream& os, std::string const& msg);
void PrintMsg(std::ostream& os, const double msg);

class Variables
{
public:
	bool CreateVariable(std::string const& var);
	bool SetVariable(std::string const& var, const double num);
	bool SetVariable(std::string const& var, std::string const& num);
	bool SetFn(std::string const& fnName, std::string const& args);
	bool PrintVars();
	bool PrintFns();
	bool Print(std::string const& id);

	Variables(std::ostream& os);
	Variables();
private:
	Vars m_vars;
	Fns m_fns;
	std::ostream& m_oStream;
};