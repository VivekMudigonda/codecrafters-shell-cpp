#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  while (true) {
    std::cout << "$ ";

    std::getline(std::cin, input);

    std::unordered_map<std::string,bool> mp = {{"echo",true},{"exit",true},{"type",true}};

    std::stringstream s(input);

    std::string inputPart;
    char c = ' ';   
    std::vector<std::string> inputSeg;

    while(getline(s,inputPart,c)){
      inputSeg.push_back(inputPart);
    }

    if(inputSeg[0]=="exit" && inputSeg[1]=="0"){
      break;
    }

    if(inputSeg[0]=="echo"){
      for(int i = 1 ; i < inputSeg.size() ; i++){
        std::cout << inputSeg[i] << " ";
      }
      std::cout << std::endl;
      continue;
    }

    if(inputSeg[0]=="type"){
      if(mp[inputSeg[1]]){
        std::cout << inputSeg[1] << " is a shell builtin" << std::endl;
      }
      else{
        std::cout << inputSeg[1] << " not found" << std::endl;
      }
      continue;
    }
    std::cout << input << ": not found" << std::endl;
  }
}
