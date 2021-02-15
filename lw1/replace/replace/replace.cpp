#include <iostream>
#include <string>
#include <optional>
#include <fstream>

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
        std::cout << "Invalid argumets count\n";
        std::cout << "Please use: replace.exe <input file> <output file> <search string> <replace string>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    args.searchString = argv[3];
    args.replaceString = argv[4];
    return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args) return 1;

    if (args->searchString.length() == 0)
    {
        std::cout << "Search string argument is not defined\n";
        return 1;
    }
    
    // Open file for read
    std::ifstream input;
    input.open(args->inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "'for reading\n";
        return 1;
    }
    // Open file for write
    std::ofstream output;
    output.open(args->outputFileName);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << args->inputFileName << "'for writing\n";
        return 1;
    }
    // Get string from input file
    std::string fileContent;
    while (getline(input, fileContent))
    {
        // replace
        while (fileContent.find(args->searchString) != -1)
        {
            output << fileContent.substr(0, fileContent.find(args->searchString)) + args->replaceString;
            fileContent = fileContent.substr(fileContent.find(args->searchString) + args->searchString.length(), -1);
        }
        output << fileContent + "\n";
    }
    
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
