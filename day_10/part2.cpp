#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int trails = 0;

typedef pair<int, int> coords; // first x, second y

bool operator==(const coords& l, const coords& r){
    return (l.first == r.first) && (l.second == r.second);
}

bool coords_exist(vector<coords> vc, coords c){
    for (auto &&i : vc)
    {
       if (i == c)
       {
        return true;
       }
    }
    return false;
}

void traverse(vector<string> map, int x, int y, vector<coords>& end_coords){
    char currently_at = map.at(y).at(x);
    // Base case
    if(currently_at == '9'){ // Yes im using chars for this
        coords end_coord = {x,y};

        end_coords.push_back(end_coord);
        return;
    }
    
    
    // TODO: OOB CHECKS
    // Look up
    if(y>0){
        if(map.at(y-1).at(x) == currently_at+1){
            traverse(map, x, y-1, end_coords);
        }
    }
    
    // Look down
    if(y<map.size()-1){
        if(map.at(y+1).at(x) == currently_at+1){
            traverse(map, x, y+1, end_coords);
        }
    }
    
    // Look left
    if(x>0){
        if(map.at(y).at(x-1) == currently_at+1){
            traverse(map, x-1, y, end_coords);
        }
    }
    
    // Look right
    if(x<map.at(0).size()-1){
        if(map.at(y).at(x+1) == currently_at+1){
            traverse(map, x+1, y, end_coords);
        }
    }
    
}


int main(){
    string buff;
    
    vector<string> map;
    
    ifstream f("input.txt");
    
    while(getline(f, buff)){
        map.push_back(buff);
        buff.clear();
    }
    
    for(int y = 0; y < map.size(); y++){
        for(int x = 0; x < map.at(0).size(); x++){
            if(map.at(y).at(x) == '0'){
                // Find how many times I can find a 9 starting here
                vector<coords> end_coords;
                traverse(map, x, y, end_coords);
                trails += end_coords.size();
                end_coords.clear();
            }
        }
    }
    cout << "Res: " << trails << "\n";
}
