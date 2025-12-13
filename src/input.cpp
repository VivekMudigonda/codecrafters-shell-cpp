#include "globals.h"
void Input(std::vector<std::string> &args, const std::string &S, char delimeter)
{
    std::stringstream s(S);

    std::string inputPart;

    while (getline(s, inputPart, delimeter))
    {
        args.push_back(inputPart);
    }
}