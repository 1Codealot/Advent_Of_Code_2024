#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

struct info
{
    string rhs;
    string lhs;
    string out;
    string op;
};


int64_t checkIfComplete(map<string, int> wires){
    int64_t res = 0;
    for (auto i = wires.rbegin(); i != wires.rend(); i++)
    {
        if((*i).first.at(0) == 'z'){
            if((*i).second == -1){
                return 0;
            }
            else
            {
                res <<= 1;
                res |= (*i).second;
            }            
        }
    }
    return res;
}

int main()
{
    string buff;
    int z_count = 0;
    map<string, int> wires; // string for the name; int is value: -1 = uninitialised, 0 = 0, 1 = 1.
    vector<info> ops;

    ifstream f("input.txt");
    bool foundBreak = false;
    while (getline(f, buff))
    {
        if (buff.size() == 0)
        {
            foundBreak = true;
            continue;
        }

        if (!foundBreak)
        {
            wires[buff.substr(0, 3)] = buff.at(5) - '0';
        }
        else
        {
            info i;
            i.lhs = buff.substr(0,3);
            i.out = buff.substr(buff.size() - 3, 3);

            if (wires.find(buff.substr(0, 3)) == wires.end())
            {
                wires[buff.substr(0, 3)] = -1;
            }

            if (wires.find(buff.substr(buff.size() - 3, 3)) == wires.end())
            {
                wires[buff.substr(buff.size() - 3, 3)] = -1;
            }

            if (buff.at(4) == 'O')
            {
                // OR op
                // 7
                i.rhs = buff.substr(7, 3);
                i.op = "OR";

                if (wires.find(buff.substr(7, 3)) == wires.end())
                {
                    wires[buff.substr(7, 3)] = -1;
                }
            }
            else
            {
                i.rhs = buff.substr(8, 3);
                i.op = buff.substr(4,3);
                if (wires.find(buff.substr(8, 3)) == wires.end())
                {
                    wires[buff.substr(8, 3)] = -1;
                    
                }
            }
            ops.push_back(i);
        }
    }

    for (auto &&i : wires)
    {
        cout << i.first << "\t" << i.second << "\n";
    }
    
    while(!checkIfComplete(wires))
    {
        for (auto &&i : ops)
        {
            if (wires[i.lhs] != -1 && wires[i.rhs] != -1)
            {
                if (i.op == "OR")
                {
                    wires[i.out] = wires[i.lhs] | wires[i.rhs];
                }
                else if (i.op == "AND")
                {
                    wires[i.out] = wires[i.lhs] & wires[i.rhs];
                }
                else if (i.op == "XOR")
                {
                    wires[i.out] = wires[i.lhs] ^ wires[i.rhs];
                }
                else
                {
                    cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA; " << i.op << " Unknown\n";
                }
            }
        }
    }

    for (auto &&i : wires)
    {
        cout << i.first << "\t" << i.second << "\n";
    }
    

    cout << "Res: " << checkIfComplete(wires) << "\n";

    return 0;
}