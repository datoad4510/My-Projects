#include <vector>
#include <iostream>
using namespace std; //assuming there are no duplicates in the sets. normalize deletes duplicates

template<typename A>//fix the functions
void normalize(vector<A>& v);

template<typename A>
vector<A> set_intersection(vector<A>&, vector<A>&);

template<typename A>
vector<A> set_union(vector<A>&, vector<A>&);

template<typename A>
vector<A> set_difference(vector<A>&, vector<A>&);

template<typename A>
void print(const vector<A>& v)
{
	for (auto m : v)
	{
		cout << m << " ";
	}
}

template<typename A>
void input(vector<A>& v)
{
	A temp;
	while (cin >> temp)
	{
		v.push_back(temp);
	}
}

int main()
{
	vector<int> v1;
	input(v1);
	cin.clear();
	vector<int> v2;
	input(v2);
	cin.clear();
	normalize(v1);
	normalize(v2);
	vector<int> v3 = set_difference(v1, v2);
	print(v3);
	getchar();
}

template<typename A>
void normalize(vector<A>& v)
{
	vector<A> temp;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < temp.size(); j++)
		{
			if (temp[j] == v[i])
				break;
			if (j == temp.size() - 1)
				temp.push_back(v[i]);
		}
	}
	v = temp;
}


template<typename A>
vector<A> set_intersection(vector<A>& v1, vector<A>& v2)
{
	vector<A> v;
	for (int i = 0; i < v1.size(); i++)
	{
		for (int j = 0; j < v2.size(); j++)
		{
			if (v1[i] == v2[j])
			{
				v.push_back(v1[i]);
				break;
			}
		}
	}
	return v;
}


template<typename A>
vector<A> set_union(vector<A>& v1, vector<A>& v2)
{
	vector<A> v = v1;
	for (int i = 0; i < v2.size(); i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			if (v[j] == v2[i])
				break;
			if (j == v.size() - 1)
				v.push_back(v2[i]);
		}
	}
	return v;
}

template<typename A>
vector<A> set_difference(vector<A>& v1, vector<A>& v2)
{
	vector<A> v;
	for (int i = 0; i < v2.size(); i++)
	{
		bool contains = false;
		for (int j = 0; j < v1.size(); j++)
		{
			if (v2[i] == v1[j])
			{
				contains = true;
				break;
			}
		}
		if (contains == true)
			continue;
		else
			v.push_back(v1[i]);
	}
	return v;
}




