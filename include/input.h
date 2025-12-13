#pragma once
std::vector<std::string> splitWhitespace(const std::string &s);
bool isSpecial(char input);
bool readUnqouted(const std::string &input_string, int &j, std::string &token);
bool readQuoted(const std::string &input_string, int &j, std::string &token);
void Input(std::string &S);