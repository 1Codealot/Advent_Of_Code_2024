#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int WIDTH = 101;
int HEIGHT = 103;
int MIDW = (WIDTH - 1) / 2;
int MIDH = (HEIGHT - 1) / 2;

typedef pair<pair<int, int>, pair<int, int>> robot;
vector<robot> robots;

robot getRobot(string line)
{
    robot r;
    r.first.first = stoi(line.substr(2, line.find(',') - 2));
    r.first.second = stoi(line.substr(line.find(',') + 1, line.find(' ') - line.find(',') + 1));

    r.second.first = stoi(line.substr(line.find_last_of('=') + 1, line.find_last_of(',') - line.find_last_of('=') + 1));
    r.second.second = stoi(line.substr(line.find_last_of(',') + 1));

    return r;
}

void updatePos(robot &r)
{
    r.first.first += r.second.first;
    if (r.first.first < 0)
    {
        r.first.first += WIDTH;
    }
    else if (r.first.first >= WIDTH)
    {
        r.first.first %= WIDTH;
    }

    r.first.second += r.second.second;
    if (r.first.second < 0)
    {
        r.first.second += HEIGHT;
    }
    else if (r.first.second >= HEIGHT)
    {
        r.first.second %= HEIGHT;
    }
}

void printVec(vector<vector<int>> v){
    cout << "\n\n\n\n";
    for (auto &&y : v)
    {
        for (auto &&x : y)
        {
            if (x > 0)
            {
                cout << "■";
            }
            else
            {
                cout << " ";
            }
        }
        cout << "\n";        
    }
    
}

vector<vector<int>> output;

int main()
{
    string buff;
    ifstream f("input.txt");

    while (getline(f, buff))
    {
        robots.push_back(getRobot(buff));
    }
    
    for (size_t y = 0; y < HEIGHT; y++)
    {
        output.push_back({});
        for (size_t x = 0; x < WIDTH; x++)
        {
            output.at(y).push_back(0);
        }    
    }
    
    vector<vector<int>> empty = output;

    unsigned long long idx = 0;
    while(idx++ != 1000000)
    {
        output = empty;
        for (robot& r : robots)
        {
            updatePos(r);
            output.at(r.first.second).at(r.first.first)++;

        }
            printVec(output);
            cout << idx;
    }
    
/*    unsigned long long res = 0;

    int q1 = 0;
    int q2 = 0;
    int q3 = 0;
    int q4 = 0;

    
    for (robot r: robots)
    {
        output.at(r.first.second).at(r.first.first)++;
        cout << r.first.first << "\t" << r.first.second << "\n";
        // Check q1
        if (r.first.first < MIDW && r.first.second < MIDH)
        {
            q1++;
        }
        // Check q2
        if (r.first.first > MIDW && r.first.second < MIDH)
        {
            q2++;
        }
        // Check q3
        if (r.first.first < MIDW && r.first.second > MIDH)
        {
            q3++;
        }
        // Check q4
        if (r.first.first > MIDW && r.first.second > MIDH)
        {
            q4++;
        }
    }

    for (auto &&i : output)
    {
        for (auto &&ii : i)
        {
            cout << ii;
        }
        cout << endl;        
    }
    
        
    res = q1*q2*q3*q4;
    cout << "Res: " << res << "\n";
*/
    return 0;
}