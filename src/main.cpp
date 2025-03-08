#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
    }

    std::cout << input << ": command not found" << std::endl;
  }
}
