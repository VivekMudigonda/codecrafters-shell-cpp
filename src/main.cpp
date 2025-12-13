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
std::vector<std::string> args;

int runCommand(const std::string &program)
{
  std::string cmd = program;

  for (const auto &arg : args)
  {
    cmd += " \"" + arg + "\"";
  }
  int result = std::system(cmd.c_str());

  if (result == -1)
  {
    std::cerr << "Failed to run command\n";
  }
  return result;
}

void Exec(std::string &input)
{
  std::string extPath = isExternal(args[0]);
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
      runCommand(extPath);
      break;
    }
    std::cout << input << ": not found" << std::endl;
  }
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
    Input(args, input, ' ');

    if (args[0] == "exit" && args[1] == "0")
    {
      break;
    }
    else if (args[0] == "\n")
    {
      continue;
    }

    Exec(input);
  }
}
