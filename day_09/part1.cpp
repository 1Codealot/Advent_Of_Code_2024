#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

typedef struct part
{
    int id;
    int count;
} part;

using namespace std;

bool isBlank(struct part p){
    return p.id == -1;
}

bool isDefragmented(vector<part> hard_disk){
    int idx = 0;
    while (!isBlank(hard_disk.at(idx)))
    {
        idx++;
    }
    if (idx == hard_disk.size())
    {
        return false;
    }

    // Found a blank 
    for (; idx < hard_disk.size(); idx++)
    {
        if (!isBlank(hard_disk.at(idx)))
        {
            return false;
        }
    }
    return true;
}

int main(){
    string line;

    fstream f("input.txt");

    getline(f, line);

    f.close();

    vector<struct part> hard_disk;

    int id = 0;
    for (size_t i = 0; i < line.size(); i++)
    {
        if(i % 2 == 0){
            hard_disk.push_back({
                .id = id,
                .count = line.at(i) - '0'
            });
            id++;
        }
        else
        {
            hard_disk.push_back({
                .id = -1,
                .count = line.at(i) - '0'
            });
        }
    }

    
    // Defragment
    
    while (!isDefragmented(hard_disk))
    {
        auto first_blank = *(find_if(hard_disk.begin(), hard_disk.end(), isBlank));
        auto last_non_blank = *(find_if_not(hard_disk.rbegin(), hard_disk.rend(), isBlank));

        if (first_blank.count == last_non_blank.count)
        {
            *find_if(hard_disk.begin(), hard_disk.end(), isBlank) = {
                .id = last_non_blank.id,
                .count = last_non_blank.count
            };
            *(find_if_not(hard_disk.rbegin(), hard_disk.rend(), isBlank)) = {
                .id = -1,
                .count = 0
            };
            continue;
        }

        if (first_blank.count > last_non_blank.count)
        {
            // Find the blank's index
            int idx = distance(hard_disk.begin(), find(hard_disk.begin(), hard_disk.end(), first_blank)) + 1;
            hard_disk.insert(hard_disk.begin() + idx, last_non_blank);

            hard_disk.at(idx+1).count -= first_blank.count > last_non_blank.count;

            *(find_if_not(hard_disk.rbegin(), hard_disk.rend(), isBlank)) = {
                .id = -1,
                .count = 0
            };
            continue;
        }

        if (first_blank.count < last_non_blank.count)
        {
            // Replace the blank
            
            
            

        }        
    }    

    return 0;
}