#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>
using namespace std;

int main()
{
	int dummy;
	cin >> dummy;
	string s1;
	string s2;
	cin.ignore(256, '\n');
	getline(cin, s1);
	cin.clear();
	getline(cin, s2);
	vector<int> v1;
	vector<int> v2;
	int starting = 0;
	for (int i = 0; i < s1.size(); ++i)
	{
		if (s1[i] == ' ' || i == s1.size() - 1)
		{
			v1.push_back(stoi(s1.substr(starting, i - starting)));
			starting = i + 1;
		}
	}
	starting = 0;
	for (int i = 0; i < s2.size(); ++i)
	{
		if (s2[i] == ' ' || i == s2.size() - 1)
		{
			v2.push_back(stoi(s2.substr(starting, i - starting)));
			starting = i + 1;
		}
	}
	vector<vector<int>> matrix(v1.size(), vector<int>(v1.size()));
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			matrix[i][j] = abs(v1[i] - v2[j]);
		}
	}
	pair<int, int> alice_max = make_pair(matrix[0][0],0);
	pair<int, int> bob_min = make_pair(matrix[0][0], 0);
	while (matrix.size() > 1 && matrix[0].size() > 1)
	{
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix.size(); ++j)
			{
				if (alice_max.first < matrix[i][j])
					alice_max = make_pair(matrix[i][j], i);
			}
		}
		matrix.erase(matrix.begin() + alice_max.second);
		for (int i = 0; i < matrix.size(); ++i)
		{
			for (int j = 0; j < matrix.size(); ++j)
			{
				if (bob_min.first > matrix[i][j])
					bob_min = make_pair(matrix[i][j], j);
			}
		}
		for (int i = 0; i < matrix.size(); ++i)
		{
			matrix[i].erase(matrix[i].begin() + bob_min.second);
		}
	}
	cout << matrix[0][0];
}