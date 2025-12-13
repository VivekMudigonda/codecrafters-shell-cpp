#include "globals.h"
bool backSlash = false;
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
    return !backSlash&&(input == '\'' || input == ' ' || input == '\"');
}
void flush_token(std::string &token)
{
    if (!token.empty())
    {
        args.push_back(token);
    }
    token.clear();
}
bool readDoubleQuoted(const std::string &input_string,int &j,std::string &token){
    j++;
    while(j<input_string.size()&&(input_string[j]!='\"')){
        token += input_string[j];
        j++;
    }
    if(j==input_string.size()){
        std::cerr<<"Error: unmatched double quote\n";
        return false;
    }
    j++;
    return true;
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
bool readUnQouted(const std::string &input_string, int &j, std::string &token)
{
    
    while (j < input_string.size() && !isSpecial(input_string[j]))
    {
        if(input_string[j]=='\\'&&!backSlash){
            backSlash = true;
            j++;
            continue;
        }
        token += input_string[j];
        backSlash = false;
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
            backSlash = false;
            flush_token(token);
            j++;
            continue;
        }
        if(S[j]=='\"'&&!backSlash){
            backSlash = false;
            if(!readDoubleQuoted(S,j,token)){
                return;
            }
        }
        else if (S[j] == '\''&&!backSlash)
        {
            backSlash = false;
            if (!readQuoted(S, j, token))
            {
                return;
            }
        }
        else if(S[j]=='\\'&&!backSlash){
            backSlash = true;
        }
        else
        {
            backSlash = false;
            readUnQouted(S, j, token);
        }
    }
    flush_token(token);
}