#include "globals.h"
#include "isExternal.cpp"

std::unordered_map<std::string, bool> isBuiltin = {{"echo", true}, {"exit", true}, {"type", true}, {"pwd", true}, {"cd", true}};
void Type()
{
    std::string extPath = isExternal(args[1]);
    if (isBuiltin[args[1]])
    {
        std::cout << args[1] << " is a shell builtin" << std::endl;
    }
    else if (extPath != "")
    {
        std::cout << args[1] << " is " << extPath << std::endl;
    }
    else
    {
        std::cout << args[1] << " not found" << std::endl;
    }
}