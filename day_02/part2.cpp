
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int safe_count = 0;

vector<int> split(string line){
    vector<int> res;
   
    string buff = "";
   
    for(char x: line){
        if(x==' '){
            res.push_back(stoi(buff));
            buff = "";
        } else {
            buff += x;
        }
    }
    res.push_back(stoi(buff)); // I FORGOT THIS LINE AND I KEPT GEIING IT WRONG FML!!!!
    return res;
}

bool check_safety(vector<int> vals){
    bool is_increasing = vals.at(0) < vals.at(1);

    if (is_increasing)
    {
        for (size_t i = 1; i < vals.size(); i++)
        {
            if (vals.at(i-1) > vals.at(i))
            {
                return false;
            }
            

            int diff = vals.at(i) - vals.at(i-1);
            if(diff < 1 || diff > 3){
                return false;
            }
        }
    }
    else{
        // Decreasing

        int last_num = vals.at(0);

        for (size_t i = 1; i < vals.size(); i++)
        {
            int diff = -(vals.at(i) - last_num);
            if(diff < 1 || diff > 3){
                return false;
            }
            last_num = vals.at(i);
        }
    }
    return true;
}

bool check_dampened_safety(vector<int> vals){
    if (check_safety(vals))
    {
        return true;
    }
    // Dampening
    vector<vector<int>> vecs; // OHGOD DOUBLE NESTED VECs!!!!

    for (size_t i = 0; i < vals.size(); i++)
    {
        vecs.push_back(vals);
        vecs.at(i).erase(vecs.at(i).begin()+i);
    }

    
    for (size_t i = 0; i < vecs.size(); i++)
    {
        if (check_safety(vecs.at(i)))
        {
            return true;
        }
        
    }
    return false; 
}

int main(){
   
    // Read in the input.
    string buff;
    ifstream f("input.txt");

    while (getline(f, buff)){
        if (check_dampened_safety(split(buff)))
        {
            safe_count++;
        }
        
        buff.clear();
    }
   
    f.close();
   
    cout << "Safe count: " << safe_count << "\n";

    return 0;
}
