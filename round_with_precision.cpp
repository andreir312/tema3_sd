# include <iostream>

# include <cmath>

int main()
{
    double x = 9.33511;

    x = round(x * 100) / 100;

    std::cout << x << std::endl;

    return 0;
}
