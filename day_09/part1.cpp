#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

bool isMinus1(int i){
    return i == -1;
}

int main(){
    string puzzle;

    ifstream f("input.txt");

    getline(f, puzzle);

    f.close();

    vector<int> disk;

    for (size_t i = 0; i < puzzle.size(); i++)
    {
        if (i%2 == 0)
        {
            for (size_t n = 0; n < (puzzle.at(i)) - '0'; n++)
            {
                disk.push_back(i/2);
            }
            
        }
        else
        {
            for (size_t n = 0; n < (puzzle.at(i)) - '0'; n++)
            {
                disk.push_back(-1);
            }
        }
    }

    // Defragment

    for (auto i = disk.rbegin(); i != disk.rend(); i++)
    {
        if(*i == -1){
            continue;
        }
        

        int tmp = *i;
        *i = *find_if(disk.begin(), disk.end(), isMinus1);
        *find_if(disk.begin(), disk.end(), isMinus1) = tmp;
    }
    
    for (auto &&i : disk)
    {
        if(isMinus1(i)){
            cout << ".";
        }
        else{
            cout << i;
        }
    }


    size_t res = 0;

    for (size_t i = 0; i < disk.size(); i++)
    {
        if (disk.at(i) == -1)
        {
            break;
        }
        res += i * disk.at(i);       
    }
    cout <<"\n";
    
    cout << "Res: " << res << "\n";

    return 0;
    
}