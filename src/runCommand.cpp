#include "globals.h"
int runCommand(std::string program)
{
#ifdef _WIN32
    std::string cmdLine = "\"" + program + "\"";

    for (const auto &arg : args) {
        cmdLine += " \"";
        for (char c : arg) {
            if (c == '"') cmdLine += "\\\"";
            else cmdLine += c;
        }
        cmdLine += "\"";
    }

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);

    if (!CreateProcessA(
            nullptr,
            cmdLine.data(),
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi))
    {
        std::cerr << "CreateProcess failed\n";
        return -1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return static_cast<int>(exitCode);

#else
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(program.c_str()));
    for (auto &arg : args)
        argv.push_back(const_cast<char*>(arg.c_str()));

    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        execvp(program.c_str(), argv.data());
        perror("execvp");
        _exit(1);
    }
    else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        return -1;
    }
    else {
        perror("fork");
        return -1;
    }
#endif
}