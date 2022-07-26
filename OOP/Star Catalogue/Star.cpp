#include "Star.h"

#include <vector>
#include <sstream>

istream& operator>>(istream& is, Star& st)
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

    if (tokens.size() != 5)
        return is;

    st.name = tokens[0];
    st.constelation = tokens[1];
    st.RA = stoi(tokens[2]);
    st.Dec = stoi(tokens[3]);
    st.diameter = stoi(tokens[4]);

    return is;

}

ostream& operator<<(ostream& os, Star& st)
{
    os << st.name << "," << st.constelation << "," << st.RA << "," << st.Dec << "," << st.diameter;
    return os;
}
