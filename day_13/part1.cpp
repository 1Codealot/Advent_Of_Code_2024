#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

pair<int, int> sim_eq(int AX, int BX, int PX, int AY, int BY, int PY){
    pair<int, int> res = {0, 0};

    int tmp_yC = BX;

    AX *= BY;
    BX *= BY;
    PX *= BY;

    AY *= tmp_yC;
    BY *= tmp_yC;
    PY *= tmp_yC;

    int xC_diff = AX - AY;
    int r_diff  = PX - PY;

    double tmp = (double)(((double)r_diff) / ((double)xC_diff));
    if(fmod(tmp, 1) != 0){
        return pair(-1, -1);
    }


    res.first = r_diff / xC_diff;

    PX -= res.first * AX;

    tmp = (double)(((double)PX) / ((double)BX));

    if (fmod(tmp, 1) != 0)
    {
        // i.e. not whole
        return pair(-1,-1);
    }
    
    res.second = tmp;

    return res;
}

vector<pair<int, int>> get_info(string info){
    // (AX,AY) (BX,BY) (PX,PY)


    vector<string> lines;

    string buff;
    for(char c: info){
        if (c == '\n')
        {
            lines.push_back(buff);
            buff.clear();
        }
        else
        {
            buff += c;
        }
    }

    pair<int,int> A;
    string cLine = lines.at(0);

    A.first = stoi(cLine.substr(cLine.find('X')+2, 2));
    A.second = stoi(cLine.substr(cLine.find('Y')+2, 2));


    pair<int,int> B;
    cLine = lines.at(1);

    B.first = stoi(cLine.substr(cLine.find('X')+2, 2));
    B.second = stoi(cLine.substr(cLine.find('Y')+2, 2));


    pair<int,int> P;
    cLine = lines.at(2);

    P.first = stoi(cLine.substr(cLine.find('X')+2, cLine.find(',') - cLine.find('X')));
    P.second = stoi(cLine.substr(cLine.find('Y')+2));

    return vector{A,B,P};

}

vector<vector<pair<int, int>>> puzzle_info;
const pair<int, int> impossible = pair(-1,-1);

int main(){
    string buff;
    string tmp;
    vector <string> lines;

    unsigned long long tokens = 0;

    ifstream f("input.txt");

    while (getline(f, tmp))
    {
        lines.push_back(tmp);
    }

    for (size_t i = 0; i < lines.size(); i++)
    {
        buff += lines.at(i) + "\n";
        if (i%4==3)
        {
            puzzle_info.push_back(get_info(buff));
            buff.clear();
        }   
    }
    
    auto current_info = puzzle_info.at(0);

    for (auto info: puzzle_info)
    {
        pair<int,int> presses = sim_eq(info.at(0).first, info.at(1).first, info.at(2).first,
                                       info.at(0).second, info.at(1).second, info.at(2).second);



        if (presses != impossible)
        {
            //cout << presses.first << "\t" << presses.second << "\n";
            tokens += (3*presses.first) + presses.second;
        }
    }
        
    cout << "Tokens needed: " << tokens << "\n";

    return 0;
}