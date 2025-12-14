#include "redirect.h"

namespace {
    std::streambuf* oldOut = nullptr;
    std::streambuf* oldErr = nullptr;

    std::ofstream outFile;
    std::ofstream errFile;
}


Redirect pareseRedirects(std::vector<std::string> &args)
{
    Redirect r;
    size_t i = 0;
    while (i < args.size())
    {
        if ((args[i] == ">" || args[i] == "1>") && i + 1 < args.size())
        {
            r.out = args[i + 1];
            args.erase(args.begin() + i, args.begin() + i + 2);
        }
        else if (args[i] == "2>" && i + 1 < args.size())
        {
            r.err = args[i + 1];
            args.erase(args.begin() + i, args.begin() + i + 2);
        }
        else if ((args[i] == ">>" || args[i] == "1>>") && i + 1 < args.size())
        {
            r.out = args[i + 1];
            r.appendOut = true;
            args.erase(args.begin() + i, args.begin() + i + 2);
        }
        else if (args[i] == "2>>" && i + 1 < args.size())
        {
            r.err = args[i + 1];
            r.appendErr = true;
            args.erase(args.begin() + i, args.begin() + i + 2);
        }
        else if (args[i] == "2>&1")
        {
            r.errOut = true;
            args.erase(args.begin() + i);
        }
        else
        {
            i++;
        }
    }
    return r;
}
void beginRedirect()
{
    if (!oldOut)
        oldOut = std::cout.rdbuf();
    if (!oldErr)
        oldErr = std::cerr.rdbuf();
}
void endRedirect()
{
    if (oldOut) std::cout.rdbuf(oldOut);
    if (oldErr) std::cerr.rdbuf(oldErr);

    if (outFile.is_open()) outFile.close();
    if (errFile.is_open()) errFile.close();
}


void RedirectOutErr(Redirect &r)
{

    beginRedirect();

    if (!r.out.empty())
    {
        outFile.open(
            r.out,
            r.appendOut ? std::ios::app : std::ios::trunc);
        std::cout.rdbuf(outFile.rdbuf());
    }

    if (r.errOut)
    {
        std::cerr.rdbuf(std::cout.rdbuf());
    }
    else if (!r.err.empty())
    {
        errFile.open(
            r.err,
            r.appendErr ? std::ios::app : std::ios::trunc);
        std::cerr.rdbuf(errFile.rdbuf());
    }
}