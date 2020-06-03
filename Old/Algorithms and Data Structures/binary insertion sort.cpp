#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
#include <cassert>
using namespace std;
void print(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}

bool binary_recursive(vector<int> v, int x) //binary search: input a sorted vector. amis gaketeba sheileba washlis gareshec, tu dinamiurad shevcvlit borderebs, magalitad inputshi iyos saidan sadamde aketebs programa search-s
{
	int i = v.size() / 2;
	cout << "v.size() == " << v.size() << endl;
	if (v.size() == 0)
		return false;
	if (v[i] == x)
		return true;

	if (x > v[i])
	{
		v.erase(v.begin(), v.begin() + i + 1);
		print(v);
		return binary_recursive(v, x);
	}
	if (x < v[i])
	{
		v.erase(v.begin() + i, v.begin() + v.size());
		print(v);
		return binary_recursive(v, x);
	}
}

bool binary_iterative(vector<int> v, int x)
{
	while (v.size() != 0)
	{
		int i = v.size() / 2;
		cout << "v.size() == " << v.size() << endl;
		if (v[i] == x)
			return true;

		if (x > v[i])
		{
			v.erase(v.begin(), v.begin() + i + 1);
			print(v);
		}
		else	//aq if (x < v[i])-is dawera agar sheileba, roca v carielia wvdoma v[i]-ze (anu v[0]-ze) error-s iwvevs. rekursiulshi meore binary search gamoidzaxeboda da es ar xdeboda
		{
			v.erase(v.begin() + i, v.begin() + v.size());
			print(v);
		}
	}
	return false;
}

void sorted_insert(vector<int>& v, int x) //binary insertion sort
{
	if (x <= v[0])
	{
		v.insert(v.begin(), x);
		return;
	}
	if (v[v.size() - 1] <= x)
	{
		v.push_back(x);
		return;
	}
	for (int i = 0; i < v.size() - 1; i++)
	{
		if (v[i] <= x && x <= v[i + 1])
		{
			v.insert(v.begin() + i + 1, x);
			return;
		}
	}
}

void sorted_insertFast(vector<int>& v, int x)
{
	if (x <= v[0])
	{
		v.insert(v.begin(), x);
		return;
	}
	if (v[v.size() - 1] <= x)
	{
		v.push_back(x);
		return;
	}


	int min = 0;
	int max = v.size() - 1;
	while (1)
	{
		int i = (min + max + 1) / 2; //[min,max] nomrebit elementebis shua. tu araaq shua, meore naxevris pirveli elementis nomeri.
		if (v[i - 1] <= x && x <= v[i])
		{
			v.insert(v.begin() + i, x);
			return;
		}
		if (v[i] <= x && x <= v[i+1])
		{
			v.insert(v.begin() + i + 1, x);
			return;
		}
		if (x < v[i])
			max = i - 1;
		else
			min = i + 1;
	}
}

int main()
{
	default_random_engine dre(time(NULL));
	uniform_int_distribution<int> uid(-100, 100);
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(uid(dre));
	}
	sort(v.begin(), v.end());
	print(v);
	cout << "\n\n\n";
	int a;
	while (cin >> a)
	{
		sorted_insertFast(v, a);
		print(v);
		cout << "\n\n\n";
		//if (binary_iterative(v, a))
		//	cout << "True" << endl;
		//else
		//	cout << "False" << endl;
	}
}