#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

string input_ops(string equation, string ops){
    // + = 0, * = 1 | = 2
    int op_num = 0;

    for (int i = 0; i < equation.size(); i++)
    {
        if (equation.at(i) == ' ')
        {
            switch (op_num)
            {
            case 0:
                equation.at(i) = '+';
                break;

            case 1:
                equation.at(i) = '*';
                break;

            case 2:
                equation.erase(i,1);
                i++;
                break;

            
            default:
                cout << "jcrhkcghvxkl\n";
                break;
            }
            
            
            op_num++;
        }
        
    }
    return equation;    
}

long eval(string equation){
    long res = 0;
    char op = '+';
    string buff;

    for(char c: equation){
        if (isdigit(c))
        {
            buff += c;
        }
        else
        {
            if (op == '+')
            {
                res += stol(buff);
            }
            else
            {
                res *= stol(buff);
            }
            buff.clear();
            op = c;
        }
    }
    if (op == '+')
        {
            res += stol(buff);
        }
        else
        {
            res *= stol(buff);
        }
    return res;
}

int main(){
    string buff;
    vector<string> lines;

    ifstream f("input.txt");

    int64_t res = 0; // Too small tyoe before lmao

    while (getline(f, buff)){
        lines.push_back(buff);
        buff.clear();
    }

    for (string line : lines)
    {
        long expected = stol(line.substr(0, line.find(':')));
        string nums = line.substr(line.find(':') + 2);

        int_fast16_t spaces = count(line.begin(), line.end(), ' ');

        for (int_fast16_t i = 0; i < pow(2, spaces) + 1; i++)
        {
            if (eval(input_ops(nums, i)) == expected)
            {
                res += expected;
                break;
            }            
        }
        
        
    }

    cout << res << endl;

    return 0;
}