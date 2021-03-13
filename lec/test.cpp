#include <iostream>

using namespace std;

int count = 0;

int NearestSquare(int num)
{
    int res = 1;
    while (res*res <= num)
    {
        res++;
    }
    return res - 1;
}

bool CountSum(int num)
{
    if (num = 0)
    {
        return 1;
    }
    int next = NearestSquare(num);
    cout << next;
    CountSum(num - next * next);
    count++;
    return 0;
}

int main(int argc, char* argv[])
{
    int num = 0;
    cin >> num;
    CountSum(num);
    cout << endl << count << endl;


}