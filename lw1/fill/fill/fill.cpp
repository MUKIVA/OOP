#include <iostream>
#include <optional>
#include <fstream>
#include <string>
#include <array>

const int COORD_MAX = 100;
const int COORD_MIN = 0;
using PaintField = std::array<std::array<char, COORD_MAX>, COORD_MAX>;
PaintField field;

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid argumetns coutn\n"
				  << "Please use: fill.exe <input file> <output file>";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

bool ClearField(PaintField& field)
{
	for (std::array<char, COORD_MAX>& row : field)
	{
		for (char& ch : row)
		{
			ch = ' ';
		}
	}
	return 1;
}

bool CopyFieldFromIS(PaintField& field, std::istream& is)
{
	std::string lineContent;
	int row = 0;
	while (row != COORD_MAX && getline(is, lineContent))
	{
		for (int column = 0; column < COORD_MAX && column < lineContent.length(); column++)
		{
			field[row][column] = lineContent[column];
		}
		row++;
	}

	if (is.bad())
	{
		std::cout << "Failed to read data from input stream" << std::endl;
		return 0;
	}
	return 1;
}

bool fill(int row, int column, const int rowOffset, const int columnOffset)
{
	if ((row + rowOffset >= COORD_MAX || row + rowOffset < COORD_MIN)
		|| (column + columnOffset >= COORD_MAX || column + columnOffset < COORD_MIN)
		|| (columnOffset > COORD_MAX || rowOffset > COORD_MAX))
	{
		//std::cout << "close";
		return 0;
	}
	if ((field[row + rowOffset][column + columnOffset] != ' '))
	{
		//std::cout << "close";
		return 0;
	}
	field[row + rowOffset][column + columnOffset] = '-';
	fill(row, column, rowOffset + 1, columnOffset);
	fill(row, column, rowOffset - 1, columnOffset);
	fill(row, column, rowOffset, columnOffset + 1);
	fill(row, column, rowOffset, columnOffset - 1);

	return 1;
}

bool fill(int row, int column)
{
	if (field[row][column] != 'O')
	{
		return 0;
	}
	int rowOffset = 0, columnOffset = 0;
	fill( row, column, rowOffset + 1, columnOffset);
	fill( row, column, rowOffset - 1, columnOffset);
	fill( row, column, rowOffset, columnOffset + 1);
	fill( row, column, rowOffset, columnOffset - 1);
	return 1;
}

bool WriteField(PaintField& field, std::ostream& os)
{
	for (std::array<char, COORD_MAX>& row : field)
	{
		for (char ch : row)
		{
			if (!os.put(ch))
			{
				std::cout << "Failed to write data to output stream";
				return 0;
			}
		}
		os << std::endl;
	}
	return 1;
}

bool Test(PaintField f, int i)
{
	std::cout << "Вошел\n";
	if (i != 99)
	{
		Test(f, i + 1);
	}
	std::cout << "clear\n";
	return 1;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	
	std::ifstream input(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open file for reading\n";
		return 1;
	}

	std::ofstream output(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open file for writing\n";
		return 1;
	}
	
	// заполнение поля пробелами
	ClearField(field);

	// Копирование данных из файла
	CopyFieldFromIS(field, input);

	// Заполнение поля
	//Test(field, 0);
	for (int i = 0; i < COORD_MAX; i++)
	{
		for (int j = 0; j < COORD_MAX; j++)
		{
			if (field[i][j] == 'O')
			{
				fill(i, j);
			}
		}
	}
	WriteField(field, output);
	return 0;
}