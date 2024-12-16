#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(){
    string buff;
    vector<string> puzzle;
    vector<string> solved;

    ifstream f("input.txt");

    while (getline(f, buff))
    {
        puzzle.push_back(buff);
        solved.push_back(buff);
    }
 
    f.close();

    for (size_t y1 = 0; y1 < puzzle.size(); y1++)
    {
        for (size_t x1 = 0; x1 < puzzle.at(0).size(); x1++)
        {
            if(puzzle.at(y1).at(x1) == '.'){
                continue;
            }

            cout << "x1: " << x1 << "\ty1: " << y1 << endl;

            // Else
            for (size_t y2 = y1; y2 < puzzle.size(); y2++)
            {
                for (size_t x2 = 0; x2 < puzzle.at(0).size(); x2++)
                {
                    if (puzzle.at(y1).at(x1) == puzzle.at(y2).at(x2))
                    {
                        //cout << "x1: " << x1 << ", y1: " << y1 << ", x2: " << x2 << ", y2: " << y2 << "\n";

                        int x_diff = x2-x1;
                        int y_diff = y2-y1;

                        if (x_diff == 0 && y_diff == 0)
                        {
                            continue;
                        }
                        

                        if ((x2 + x_diff >= 0) && (x2 + x_diff < puzzle.at(0).size()) && (y2 + y_diff >= 0) && (y2 + y_diff < puzzle.size()))
                        {
                            solved.at(y2+y_diff).at(x2+x_diff) = '#';
                        }

                        if ((x1 - x_diff >= 0) && (x1 - x_diff < puzzle.at(0).size()) && (x1 - y_diff >= 0) && (y1 - y_diff < puzzle.size()))
                        {
                            solved.at(y1 - y_diff).at(x1-x_diff) = '#';
                        }
                    }
                }
            }
        }
    }

    int res = 0;
       
    for (string line: solved)
    {
        cout << line << "\n";
        for(char c: line){
            if(c == '#'){
                res++;
            }
        }
    }
    
    cout << "Res: " << res << "\n";

    return 0;
}