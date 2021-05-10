#include <string>
#include <map>

double Plus(double a, double b);
double Minus(double a, double b);
double Multiply(double a, double b);
double Divide(double a, double b);

class Fn
{
public:
	double* GetValue();
	double* GetFirst() const;
	double* GetSecond() const;
	bool SetFirst(double& num);
	bool SetSecond(double& num);
	bool SetOperation(std::string const& op);
	bool CalculateValue();

private:
	double m_value = nan("1");
	static std::map<std::string, double (*)(double a, double b)> const OPERATION_MAP;
	double (*m_operation)(double a, double b) = nullptr;
	double* m_firstArg = nullptr;
	double* m_secondArg = nullptr;
};
