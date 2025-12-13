#include "globals.h"
std::string expandHomeDirectory(const std::string &path)
{
    if (path.empty() || path[0] != '~')
        return path;

    std::string home;

#ifdef _WIN32
    const char *userProfile = std::getenv("USERPROFILE");
    const char *homeDrive = std::getenv("HOMEDRIVE");
    const char *homePath = std::getenv("HOMEPATH");

    if (userProfile)
        home = userProfile;
    else if (homeDrive && homePath)
        home = std::string(homeDrive) + std::string(homePath);
    else
    {
        std::cerr << "Error: HOME directory not found on Windows.\n";
        return "";
    }

#else
    const char *homeEnv = std::getenv("HOME");
    if (homeEnv)
        home = homeEnv;
    else
    {
        std::cerr << "Error: HOME environment variable is not set.\n";
        return "";
    }
#endif
    return home + path.substr(1);
}