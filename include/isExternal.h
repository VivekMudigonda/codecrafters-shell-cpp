#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#ifdef _WIN32
#include <io.h>
#define ACCESS _access
#define X_OK 4
#define PATH_SEPARATOR ';'
#define DIR_SEPARATOR '\\'
const std::string EXE_SUFFIX = ".exe";
#else
#include <unistd.h>
#define ACCESS access
#define PATH_SEPARATOR ':'
#define DIR_SEPARATOR '/'
const std::string EXE_SUFFIX = "";
#endif
std::string isExternal(const std::string &execName);