#include "Teacher.h"

#include <sstream>
#include <vector>

istream& operator>>(istream& is, Teacher& th)
{
    string line;
    is >> line;

    stringstream ss(line);
    string token;
    vector<string> tokens;

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 1)
        return is;

    th.name = tokens[0];

    return is;
}
