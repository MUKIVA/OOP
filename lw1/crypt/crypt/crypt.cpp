#include <iostream>
#include <string>
#include <optional>

const int KEY_MAX = 255;
const int KEY_MIN = 0;

struct Args
{
	std::string mode;
	std::string inputFileName;
	std::string outputFileName;
	int key;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid arguments count\n"
				  << "Please use: crypt.exe <crypt/decrypt> <input file> <output file> <key>\n";
		return std::nullopt;
	}
	Args args;
	args.mode = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];
	args.key = std::stoi(argv[4]);
	if (args.key > KEY_MAX || args.key < KEY_MIN)
	{
		std::cout << "The argument \"key\" must be in the range from 0 to 255\n";
		return std::nullopt;
	}
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}


	return 0;
}