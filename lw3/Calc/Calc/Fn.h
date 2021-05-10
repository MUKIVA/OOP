#include <string>
#include <map>

enum class Operation
{
	NONE,
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDE,
};

class Fn
{
public:
	Operation GetOperation() const;
	double GetValue() const;
	std::string GetFirst() const;
	std::string GetSecond() const;
	bool SetFirst(std::string const& arg);
	bool SetValue(double num);
	bool SetSecond(std::string const& arg);
	bool SetOperation(std::string const& op);

private:
	static std::map<std::string, Operation> const OPERATION_MAP;
	Operation m_operation = Operation::NONE;
	std::string m_firstArg;
	std::string m_secondArg;
	double m_value = nan("1");
};
