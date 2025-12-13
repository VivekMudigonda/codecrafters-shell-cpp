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
void flush_token(std::string &token)
{
    if (!token.empty())
    {
        args.push_back(token);
    }
    token.clear();
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
        j++;
    }
    return true;
}
void Input(std::string &S)
{
    int j = 0;
    std::string token;
    while (j < S.size())
    {
        if (S[j] == ' ')
        {
            flush_token(token);
            j++;
            continue;
        }
        if (S[j] == '\'')
        {
            if (!readQuoted(S, j, token))
            {
                return;
            }
        }
        else
        {
            readUnqouted(S, j, token);
        }
    }
    flush_token(token);
}