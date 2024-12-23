#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> rules;
vector<vector<string>> prints;

vector<string> split(string line){
    string buf = "";
    vector<string> out;
    for (char c: line)
    {
        if (c == ',')
        {
            out.push_back(buf);
            buf = "";
        }
        else{
            buf += c;
        }
    }
    out.push_back(buf);
    return out;
}

bool invec(vector<string> v, string s){
    for (string i : v)
    {
        if (i == s)
        {
            return true;
        }  
    }
    return false;
}

bool check(vector<string> printout){
    for (size_t i = 0; i < printout.size() - 1; i++)
        {
            for (size_t j = i+1; j < printout.size(); j++)
            {
                string potential_rule = printout[i];
                potential_rule += "|";
                potential_rule += printout[j];

                cout << "Potential rule: " << potential_rule << endl;

                if(!invec(printout, potential_rule)){
                    return false;
                }
           }   
        }
    return true;
}

int res = 0;

int main()
{
    string buff;
    ifstream f("_input.txt");
 
    while (getline(f, buff)){
        if (buff.size() < 2)
        {
            buff.clear();
            continue;
        }
        
        if (buff.at(2) == '|')
        {
            rules.push_back(buff); // So \n doesnt 
        }
        else if (buff.at(2) == ',')
        {
            prints.push_back(split(buff));
        }

        buff.clear();
    }
    
    f.close();


    for (auto p: prints)
    {
        if (check(p))
        {
            cout << stoi(p.at((p.size()-1) / 2)) << endl;
            res += stoi(p.at((p.size()-1) / 2));
        }
        
    }
    
    cout << "Res: " << res << "\n";

    return 0;
}
