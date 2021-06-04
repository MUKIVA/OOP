#include <vector>
#include <string>
#include <map>

const double DOUBLE_NAN = nan("1");

double Plus(double a, double b);
double Minus(double a, double b);
double Multiply(double a, double b);
double Divide(double a, double b);

struct Fn
{
	double* first = nullptr;
	double (*operation)(double a, double b) = nullptr;
	double* second = nullptr;
	double result = DOUBLE_NAN;
};

typedef std::map<std::string, double*> Vars;
typedef std::map<std::string, Fn> Fns;

class Variables
{
public:

private:
};