#include "Writer.h"

#include <vector>
#include <sstream>

istream& operator>>(istream& is, Writer& wr)
{
    string line;
    getline(is, line);

    vector <string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, ','))
    {
        tokens.push_back(token);
    }

    if (tokens.size() == 0)
        return is;

    wr.name = tokens[0];
    wr.expertise = tokens[1];

    return is;

}
