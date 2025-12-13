#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#endif

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <sstream>
#include <functional>
#include <filesystem>
extern std::vector<std::string> args;

enum class StringCode
{
    echo,
    type,
    pwd,
    cd,
    unknown
};
