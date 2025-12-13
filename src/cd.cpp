#include "globals.h"
#include "home.h"
bool Cd(const std::string &dirPath)
{
    namespace fs = std::filesystem;

    try
    {
        std::string expanded = expandHomeDirectory(dirPath);
        fs::path p = fs::absolute(expanded);
        if (!fs::exists(p) || !fs::is_directory(p))
        {
            std::cout << "cd: " << dirPath << ": No such file or directory\n";
            return false;
        }
        fs::current_path(p);
        return true;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cout << "cd: " << dirPath << ": " << e.what() << "\n";
        return false;
    }
}