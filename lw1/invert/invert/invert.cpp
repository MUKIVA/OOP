#include <iostream>
#include <string>
#include <optional>
#include <iomanip>
#include <fstream>

const int SIZE = 3;

struct Args
{
	std::string matrixFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count"
				  << "Please use: multmatrix.exe <matrix file1> <matrix file2>";
		return std::nullopt;
	}
	Args args;
	args.matrixFileName = argv[1];
	return args;
}

struct Error
{
	std::string message;
};

bool MatrixTranspose(float (&matrix)[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = i; j < SIZE; j++)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}
	return 1;
}

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

float MatrixDeterminant3x3(float (&matrix)[SIZE][SIZE])
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[1][2] * matrix[2][1] * matrix[0][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2];
}

bool GetMinor(float (&matrix)[SIZE][SIZE], float (&result)[SIZE - 1][SIZE - 1], int i, int j)
{
	int m = 0, n = 0;
	for (int k = 0; k < SIZE; k++)
		if (k != i)
			for (int l = 0; l < SIZE; l++)
			{
				if (l != j)
				{
					result[m][n] = matrix[k][l];
					if (n < SIZE - 2)
						n++;
					else
					{
						n = 0;
						m++;
					}
				}
			}
	return 1;
}

float MatrixDeterminant2x2(float (&matrix)[SIZE - 1][SIZE - 1])
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool CoefficientMatrix(float (&matrix)[SIZE][SIZE], float (&result)[SIZE][SIZE])
{
	int sign = 1;
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
		{
			float minor[SIZE - 1][SIZE - 1]{ 0 };
			GetMinor(matrix, minor, i, j);
			result[i][j] = MatrixDeterminant2x2(minor) * sign;
			sign *= -1;
		}
	return 1;
}

bool GetMatrix3x3(std::string& fileName, float (&matrix)[SIZE][SIZE], Error& wasError)
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
	auto args = ParseArgs(argc, argv);
	Error err;
	err.message = "";
	float matrix[SIZE][SIZE]{ 0 };
	if (!GetMatrix3x3(args->matrixFileName, matrix, err))
	{
		std::cout << err.message;
		return 1;
	}
	float det = 0;
	if (!(det = MatrixDeterminant3x3(matrix)))
	{
		std::cout << "The determinant is 0. The inverse matrix does not exist";
		return 1;
	}

	MatrixTranspose(matrix);
	float coefMatrix[SIZE][SIZE];
	CoefficientMatrix(matrix, coefMatrix);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			coefMatrix[i][j] /= det;
	PrintMatrix(coefMatrix);
	return 0;
}