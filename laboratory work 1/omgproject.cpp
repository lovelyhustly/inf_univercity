#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
    float x, y;

    const double PI = 3.141592653589793;
    
    std::cout << "Input X and Y" << "\n";
    std::cin >> x >> y;


    double R = 1 / tan(PI * x / 4);
    double S = sqrt(sqrt(y)) * pow(2, (1 / y));
    double C = std::max(R, S);

    std::cout << "R = " << R << "\n";
    std::cout << "S = " << S << "\n";
    std::cout << "C = " << C << "\n";

    std::cout << "Tap ENTER to close.....";
    system("pause");

    return 0;
}
