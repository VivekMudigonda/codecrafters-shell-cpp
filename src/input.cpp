#include "globals.h"
std::vector<std::string> splitWhitespace(const std::string &s)
{
    std::stringstream ss(s);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}
bool isSpecial(char input)
{
    return input == '\'' || input == ' ';
}
bool readQuoted(const std::string &input_string, int &j, std::string &token)
{
    j++;
    while (j < input_string.size() && input_string[j] != '\'')
    {
        token += input_string[j];
        j++;
    }
    if (j == input_string.size())
    {
        std::cerr << "Error: unmatched single quote\n";
        return false;
    }
    j++;
    return true;
}
bool readUnqouted(const std::string &input_string, int &j, std::string &token)
{
    while (j < input_string.size() && !isSpecial(input_string[j]))
    {
        token += input_string[j];
    }
    return true;
}
void Input(std::string &S)
{
    int j = 0;
    while (j < S.size())
    {
        if (S[j] == ' ')
        {
            j++;
            continue;
        }
        std::string token;
        if (S[j] == '\'')
        {
            readQuoted(S, j, token);
        }
        else if (S[j] == ' ')
        {
            readUnqouted(S, j, token);
        }
        if (!token.empty())
        {
            args.push_back(token);
        }
    }
}