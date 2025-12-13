#include "isExternal.h"

std::string isExternal(const std::string &execName)
{
    const char *pathEnv = std::getenv("PATH");
    if (!pathEnv)
    {
        std::cerr << "Error: PATH environment variable is not set." << std::endl;
        return "";
    }

    std::string path = pathEnv;
    std::string candidateName = execName;

#ifdef _WIN32
    if (candidateName.size() < 4 ||
        candidateName.substr(candidateName.size() - 4) != ".exe")
    {
        candidateName += ".exe";
    }
#endif

    size_t start = 0;
    size_t end = 0;

    while ((end = path.find(PATH_SEPARATOR, start)) != std::string::npos)
    {
        std::string dir = path.substr(start, end - start);
        std::string fullPath = dir + DIR_SEPARATOR + candidateName;

        if (ACCESS(fullPath.c_str(), X_OK) == 0)
        {
            return fullPath;
        }

        start = end + 1;
    }

    std::string lastDir = path.substr(start);
    std::string fullPath = lastDir + DIR_SEPARATOR + candidateName;

    if (ACCESS(fullPath.c_str(), X_OK) == 0)
    {
        return fullPath;
    }

    return "";
}