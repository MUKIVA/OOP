#include <iostream>
#include <optional>
#include <string>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;
const std::string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Args
{
	int sourceNotation = 0;
	int destinationNotation = 0;
	std::string value;
};

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;
	if (radix < 2 || radix > 36)
	{
		std::cout << "One of the notations out of range" << std::endl
				  << "Please specify notation in the range from 2 to 36" << std::endl;
		wasError = true;
		return 0;
	}

	if (str.length() == 0)
	{
		wasError = true;
		std::cout << "Incorrect arguments\n";
		return 1;
	}
	const std::string SIGNS_CHARS = "+-";
	const size_t NPOS = std::string::npos;

	std::size_t unaryOperatorPos = str.find_last_of(SIGNS_CHARS);

	if (str.find_first_not_of(DIGITS.substr(0, radix) + "+-") != NPOS
		|| ((unaryOperatorPos != NPOS)
			&& (unaryOperatorPos != 0)))
	{
		std::cout << "An invalid character was found\n";
		wasError = true;
		return 1;
	}

	long long int result = 0;
	int sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
	}

	for (char digit : str)
	{
		if (SIGNS_CHARS.find(digit) != NPOS)
			continue;
		result *= radix;
		result += DIGITS.find(digit);
		if ((sign == -1 && result > abs((long long int)INT_MIN))
			|| sign == 1 && result > INT_MAX)
		{
			wasError = true;
			std::cout << "Value out of range\n";
			return 1;
		}
	}
	
	return (int)(result * sign);
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = false;
	if (radix < 2 || radix > 36)
	{
		std::cout << "One of the notations out of range" << std::endl
				  << "Please specify notation in the range from 2 to 36" << std::endl;
		wasError = true;
		return "";
	}

	std::string result = "";

	if (n < 0)
		result = "-";

	if (n == 0)
		result = '0';

	size_t insertPos = result.length();

	while (n)
	{
		int curDigit = abs(n) % radix;	
		result.insert(insertPos, 1, DIGITS[curDigit]);
		n /= radix;
	}
	return result;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Ivalid arguments count\n";
		std::cout << "Please use: radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}
	Args args;
	bool err;
	args.sourceNotation = StringToInt(argv[1], 10, err);
	if (err)
	{
		return std::nullopt;
	}
	args.destinationNotation = StringToInt(argv[2], 10, err);
	if (err)
	{
		return std::nullopt;
	}
	args.value = argv[3];
	return args;
}

std::string ConvertRadix(const int from, const int to, const std::string& value)
{
	bool err;
	int number = StringToInt(value, from, err);
	if (err)
		return "";
	std::string result = IntToString(number, to, err);
	if (err)
		return "";
	return result;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		std::cout << "Invalid arguments\n";
		return 1;
	}
	std::string outStr = ConvertRadix(args->sourceNotation, args->destinationNotation, args->value);
	if (outStr == "")
	{
		return 1;
	}
	std::cout << outStr << std::endl;
	return 0;
}
