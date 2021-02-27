#include <iostream>
#include <optional>
#include <string>


const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Ivalid arguments count\n";
		std::cout << "Please use: radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];
	return args;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	const std::string VALID_CAHRS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::size_t unaryOperatorPos = str.find_last_of("+-");

	if (str.find_first_not_of(VALID_CAHRS.substr(0, radix) + "+-") != std::string::npos
		|| ((unaryOperatorPos != std::string::npos)
			&& (unaryOperatorPos != 0)))
	{
		std::cout << "An invalid character was found\n";
		wasError = true;
		return 1;
	}
	int result;
	try
	{
		result = std::stoi(str, 0, radix);
	}
	catch (const std::exception& ex)
	{
		std::string what = ex.what();
		if (what == "stoi argument out of range")
		{
			std::cout << "Value out of range\n";
		}
		if (what == "invalid stoi argument")
		{
			std::cout << "Incorrect arguments\n";
		}
		wasError = true;
		return 1;
	}
	return result;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	const std::string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	std::string result = "";

	if (n < 0)
		result = "-";

	if (n == 0)
		result = '0';

	int insertPos = result.length();

	while (n)
	{
		int curDigit = abs(n) % radix;
		if (curDigit < 0)
		{
			std::cout << "Error while converting a number to a string";
			wasError = true;
			return "";
		}
		result.insert(insertPos, 1, DIGITS[curDigit]);
		n /= radix;
	}

	return result;
}

int main(int argc, char* argv[])
{
	bool err = false;
	auto args = ParseArgs(argc, argv);

	int radix[2];
	radix[0] = StringToInt(args->sourceNotation, 10, err);
	if (err)
		return 1;
	radix[1] = StringToInt(args->destinationNotation, 10, err);
	if (err)
		return 1;
	for (int num : radix)
	{
		if (num > MAX_RADIX || num < MIN_RADIX)
		{
			std::cout << "One of the notations out of range" << std::endl
					  << "Please specify notation in the range from 2 to 36" << std::endl;
			return 1;
		}
	}

	int value = StringToInt(args->value, radix[0], err);
	if (err)
		return 1;
	std::string outStr = IntToString(value, radix[1], err);
	if (err)
		return 1;

	std::cout << outStr << std::endl;
	return 0;
}
