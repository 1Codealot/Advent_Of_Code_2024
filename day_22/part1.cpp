#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

size_t updateValue(size_t& n){
    n = (n*64)^n;
    n %= 16777216;
    n = (n/32)^n;
    n %= 16777216;
    n = (n*2048)^n;
    n %= 16777216;

    return n;
}

int main(){
    string buff;
    vector<size_t> secretNums;

    ifstream f("input.txt");
    while (getline(f, buff))
    {
        secretNums.push_back(stoul(buff));
    }
    
    for (size_t i = 0; i < 2000; i++)
    {
        for (auto &&n : secretNums)
        {
            updateValue(n);
        }
    }

    unsigned long long res = 0;

    for (auto &&i : secretNums)
    {
        res += i;
    }
    
    cout << "Res: " << res << "\n";

    return 0;
}
