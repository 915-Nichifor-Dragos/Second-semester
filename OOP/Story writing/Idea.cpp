#include "Idea.h"

#include <vector>
#include <sstream>

istream& operator>>(istream& is, Idea& id)
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

    id.description = tokens[0];
    id.status = tokens[1];
    id.creator = tokens[2];
    id.act = stoi(tokens[3]);

    return is;

}
