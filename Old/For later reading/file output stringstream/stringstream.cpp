#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
void showmat(const vector<vector<T>>& m)
{
	for (int i = 0; i < m.size(); i++)
	{
		for (int j = 0; j < m[i].size(); j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	vector<vector<int>> m;
	string s;
	ifstream ifs("data.txt");
	while (getline(ifs, s))
	{
		vector<int> tmp;
		int n;
		istringstream iss(s);
		while (iss >> n)
			tmp.push_back(n);
		m.push_back(tmp);
	}
	showmat(m);
	system("pause");
}