
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
   
    // Horizontal
    
    for(string line: lines){
        for(int i = 0; i < horiz; i++){
            if(line.substr(i,4) == "XMAS" || line.substr(i,4) == "SAMX"){
                xmas_cnt++;
            }
        }
    }
   
    // Vertical
    for(int y = 0; y < verti - 3; y++){
        for(int x = 0; x < horiz; x++){
            string to_check = string({lines.at(y).at(x),
                                        lines.at(y+1).at(x),
                                        lines.at(y+2).at(x),
                                        lines.at(y+3).at(x)});


            if(to_check == "XMAS" || to_check == "SAMX"){
                xmas_cnt++;
            }
        }
    }
    
    // Diagonal (>V)

    for (int y = 0; y < verti - 3; y++)
    {
        for (int x = 0; x < horiz - 3; x++)
        {
            string to_check = string({lines.at(y).at(x),
                                        lines.at(y+1).at(x+1),
                                        lines.at(y+2).at(x+2),
                                        lines.at(y+3).at(x+3)});

            if(to_check == "XMAS" || to_check == "SAMX"){
                xmas_cnt++;
            }
        }
        
    }
    
    // Diagonal (>^)

    for (int y = 3; y < verti; y++)
    {
        for (int x = 0; x < horiz - 3; x++)
        {
            string to_check = string({lines.at(y).at(x),
                                        lines.at(y-1).at(x+1),
                                        lines.at(y-2).at(x+2),
                                        lines.at(y-3).at(x+3)});

            if(to_check == "XMAS" || to_check == "SAMX"){
                xmas_cnt++;
            }
        }
        
    }
    

    cout << "Result:" << xmas_cnt << endl;
   
    f.close();
    return 0;
}
