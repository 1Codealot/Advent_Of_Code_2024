#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> puzzle;

void simulate(vector<string>& puzzle, int x, int y, int dir){
    puzzle.at(y).at(x) = 'X';
    if(dir == 0){
        //Up
        if(y == 0){
            return;
        }
        
        if(puzzle.at(y-1).at(x) == '#'){
            dir++;
            y++;
        }
        
        simulate(puzzle, x, y-1, dir);

    } else if(dir == 1){
        //Right
        if(x == puzzle.at(0).size()-1){
            return;
        }
        
        if(puzzle.at(y).at(x+1) == '#'){
            dir++;
            x--;
        }
        
        simulate(puzzle, x+1, y, dir);
    }
    else if(dir == 2){
        //Down
        if(y == puzzle.size()-1){
            return;
        }
        
        if (puzzle.at(y+1).at(x) == '#'){
            dir++;
            y--;
        }
        
        simulate(puzzle, x, y+1, dir);
        
    }
    else if(dir == 3){
        //Left
        if(x == 0){
            return;
        }
        
        if(puzzle.at(y).at(x-1) == '#'){
            dir = 0;
            x++;
        }
        
        simulate(puzzle, x-1, y, dir);
    }
    
}

int count(vector<string> p){
    int res = 0;
    for(string l: p){
        res += count(l.begin(), l.end(), 'X');
    }
    return res;
}

int start_x;
int start_y;
int last_dir = 0; // 0^, 1> 2v 3<

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
    simulate(puzzle, start_x, start_y, 0);
    
    cout << "Res: " << count(puzzle) << endl;
    
    return 0;
}
