#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>

using namespace std;

string huge_regex = "((";

int main()
{
	string buff;
	vector<string> designs;
	bool foundline = false;

	ifstream f("input.txt");

	getline(f, buff);
	for (int i = 0; i < buff.size(); i++)
	{
		if (buff.at(i) == ',')
		{
			i += 1;
			huge_regex += ")|(";
		}
		else
		{
			huge_regex += buff.at(i);
		}
	}
	huge_regex += "))*$";

	getline(f,buff);

	while (getline(f, buff))
	{
		designs.push_back(buff);
	}
	

	int res = 0;

	cout << huge_regex << endl;

	regex r = regex(huge_regex);

	int line_n = 0;
	size_t sz = designs.size();

	for (string line : designs)
	{
		cout << line_n << " / " << sz << endl;
		cout << line << endl;
		if (regex_match(line, r))
		{
			res++;
		}
		line_n++;
	}

	cout << "res: " << res << endl;

	return 0;
}
