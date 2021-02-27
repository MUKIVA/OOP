#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argumets count\n"
				  << "Please use: replace.exe <input file> <output file> <search "
					 "string> <replace string>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

int ReplaeceAll(std::istream& input, std::ostream& output,
	std::optional<Args>& args)
{
	std::string fileLineContent;
	while (getline(input, fileLineContent))
	{
		std::size_t find = 0;
		while ((find = fileLineContent.find(args->searchString))
				!= std::string::npos
			&& args->searchString != "")
		{
			output << fileLineContent.substr(0, find) + args->replaceString;
			fileLineContent = fileLineContent.substr(find + args->searchString.length());
		}
		output << fileLineContent + "\n";
	}
	return 0;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
		return 1;

	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "'for reading\n";
		return 1;
	}

	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "'for writing\n";
		return 1;
	}

	ReplaeceAll(input, output, args);

	if (!output.flush())
	{
		std::cout << "failed to write data to output file";
		return 1;
	}

	if (input.bad())
	{
		std::cout << "failed to read data from input file";
		return 1;
	}

	std::cout << "Program completed successfully";
	return 0;
}
