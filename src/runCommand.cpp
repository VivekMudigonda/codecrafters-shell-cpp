#include "globals.h"
#include "redirect.h"
int runCommand(std::string program, Redirect &r)
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

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hErr = GetStdHandle(STD_ERROR_HANDLE);

    HANDLE fileOut = nullptr;
    HANDLE fileErr = nullptr;

    if (!r.out.empty()) {
        fileOut = CreateFileA(
            r.out.c_str(),
            GENERIC_WRITE,
            FILE_SHARE_READ,
            nullptr,
            r.appendOut ? OPEN_ALWAYS : CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        if (r.appendOut)
            SetFilePointer(fileOut, 0, nullptr, FILE_END);
        hOut = fileOut;
    }

    if (r.errToOut) {
        hErr = hOut;
    }
    else if (!r.err.empty()) {
        fileErr = CreateFileA(
            r.err.c_str(),
            GENERIC_WRITE,
            FILE_SHARE_READ,
            nullptr,
            r.appendErr ? OPEN_ALWAYS : CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            nullptr
        );
        if (r.appendErr)
            SetFilePointer(fileErr, 0, nullptr, FILE_END);
        hErr = fileErr;
    }

    STARTUPINFOA si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hOut;
    si.hStdError  = hErr;
    si.hStdInput  = GetStdHandle(STD_INPUT_HANDLE);

    if (!CreateProcessA(
            nullptr,
            cmdLine.data(),
            nullptr,
            nullptr,
            TRUE,
            0,
            nullptr,
            nullptr,
            &si,
            &pi))
        return -1;

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode = 0;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    if (fileOut) CloseHandle(fileOut);
    if (fileErr) CloseHandle(fileErr);

    return static_cast<int>(exitCode);

#else
    std::vector<char*> argv;
    argv.push_back(const_cast<char*>(program.c_str()));
    for (auto &arg : args)
        argv.push_back(const_cast<char*>(arg.c_str()));
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid == 0) {
        int fd;

        if (!r.out.empty()) {
            int flags = O_WRONLY | O_CREAT | (r.appendOut ? O_APPEND : O_TRUNC);
            fd = open(r.out.c_str(), flags, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        if (r.errOut) {
            dup2(STDOUT_FILENO, STDERR_FILENO);
        }
        else if (!r.err.empty()) {
            int flags = O_WRONLY | O_CREAT | (r.appendErr ? O_APPEND : O_TRUNC);
            fd = open(r.err.c_str(), flags, 0644);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        execvp(program.c_str(), argv.data());
        _exit(1);
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return -1;
#endif
}
