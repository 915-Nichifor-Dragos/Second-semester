#include "Post.h"

#include <vector>
#include <sstream>

istream& operator>>(istream& is, Post& us)
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

    if (tokens.size() != 5)
        return is;

    us.id = tokens[0];
    us.text = tokens[1];
    us.date = tokens[2];
    us.time = tokens[3];
    us.user = tokens[4];
    
    return is;

}

ostream& operator<<(ostream& os, Post& us)
{
    os << us.id << "," << us.text << "," << us.date << "," << us.time << "," << us.user;
    return os;
}
