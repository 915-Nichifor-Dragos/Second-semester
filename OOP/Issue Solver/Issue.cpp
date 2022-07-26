#include "Issue.h"

#include <sstream>
#include <vector>

istream& operator>>(istream& is, Issue& u)
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

    if (tokens.size() != 3 and tokens.size() != 4)
        return is;

    u.description = tokens[0];
    u.status = tokens[1];
    u.reporter = tokens[2];
    if (tokens.size() == 4)
        u.solver = tokens[3];

    return is;
}

ostream& operator<<(ostream& os, Issue& issue)
{
    os << issue.getDescription() + "," + issue.getStatus() + "," + issue.getReporter() + "," + issue.getSolver();
    return os;
}
