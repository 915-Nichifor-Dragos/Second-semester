#include "Topic.h"

#include <sstream>

istream& operator>>(istream& is, Topic& us)
{
    string line;
    getline(is, line);

    stringstream ss(line);
    string token;
    vector<string> tokens;

    us.users.clear();

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() < 1)
        return is;

    us.topic = tokens[0];
    
    int i = 1;
    while (i < tokens.size())
    {
        us.users.push_back(tokens[i]);
        i++;
    }

    return is;
}

ostream& operator<<(ostream& os, Topic& us)
{
    os << us.topic;
    for (auto element : us.users)
        os << "," << element;
    return os;
}
