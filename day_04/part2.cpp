
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){
    string buff;
   
    vector<string> lines;
    int xmas_cnt = 0;
   
    ifstream f("input.txt");

    while (getline(f, buff)){
        lines.push_back(buff);
        buff.clear();
    }
   
    const int horiz = lines.at(0).size();
    const int verti = lines.size();
   
    // Start searching
   
    for (int y = 1; y < verti - 1; y++)
    {
        for (int x = 1; x < horiz - 1; x++)
        {
            if (lines.at(y).at(x) == 'A')
            {
                // Check (>V)
                if (((lines.at(y-1).at(x-1) == 'M' && lines.at(y+1).at(x+1) == 'S')
                    || (lines.at(y+1).at(x+1) == 'M' && lines.at(y-1).at(x-1) == 'S'))
                    /*Check (>^)*/ /*Also, its a beautiful if statement*/
                    && 
                    ((lines.at(y+1).at(x-1) == 'M' && lines.at(y-1).at(x+1) == 'S')
                    || (lines.at(y-1).at(x+1) == 'M' && lines.at(y+1).at(x-1) == 'S'))
                )
                {
                    xmas_cnt++;
                }
            }  
        }
    }
    
    cout << "Result:" << xmas_cnt << endl;
   
    f.close();
    return 0;
}
