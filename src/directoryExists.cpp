#include "globals.h"
bool directoryExists(const std::string &dirPath)
{
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(dirPath.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES)
        return false;

    return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;

#else

    struct stat info;
    if (stat(dirPath.c_str(), &info) != 0)
        return false;

    return S_ISDIR(info.st_mode);

#endif
}