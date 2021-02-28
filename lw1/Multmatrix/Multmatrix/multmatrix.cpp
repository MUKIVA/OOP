#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <iomanip>

const int SIZE = 3;

struct Args
{
	std::string firstMatrixFileName;
	std::string secondMatrixFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count"
				  << "Please use: multmatrix.exe <matrix file1> <matrix file2>";
		return std::nullopt;
	}
	Args args;
	args.firstMatrixFileName = argv[1];
	args.secondMatrixFileName = argv[2];
	return args;
}

struct Error
{
	std::string message;
};

bool PrintMatrix(float (&matrix)[SIZE][SIZE])
{
	std::setprecision(3);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			std::cout << std::setw(10) << std::left << matrix[i][j];
		}
		std::cout << std::endl;
	}
		
	return 1;
}

bool MatrixMultiplication3x3(float (&firstMatrix)[SIZE][SIZE], float (&secondMatrix)[SIZE][SIZE], float (&result)[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			result[i][j] = firstMatrix[i][0] * secondMatrix[0][j]
					     + firstMatrix[i][1] * secondMatrix[1][j]
						 + firstMatrix[i][2] * secondMatrix[2][j];
		}
	}
	return 1;
}

bool GetMatrix3x3(std::string & fileName, float (&matrix)[SIZE][SIZE], Error& wasError)
{
	// подключение файла
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		wasError.message = "Failed to open input file\n";
		return 0;
	}
	// чтение данных из файла
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{	
			if (!(input >> matrix[i][j]))
			{
				wasError.message = "Failed to read data from input file\n";
				return 0;
			}
		}
	}
	if (!input.eof())
	{
		wasError.message = "Wrong matrix format\n";
		return 0;
	}
	input.close();
	return 1;
}


int main(int argc, char* argv[])
{
	// Парсинг аргументов
	auto args = ParseArgs(argc, argv);
	Error err;
	err.message = "";
	float firstMatrix[SIZE][SIZE]{ 0 };
	float secondMatrix[SIZE][SIZE]{ 0 };
	// Получение матриц
	if (!GetMatrix3x3(args->firstMatrixFileName, firstMatrix, err))
	{
		std::cout << err.message;
		return 1;
	}
	if (!GetMatrix3x3(args->secondMatrixFileName, secondMatrix, err))
	{
		std::cout << err.message;
		return 1;
	}
	// Перемножение матриц
	float result[SIZE][SIZE]{ 0 };
	MatrixMultiplication3x3(firstMatrix, secondMatrix, result);
	PrintMatrix(result);


	return 0;
}