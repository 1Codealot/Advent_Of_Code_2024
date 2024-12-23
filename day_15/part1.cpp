#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> warehouse;
string path;

int main()
{
    string buff;
    bool foundSep = false;

    ifstream f("input.txt");
    while (getline(f, buff))
    {
        if (buff.size() == 0)
        {
            foundSep = true;
        }
        if (!foundSep)
        {
            warehouse.push_back(buff);
        }
        else
        {
            path += buff;
        }
    }

    // Find '@'

    pair<int, int> pos;

    for (int y = 0; y < warehouse.size(); y++)
    {
        for (int x = 0; x < warehouse.at(0).size(); x++)
        {
            if (warehouse.at(y).at(x) == '@')
            {
                pos = pair(x, y);
            }
        }
    }

    for (char c : path)
    {
        switch (c)
        {
        case '^':
            if (warehouse.at(pos.second - 1).at(pos.first) == '#')
            {
                continue;
            }
            else if (warehouse.at(pos.second - 1).at(pos.first) == 'O')
            {
                // Find end of O stack
                int length = 1;
                while (warehouse.at(pos.second - length).at(pos.first) == 'O')
                {
                    length++;
                }
                length--;
                if (warehouse.at(pos.second - (length + 1)).at(pos.first) == '#')
                {
                    continue;
                }
                else
                {
                    warehouse.at(pos.second - (length + 1)).at(pos.first) = 'O';
                }
            }
            pos.second--;
            warehouse.at(pos.second + 1).at(pos.first) = '.';
            warehouse.at(pos.second).at(pos.first) = '@';

            break;
        case '>':
        {
            if (warehouse.at(pos.second).at(pos.first + 1) == '#')
            {
                continue;
            }
            else if (warehouse.at(pos.second).at(pos.first + 1) == 'O')
            {
                // Find end of O stack
                int length = 1;
                while (warehouse.at(pos.second).at(pos.first + length) == 'O')
                {
                    length++;
                }
                length--;
                if (warehouse.at(pos.second).at(pos.first + (length + 1)) == '#')
                {
                    continue;
                }
                else
                {
                    warehouse.at(pos.second).at(pos.first + (length + 1)) = 'O';
                }
            }
            pos.first++;
            warehouse.at(pos.second).at(pos.first - 1) = '.';
            warehouse.at(pos.second).at(pos.first) = '@';
            break;
        }
        case 'v':
            if (warehouse.at(pos.second + 1).at(pos.first) == '#')
            {
                continue;
            }
            else if (warehouse.at(pos.second + 1).at(pos.first) == 'O')
            {
                // Find end of O stack
                int length = 1;
                while (warehouse.at(pos.second + length).at(pos.first) == 'O')
                {
                    length++;
                }
                length--;
                if (warehouse.at(pos.second + (length + 1)).at(pos.first) == '#')
                {
                    continue;
                }
                else
                {
                    warehouse.at(pos.second + (length + 1)).at(pos.first) = 'O';
                }
            }
            pos.second++;
            warehouse.at(pos.second - 1).at(pos.first) = '.';
            warehouse.at(pos.second).at(pos.first) = '@';
            break;

        case '<':
            if (warehouse.at(pos.second).at(pos.first - 1) == '#')
            {
                continue;
            }
            else if (warehouse.at(pos.second).at(pos.first - 1) == 'O')
            {
                // Find end of O stack
                int length = 1;
                while (warehouse.at(pos.second).at(pos.first - length) == 'O')
                {
                    length++;
                }
                length--;
                if (warehouse.at(pos.second).at(pos.first - (length + 1)) == '#')
                {
                    continue;
                }
                else
                {
                    warehouse.at(pos.second).at(pos.first - (length + 1)) = 'O';
                }
            }
            pos.first--;
            warehouse.at(pos.second).at(pos.first + 1) = '.';
            warehouse.at(pos.second).at(pos.first) = '@';

            break;
        default:
            break;
        }
    }

    unsigned long long res = 0;

    for (size_t y = 1; y < warehouse.size() - 1; y++)
    {
        for (size_t x = 1; x < warehouse.at(0).size() - 1; x++)
        {
            if(warehouse.at(y).at(x) == 'O'){
                res += 100 * y + x;
            }
        }
        
    }

    for(string line: warehouse){
        cout << line << "\n";
    }
    

    cout << "Res: " << res << "\n";

    return 0;
}