#include <ctime>

#include <string>

#include <iostream>

int main()
{
    int rawtime = 725068800;

    time_t aux = rawtime;

    struct tm *timeinfo;

    char buffer[5];

    timeinfo = gmtime(&aux);

    strftime(buffer, 5, "%Y", timeinfo);

    std::string s(buffer);

    std::cout << s << std::endl;

    return 0;
}
