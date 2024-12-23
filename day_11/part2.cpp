#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string line){
    string buf;
    vector<string> res;
    
    for (char c: line)
    {
        if(c == ' '){
            res.push_back(buf);
            buf.clear();
        } else
        {
            buf += c;
        }   
    }
    res.push_back(buf);

    return res;
}

unsigned long long blink(vector<string> stones, int depth = 25){
    if (depth == 0)
    {
        return stones.size();
    }
    for (size_t i = 0; i < stones.size(); i++)
    {
        if (stones.at(i) == "0")
        {
            stones.at(i) = "1";
        }
        else if (stones.at(i).size() % 2 == 0)
        {
            // Split in 2
            string lhs, rhs;

            lhs = to_string(stoull(stones.at(i).substr(0, (int)(stones.at(i).size()/2))));
            rhs = to_string(stoull(stones.at(i).substr((int)stones.at(i).size()/2)));

            stones.at(i) = lhs;
            stones.insert(stones.begin() + (++i), rhs);
        }
        else
        {
            stones.at(i) = to_string(stoull(stones.at(i)) * 2024);
        }    
    }
    return blink(stones, depth-1);
}



int main(){
    unsigned long long stones_count = 0;

    string line;
    ifstream f("input.txt");
    
    getline(f, line);
    f.close();

    vector<string> stones = split(line);

    line.clear();

    for (string stone: stones)
    {
        stones_count += blink(stones, 75);
    }
    
    cout << "Res (75): " << stones_count/2 << "\n";

    return 0;
}