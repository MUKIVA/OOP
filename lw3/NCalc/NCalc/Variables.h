#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>

const double DOUBLE_NAN = NAN;

struct Fn
{
	double* first = nullptr;
	double (*operation)(double a, double b) = nullptr;
	double* second = nullptr;
	double result = DOUBLE_NAN;
};

typedef std::map<std::string, double> Vars;
typedef std::map<std::string, Fn> Fns;

void PrintMsg(std::ostream& os, std::string const& msg);
void PrintMsg(std::ostream& os, const double msg);
std::string DoubleToString(double d);

// Дать адекватное имя классу
class Variables
{
public:
	std::optional<double> GetVarValue(std::string const& id) const;
	std::optional<double> GetFnValue(std::string const& id) const;
	Vars const& GetAllVars() const;
	Fns const& GetAllFns() const;
	bool CreateVar(std::string const& id);
	bool SetVar(std::string const& id, double const num);
	bool SetVar(std::string const& id, std::string const& anotherId);
	bool SetFn(std::string const& id, std::string const& first, std::string const& second, double (*Operation)(double, double));

	Variables(std::ostream& os);
	Variables();

private:
	bool IsSetInVars(std::string const& id) const;
	bool IsSetInFns(std::string const& id) const;
	bool CalculateFn(Fn& fn);
	bool RecalculateFns();
	double* FindVarOrFnPtr(std::string const& id);
	Vars m_vars;
	Fns m_fns;
	std::ostream& m_oStream;
};
