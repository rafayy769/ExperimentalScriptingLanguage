#include <string>

std::string rstrip(std::string str)
{
    // Remove trailing whitespace
    while (str.back() == ' ')
    {
        str.pop_back();
    }

    return str;
}