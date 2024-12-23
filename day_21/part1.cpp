#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

std::string mainKeypad(string code)
{
    vector<string> pad = {"789", "456", "123", " 0A"};
    string out = "";
    int appendEnd = 0;
    pair<int, int> pos = pair(2, 3);

    for (char c : code)
    {
        for (int y = 0; y < pad.size(); y++)
        {
            if (pad.at(y).find(c) != string::npos)
            {
                if (y >= pos.second)
                {
                    if (pad.at(y - pos.second).at(pos.first) != ' ')
                    {
                        for (size_t i = 0; i < y - pos.second; i++)
                        {
                            out += "v";
                        }
                    }
                    else
                    {
                        appendEnd = y - pos.second;
                    }
                }
                else
                {
                    for (size_t i = 0; i < pos.second - y; i++)
                    {
                        out += "^";
                    }
                }

                pos.second = y;

                int x = pad.at(y).find(c);
                if (x >= pos.first)
                {
                    for (size_t i = 0; i < x - pos.first; i++)
                    {
                        out += ">";
                    }
                }
                else
                {

                    for (size_t i = 0; i < pos.first - x; i++)
                    {
                        out += "<";
                    }
                }
                pos.first = x;
            }
        }
        if (appendEnd > 0)
        {
            for (size_t i = 0; i < appendEnd; i++)
            {
                out += "v";
            }
        }
        out += "A";
    }
    cout << out << endl;
    return out;
}

std::string dpad(string code)
{
    vector<string> pad = {" ^A", "<v>"};
    string out = "";
    int appendEnd = 0;
    pair<int, int> pos = pair(2, 0);

    for (char c : code)
    {
        for (int y = 0; y < pad.size(); y++)
        {
            if (pad.at(y).find(c) != string::npos)
            {
                if (y >= pos.second)
                {
                    for (size_t i = 0; i < y - pos.second; i++)
                    {
                        out += "v";
                    }
                }
                else
                {
                    if (pad.at(pos.second - y).at(pos.first) != ' ')
                    {
                        for (size_t i = 0; i < pos.second - y; i++)
                        {
                            out += "^";
                        }
                    }
                    else
                    {
                        appendEnd = pos.second - y;
                    }
                }

                pos.second = y;

                int x = pad.at(y).find(c);
                if (x >= pos.first)
                {
                    for (size_t i = 0; i < x - pos.first; i++)
                    {
                        out += ">";
                    }
                }
                else
                {

                    for (size_t i = 0; i < pos.first - x; i++)
                    {
                        out += "<";
                    }
                }
                pos.first = x;
            }
        }
        if (appendEnd > 0)
        {
            for (size_t i = 0; i < appendEnd; i++)
            {
                out += "^";
            }
            
        }
        out += "A";
    }
    cout << out << endl;
    return out;
}
int main()
{
    
    string buff;
    ifstream f("_input.txt");
    int res = 0;

    while (getline(f, buff))
    {
        res += (dpad(dpad(mainKeypad(buff)))).size() * stoi(buff.substr(0, 3));
        // cout << (dpad(dpad(mainKeypad(buff)))).size() << " * " << stoi(buff.substr(0,3)) << " = " << (dpad(dpad(mainKeypad(buff)))).size() * stoi(buff.substr(0,3)) << endl;

        // cout << (dpad(dpad(mainKeypad(buff)))) << endl;
    }

    cout << "Res: " << res << "\n";

    //    string test = (dpad(dpad(mainKeypad("980A"))));


    //cout << mainKeypad("029A") << endl;

    return 0;
}