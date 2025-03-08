#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>

std::vector<std::string> args;

std::unordered_map<std::string, bool> isBuiltin = {{"echo", true}, {"exit", true}, {"type", true}};

enum class StringCode
{
  echo,
  type,
  unknown
};

StringCode hashString(const std::string &str)
{
  if (str == "echo")
    return StringCode::echo;
  if (str == "type")
    return StringCode::type;
  return StringCode::unknown;
}

void Input(std::vector<std::string> &args, std::string &S, char delimeter)
{
  std::stringstream s(S);

  std::string inputPart;

  while (getline(s, inputPart, delimeter))
  {
    args.push_back(inputPart);
  }
}

std::string isExternal(const std::string &command)
{
  std::string path = std::getenv("PATH");

  if (path == "")
  {
    return "";
  }
  std::vector<std::string> Path;

  Input(Path, path, ':');

  for (int i = 0; i < Path.size(); i++)
  {
    std::string fullPath = std::string(Path[i]) + "/" + command;
    if (access(fullPath.c_str(), X_OK) == 0)
    {
      return fullPath;
    }
  }

  return "";
}

void Echo()
{
  for (int i = 1; i < args.size(); i++)
  {
    std::cout << args[i] << " ";
  }
  std::cout << std::endl;
}

void Type()
{
  std::string extPath = isExternal(args[1]);
  if (isBuiltin[args[1]])
  {
    std::cout << args[1] << " is a shell builtin" << std::endl;
  }
  else if (extPath != "")
  {
    std::cout << args[1] << " is " << extPath << std::endl;
  }
  else
  {
    std::cout << args[1] << " not found" << std::endl;
  }
}

void runCommand(std::string &extPath)
{
  char arr[extPath.length() + 1];

  strcpy(arr, extPath.c_str());

  const char **c_array = new const char *[args.size()];
  for (size_t i = 0; i < args.size(); ++i)
  {
    c_array[i] = args[i].c_str();
  }
  pid_t pid = fork();
  if (pid == 0)
  {
    if (execvp(arr, c_array) == -1)
    {
      std::cerr << "Error executing command!" << std::endl;
    }
  }
  else if (pid > 0)
  {
    wait(NULL);
    std::cout << "Child process finished." << std::endl;
  }
  else
  {
    std::cerr << "Fork failed!" << std::endl;
  }
}

void Exec(std::string &input)
{
  switch (hashString(args[0]))
  {
  case StringCode::echo:
    Echo();
    break;
  case StringCode::type:
    Type();
    break;
  default:
    std::string extPath = isExternal(args[1]);
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
