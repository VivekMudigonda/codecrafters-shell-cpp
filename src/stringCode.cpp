#include "globals.h"

StringCode hashString(const std::string &str)
{
    if (str == "echo")
        return StringCode::echo;
    if (str == "type")
        return StringCode::type;
    if (str == "pwd")
        return StringCode::pwd;
    if (str == "cd")
        return StringCode::cd;
    return StringCode::unknown;
}