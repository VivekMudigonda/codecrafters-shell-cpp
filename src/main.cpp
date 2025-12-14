#include "globals.h"
#include "directoryExists.h"
#include "echo.h"
#include "home.h"
#include "input.h"
#include "isExternal.h"
#include "pwd.h"
#include "stringCode.h"
#include "type.h"
#include "cd.h"
#include "runCommand.h"
#include "redirect.h"
std::vector<std::string> args;

void Exec(std::string &input,Redirect &r)
{
  std::string extPath = isExternal(args[0]);
  if(hashString(args[0])!=StringCode::unknown){
    RedirectOutErr(r);
  }
  switch (hashString(args[0]))
  {
  case StringCode::echo:
    Echo();
    break;
  case StringCode::type:
    Type();
    break;
  case StringCode::pwd:
    Pwd();
    break;
  case StringCode::cd:
    Cd(args[1]);
    break;
  default:
    if (extPath != "")
    {
      std::string program = args.front();
      args.erase(args.begin());
      runCommand(program,r);
      break;
    }
    std::cout << input << ": not found" << std::endl;
  }
  endRedirect();
}

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (true)
  {
    std::cout << "$ ";

    std::getline(std::cin, input);

    args.clear();
    Input(input);
    if (args[0] == "exit")
    {
      break;
    }
    else if (args[0] == "\n")
    {
      continue;
    }
    Redirect r = pareseRedirects(args);
    Exec(input,r);
  }
}
