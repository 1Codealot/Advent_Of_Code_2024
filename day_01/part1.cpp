#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void split(vector<int>& lhs, vector<int>& rhs, string line){
    lhs.push_back(stoi(line.substr(0,5)));
    rhs.push_back(stoi(line.substr(8,5)));

}

int main(){

    // Read in the input.
    string buff;
    ifstream f("input.txt");
 
    std::vector<int> lhs;
    std::vector<int> rhs;

    while (getline(f, buff)){
        split(lhs, rhs, buff);
        buff.clear();
    }
    
    f.close();

    sort(lhs.begin(), lhs.end());
    sort(rhs.begin(), rhs.end());

    vector<int> diffs;

    for (size_t i = 0; i < rhs.size(); i++)
    {
        diffs.push_back(abs(lhs.at(i) - rhs.at(i)));
    }
    
    int64_t sum = 0;

    for (auto &&i : diffs)
    {
        sum += i;
    }

    cout << "Result: " << sum << "\n";    

    return 0;
}