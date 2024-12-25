#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <array>

using namespace std;

vector<vector<string>> keys_strs;
vector<vector<string>> locks_strs;

vector<array<int, 5>> keys;
vector<array<int, 5>> locks;

array<int, 5> convertToHeights(vector<string> v)
{
    array<int, 5> out;

    for (size_t x = 0; x < v.at(0).size(); x++)
    {
        if (v.at(0) == "#####")
        {
            int y = 0;
            while (v.at(y).at(x) == '#')
            {
                y++;
            }
            out.at(x) = y - 1;
        }
        else
        {
            int y = v.size() - 1;
            while (v.at(y).at(x) == '#')
            {
                y--;
            }
            out.at(x) = v.size() - y - 2;
        }
    }
    return out;
}

bool fits(array<int,5> lock, array<int,5> keys){
    for (size_t i = 0; i < lock.size(); i++)
    {
        if (lock.at(i) + keys.at(i) >= 6)
        {
            return false;
        }
        
    }
    return true;
}

int main()
{
    string buff;
    vector<string> tmp;

    int idx = 0;

    ifstream f("input.txt");

    while (getline(f, buff))
    {
        tmp.push_back(buff);

        if (tmp.size() % 8 == 0)
        {
            if (tmp.at(0) == "#####")
            {
                tmp.erase(tmp.end() - 1);
                locks_strs.push_back(tmp);
                tmp.clear();
            }
            else
            {
                tmp.erase(tmp.end() - 1);
                keys_strs.push_back(tmp);
                tmp.clear();
            }
        }
    }
    if (tmp.at(0) == "#####")
    {
        locks_strs.push_back(tmp);
        tmp.clear();
    }
    else
    {
        keys_strs.push_back(tmp);
        tmp.clear();
    }

    for (auto &&i : locks_strs)
    {
        locks.push_back(convertToHeights(i));
    }
    
    for (auto &&i : keys_strs)
    {
        keys.push_back(convertToHeights(i));
    }

    int res = 0;

    for(auto lock: locks){
        for (auto key : keys)
        {
            if(fits(lock, key)){
                res ++;
            }
        }
    }

    cout << "Res: " << res << "\n";

    return 0;
}