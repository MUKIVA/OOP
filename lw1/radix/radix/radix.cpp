#include <iostream>
#include <string>
#include <optional>

const int minRadix = 2;
const int maxRadix = 36;


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
// Функция перевода из строки в число
int StringToInt(const std::string& str, int radix, bool& wasError)
{
    try
    {
        std::stoi(str, 0, radix);
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
    return std::stoi(str, 0, radix);
}

// Функция перевода из числа в строку
std::string IntToString(int n, int radix, bool& wasError)
{
    const std::string digists = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int digitsLength = digists.length() - 1;
    std::string result = "";

    if (n < 0)
    {
        n *= -1;
        result = "-";
    }
    // В случае если чило 0
    if (n == 0)
    {
        result = '0';
    }
    // Перевод чилсла
    while (n)
    {
        int curDigit = n % radix;
        if (curDigit < 0 || curDigit > n % radix)
        {
            std::cout << "Error while converting a number to a string";
            wasError = true;
            return "";
        }
        result = digists[curDigit] + result;
        n = n / radix;
    }
    if (result[result.length() - 1] == '-')
    {
        result = "-" + result.substr(0, result.find("-"));
    }
    return result;
}

int main(int argc, char* argv[])
{
    bool err = false;
    auto args = ParseArgs(argc, argv);
    
    // Проверка диапазона оснований
    int radix[2];
    radix[0] = StringToInt(args->sourceNotation, 10, err);
    if (err) return 1;
    radix[1] = StringToInt(args->destinationNotation, 10, err);
    if (err) return 1;
    for (int num : radix)
    {   
        if (num > maxRadix && num < minRadix)
        {
            std::cout << "One of the notations out of range" << std::endl;
            std::cout << "Please specify notation in the range from 2 to 36" << std::endl;
            err = true;
        }
    }

    // Перевод значения из числа в строку с конечным основанием
    
    int value = StringToInt(args->value, radix[0], err);
    if (err) return 1;
    std::string outStr = IntToString(value, radix[1], err);
    if (err) return 1;

    std::cout << outStr << std::endl;
    // Программа оказалась успешной
    return 0;
}
