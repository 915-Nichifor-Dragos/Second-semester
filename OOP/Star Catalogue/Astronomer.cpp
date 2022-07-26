#include "Astronomer.h"

#include <vector>
#include <sstream>

istream& operator>>(istream& is, Astronomer& ast)
{
    string line;
    getline(is, line);
    stringstream ss(line);

    vector<string> tokens;
    string token;

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 2)
        return is;

    ast.name = tokens[0];
    ast.constelation = tokens[1];

    return is;

}

