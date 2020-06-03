#include <random>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

vector<vector<int>> permutations_with_repetition(int);
vector<string> comb(vector<vector<int>>, vector<int>);
char operation(int);

int main()
{
	cout << "Input the numbers (end the input with CRTL+Z): ";
	int total;
	vector<int> v;
	int x;
	while (cin >> x)
		v.push_back(x);
	cout << "What should it be equal to?:\n";
	cin >> total;
	vector<vector<int>> matrix = permutations_with_repetition(v.size());
	vector<string> v1 = comb(matrix, v);
	vector<int> index;
	vector<string> correct;
	for (int i = 0; i < v1.size(); i++)
	{
		if (stoi(v1[i]) == total)
		{
			correct.push_back(v1[i]);
			index.push_back(i);
		}
	}
	cout << endl;
	if (correct.size() == 0)
	{
		cout << "\nNo solutions.";
		system("pause");
	}
	for (int i = 0; i < correct.size();i++)
	{
		cout << correct[i] << endl;
	}
	system("pause");
}

vector<vector<int>> permutations_with_repetition(int num)
{
	default_random_engine dre(time(NULL));
	int permutations = 1;
	for (int i = 0; i < num-1 ; i++)
		permutations *= 4; //4 operaciaa
	uniform_int_distribution<int> uid(1, 4);
	vector<vector<int>> perm;
	vector<int> v;
	for (int i = 0; i < permutations; i++)
		perm.push_back(v);
	for (int i = 0; i < permutations; i++)
	{
		for (int j = 0; j < num - 1; j++)
			perm[i].push_back(0);
	}
	int counter = 0;
	while (perm[permutations - 1][num - 2] == 0)
	{
		vector<int> temp;
		for (int i = 0; i < num - 1; i++)
			temp.push_back(0);
		int i = 0;
		int random = uid(dre);
		int x = 0;
		for (int i = 0; i < num - 1; i++)
		{
			temp[i] = uid(dre);
		}
		for (int i = 0; i < permutations; i++)
		{
			if (temp == perm[i])
				x++;
		}
		if (x == 0)
		{
			perm[counter] = temp;
			counter++;
			continue;
		}
	}
	return perm;
}

vector<string> comb(vector<vector<int>> matrix, vector<int> v)
{
	vector<string> v1;
	for (int i = 0; i < matrix.size(); i++)
	{
		string s = "";
		for (int j = 0; j < matrix[i].size(); j++)
		{
			s += to_string(v[j]);
			s += operation(matrix[i][j]);
		}
		s += to_string(v[v.size() - 1]);
		v1.push_back(s);
	}
	return v1;
}

char operation(int n)
{
	if (n == 0)
		return '+';
	if (n == 1)
		return '-';
	if (n == 2)
		return '*';
	if (n == 3)
		return '/';
}