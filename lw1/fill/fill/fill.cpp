#include <fstream>
#include <iostream>
#include <optional>
#include <string>

const int COORD_MAX = 65;
const int COORD_MIN = 0;
//using PaintField = std::array<std::array<char, COORD_MAX>, COORD_MAX>;
char field[COORD_MAX][COORD_MAX];

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

bool ClearField()
{
	for (short i = 0; i < COORD_MAX; i++)
	{
		for (short j = 0; j < COORD_MAX; j++)
		{
			field[i][j] = ' ';
		}
	}
	return 1;
}

bool CopyFieldFromIS(std::istream& is)
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

struct Point
{
	short x = -1;
	short y = -1;
};

bool OnField(Point& p)
{
	return (p.x >= COORD_MIN && p.x < COORD_MAX
		&& p.y >= COORD_MIN && p.y < COORD_MAX);
}

bool fill(Point p)
{
	if (!(p.x >= COORD_MIN && p.x < COORD_MAX
		&& p.y >= COORD_MIN && p.y < COORD_MAX))
	{
		return 0;
	}
	if (field[p.y][p.x] == '#' || field[p.y][p.x] == '-')
	{
		return 0;
	}
	if (field[p.y][p.x] == ' ')
	{
		field[p.y][p.x] = '-';
	}
	fill({ p.x + 1, p.y });
	fill({ p.x, p.y + 1 });
	fill({ p.x - 1, p.y });
	fill({ p.x, p.y - 1 });

	return 1;
}

bool WriteField(std::ostream& os)
{
	for (short i = 0; i < COORD_MAX; i++)
	{
		for (short j = 0; j < COORD_MAX; j++)
		{
			if (!os.put(field[i][j]))
			{
				std::cout << "Failed to write data to output stream";
				return 0;
			}
		}
		os << std::endl;
	}
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
	ClearField();

	// Копирование данных из файла
	CopyFieldFromIS(input);

	// Заполнение поля
	for (short i = 0; i < COORD_MAX; i++)
	{
		for (short j = 0; j < COORD_MAX; j++)
		{
			if (field[i][j] == 'O')
			{
				fill({ j, i });
			}
		}
	}
	WriteField(output);
	return 0;
}
