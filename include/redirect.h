#pragma once
#include "globals.h"
struct Redirect
{
    std::string out;
    std::string err;
    bool errOut = false;
    bool appendOut = false;
    bool appendErr = false;
};
void beginRedirect();
void endRedirect();
Redirect pareseRedirects(std::vector<std::string> &args);
void RedirectOutErr(Redirect &r);