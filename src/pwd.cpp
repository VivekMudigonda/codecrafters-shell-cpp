#include "globals.h"
std::string Pwd()
{
    std::string cwd = std::filesystem::current_path().string();
    std::cout << cwd << std::endl;
    return cwd;
}