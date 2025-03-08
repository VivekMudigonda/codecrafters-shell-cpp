#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

std::vector<std::string> args;

std::unordered_map<std::string,bool> mp = {{"echo",true},{"exit",true},{"type",true}};

enum class StringCode {
  echo,
  type,
  unknown
};

StringCode hashString(const std::string& str) {
  if (str == "echo") return StringCode::echo;
  if (str == "type")  return StringCode::type;
  return StringCode::unknown;
}

void Echo(){
  for(int i = 1 ; i < args.size() ; i++){
    std::cout << args[i] << " ";
  }
  std::cout << std::endl;
}

void Type(){
  if(mp[args[1]]){
    std::cout << args[1] << " is a shell builtin" << std::endl;
  }
  else{
    std::cout << args[1] << " not found" << std::endl;
  }
}

void Exec(std::string& input){
  switch (hashString(args[0])) {
    case StringCode::echo:
      Echo();
      break;
    case StringCode::type:
      Type();
      break;
    default:
      std::cout << input << ": not found" << std::endl;
    
  }
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (true) {
    std::cout << "$ ";

    std::getline(std::cin, input);

    std::stringstream s(input);

    std::string inputPart;
    char c = ' ';   

    while(getline(s,inputPart,c)){
      args.push_back(inputPart);
    }
  
    if(args[0]=="exit" && args[1]=="0"){
      break;
    }
    else if(args[0]=="\n"){
      continue;
    }

    Exec(input);
    
  }
}
