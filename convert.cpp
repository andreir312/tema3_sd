# include <ctime>

# include <string>

std::string convert(int timestamp)
{
    time_t aux = timestamp;

    struct tm *tmp;

    char buffer[5];

    tmp = gmtime(&aux);

    strftime(buffer, 5, "%Y", tmp);

    return year(buffer);
}
