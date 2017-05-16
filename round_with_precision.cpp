# include <iostream>

# include <cmath>

# include <string>

# include <sstream>

int main()
{
    double x = 9.33511;

    x = round(x * 100) / 100;

    std::ostringstream s;

    s << x;

    std::cout << s.str() << std::endl;

    return 0;
}
