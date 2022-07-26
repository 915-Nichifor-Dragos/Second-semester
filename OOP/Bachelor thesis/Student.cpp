#include "Student.h"

#include <sstream>
#include <vector>

istream& operator>>(istream& is, Student& st)
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

    st.coordinator = "";
    st.title = "No title";

    if (tokens.size() < 4)
        return is;

    if (tokens.size() >= 4)
    {
        st.id = tokens[0];
        st.name = tokens[1];
        st.email = tokens[2];
        st.year = stoi(tokens[3]);

        if (tokens.size() >= 5)
            st.title = tokens[4];

        if (tokens.size() == 6)
            st.coordinator = tokens[5];
    }

    return is;
}

ostream& operator<<(ostream& os, Student st)
{
    os << st.id + "," + st.name + "," + st.email + "," + to_string(st.year);

    if (st.getTitle() != "No title")
        os << "," << st.getTitle();

    if (st.getCoordinator() != "")
        os << "," << st.getCoordinator();
    
    os << "\n";

    return os;
}
