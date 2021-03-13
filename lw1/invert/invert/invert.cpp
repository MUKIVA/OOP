#include <iostream>
#include <string>
#include <optional>
#include <iomanip>
#include <fstream>
#include <array>

const int SIZE_3 = 3;
const int SIZE_2 = 2;
using Matrix3x3 = std::array<std::array<float, SIZE_3>, SIZE_3>;
using Matrix2x2 = std::array<std::array<float, SIZE_2>, SIZE_2>;
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

bool MatrixTranspose(Matrix3x3& matrix)
{
	for (int i = 0; i < SIZE_3; i++)
	{
		for (int j = i; j < SIZE_3; j++)
		{
			std::swap(matrix[i][j], matrix[j][i]);
		}
	}
	return 1;
}

bool PrintMatrix(Matrix3x3 matrix)
{
	for (int i = 0; i < SIZE_3; i++)
	{
		for (int j = 0; j < SIZE_3; j++)
		{
			std::cout << std::setprecision(3) << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	return 1;
}

float MatrixDeterminant3x3(Matrix3x3 matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[1][0] * matrix[2][1] * matrix[0][2]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[1][2] * matrix[2][1] * matrix[0][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2];
}

bool GetMinor(Matrix3x3& matrix, Matrix2x2& result, int i, int j)
{
	int m = 0, n = 0;
	for (int k = 0; k < SIZE_3; k++)
		if (k != i)
			for (int l = 0; l < SIZE_3; l++)
			{
				if (l != j)
				{
					result[m][n] = matrix[k][l];
					if (n < SIZE_3 - 2)
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

float MatrixDeterminant2x2(Matrix2x2& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool CoefficientMatrix(Matrix3x3& matrix, Matrix3x3& result)
{
	int sign = 1;
	for (int i = 0; i < SIZE_3; i++)
		for (int j = 0; j < SIZE_3; j++)
		{
			Matrix2x2 minor{ 0 };
			GetMinor(matrix, minor, i, j);
			result[i][j] = MatrixDeterminant2x2(minor) * sign;
			sign *= -1;
		}
	return 1;
}

bool GetMatrix3x3(std::string& fileName, Matrix3x3& matrix, Error& wasError)
{
	// подключение файла
	std::ifstream input(fileName);
	if (!input.is_open())
	{
		wasError.message = "Failed to open input file\n";
		return 0;
	}
	// чтение данных из файла
	for (int i = 0; i < SIZE_3; i++)
	{
		for (int j = 0; j < SIZE_3; j++)
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

bool InvertMatrix(Matrix3x3& matrix, Error wasError)
{
	float det = 0;
	if (!(det = MatrixDeterminant3x3(matrix)))
	{
		wasError.message = "The determinant is 0. The inverse matrix does not exist";
		return 0;
	}
	MatrixTranspose(matrix);
	Matrix3x3 coefMatrix{ 0 };
	CoefficientMatrix(matrix, coefMatrix);
	for (int i = 0; i < SIZE_3; i++)
		for (int j = 0; j < SIZE_3; j++)
			coefMatrix[i][j] /= det;
	matrix = coefMatrix;
	return 1;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	Error err;
	err.message = "";
	Matrix3x3 matrix { 0 }; 
	if (!GetMatrix3x3(args->matrixFileName, matrix, err))
	{
		std::cout << err.message;
		return 1;
	}
	
	if (!InvertMatrix(matrix, err))
	{
		std::cout << err.message;
		return 1;
	}
	PrintMatrix(matrix);
	return 0;
}