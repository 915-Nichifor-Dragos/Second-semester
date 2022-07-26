#include "User.h"

#include <sstream>
#include <vector>

istream& operator>>(istream& is, User& us)
{
    string line;
    getline(is, line);

    stringstream ss(line);
    string token;
    vector<string> tokens;

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 1)
        return is;

    us.name = tokens[0];

    return is;
}
