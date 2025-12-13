#include "globals.h"
void Echo()
{
    for (int i = 1; i < args.size(); i++)
    {
        std::cout << args[i] << " ";
    }
    std::cout << std::endl;
}