#include <iostream>
#include <string>
#include <sstream>
#include <map>

typedef std::map<std::string, double> Var;

class Variables
{
public:
	int GetVariable(std::string const& var) const;
	bool SetVariable(std::string const& var, const double num);
	bool SetVariable(std::string const& var, std::string const& num);
	bool CreateVariable(std::string const& var);

private:
	Var m_variables;
};

enum class Operator
{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
};

enum class Action
{
	VAR,
	LET,
	FN,
};

class Calc
{
public:
	
	
private:
	Variables m_vars;

};

