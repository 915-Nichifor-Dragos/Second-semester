#include "User.h"

#include <sstream>
#include <vector>

istream& operator>>(istream& is, User& u)
{
    string line;
    getline(is, line);
    stringstream ss(line);

    vector <string> tokens;
    string token;

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 2)
        return is;

    u.name = tokens[0];
    u.type = tokens[1];

    return is;
}
