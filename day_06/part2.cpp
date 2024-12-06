#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <set>

using namespace std;

vector<string> puzzle;

struct bounce
{
    int x;
    int y;
    int dir;
};

bool operator==(const bounce& lhs, const bounce& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.dir == rhs.dir);
}


bool loops(vector<string>& puzzle, vector<bounce> bounces, int x, int y, int dir){
    //bounce: {x,y,dir}
    puzzle.at(y).at(x) = 'X';
    if(dir == 0){
        //Up
        if(y == 0){
            return false;
        }
        
        // bounce
        if(puzzle.at(y-1).at(x) == '#'){
            bounce b = {
                .x=x,
                .y=y,
                .dir=dir
            };
            
            if (find(bounces.begin(), bounces.end(), b) != bounces.end())
            {
                return true;
            } 
            else
            {
                bounces.push_back(b);
            }
            
            
            dir++;
            y++;
        }
        
        return loops(puzzle, bounces, x, y-1, dir);

    } else if(dir == 1){
        //Right
        if(x == puzzle.at(0).size()-1){
            return false;
        }
        
        if(puzzle.at(y).at(x+1) == '#'){
            bounce b = {
                .x=x,
                .y=y,
                .dir=dir
            };
            
            if (find(bounces.begin(), bounces.end(), b) != bounces.end())
            {
                return true;
            }
            else
            {
                bounces.push_back(b);
            }
            dir++;
            x--;
        }
        
        return loops(puzzle, bounces, x+1, y, dir);
    }
    else if(dir == 2){
        //Down
        if(y == puzzle.size()-1){
            return false;
        }
        
        if (puzzle.at(y+1).at(x) == '#'){
            bounce b = {
                .x=x,
                .y=y,
                .dir=dir
            };
            
            if (find(bounces.begin(), bounces.end(), b) != bounces.end())
            {
                return true;
            } else
            {
                bounces.push_back(b);
            }

            dir++;
            y--;
        }
        
        return loops(puzzle, bounces, x, y+1, dir);
        
    }
    else if(dir == 3){
        //Left
        if(x == 0){
            return false;
        }
        
        if(puzzle.at(y).at(x-1) == '#'){
            bounce b = {
                .x=x,
                .y=y,
                .dir=dir
            };
            
            if (find(bounces.begin(), bounces.end(), b) != bounces.end())
            {
                return true;
            } else
            {
                bounces.push_back(b);
            }

            dir = 0;
            x++;
        }
        
        return loops(puzzle, bounces, x-1, y, dir);
    }
    
}

int start_x;
int start_y;
int cnt = 0;

int main(){
    string buff;
   
    vector<string> lines;
    
    
    ifstream f("input.txt");
    
    int line = 0;
    
    while (getline(f, buff)){
        puzzle.push_back(buff);
        
        size_t found = buff.find('^', 0);
        
        if(found != string::npos){ // Not in
            start_y = line;
            start_x = found;
        }
        
        buff.clear();
        line++;
    }
    
    // simulate

    for (int y = 0; y < puzzle.size(); y++)
    {
        for (int x = 0; x < puzzle.at(0).size(); x++)
        {
            if (puzzle.at(y).at(x) == '#')
            {
                continue;
            }
            else
            {
                vector<string> tmp = puzzle;
                tmp.at(y).at(x) = '#';

                cnt += loops(tmp, {}, start_x, start_y, 0);
                tmp.clear();
            }

        }
        
    }

    cout << cnt << endl;
    

    return 0;
}
