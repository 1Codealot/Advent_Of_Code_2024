#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <regex>

using namespace std;

regex pat = regex(R"((mul\(\d{1,3},\d{1,3}\))|(do((n't)?)\(\)))");

bool do_mul = true;

int mult(string func){

    if (func == "do()")
    {
        do_mul = true;
        return 0;
    }

    if (func == "don't()")
    {
        do_mul = false;
        return 0;
    }
        

    int commaidx = func.find(',');

    int res = stoi(func.substr(4, commaidx-4)) * stoi(func.substr(commaidx+1, func.find(')')-1-commaidx)) * do_mul;

    return res;
}

int main()
{
    int res = 0;

    // Read in the input.
    string buff;
    ifstream f("input.txt");

    while (getline(f, buff)){

        auto matches_begin = sregex_iterator(buff.begin(), buff.end(), pat);
        auto matches_end = sregex_iterator();

        for(sregex_iterator i = matches_begin; i != matches_end; ++i){
            smatch match = *i;
            string match_str = match.str();
     
            res += mult(match_str);
        }
 
        buff.clear();
    }
   
    f.close();
   
    cout << res << "\n";

    return 0;
}
