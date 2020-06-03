#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void print(const vector<T>& v)
{
	cout << "\n\n";
	for (const auto& m : v)
	{
		cout << " " << m << " ";
	}
	cout << "\n\n";
}

void countingSort(vector<int>& a, vector<int>& b)
{
	int k = *max_element(a.begin(), a.end());
	k++;
	vector<int> c(k);
	for (int i = 0; i< a.size(); i++)
		c[a[i]]++;
	for (int i = 1; i<k; i++)
		c[i] += c[i - 1];
	for (int i = a.size() - 1; i >= 0; i--)
	{
		b[c[a[i]] - 1] = a[i];
		c[a[i]]--;
	}
}

void datos_countsort(const vector<int>& a, vector<int>& b)//b savsea 0-ebit
{
	int k = *max_element(a.begin(), a.end());
	assert(k <= a.size() && a.size() == b.size());
	vector<int> c(k + 1);//nulebit avsebs
	print(c);
	for (int i = 0; i < a.size(); i++)
		++c[a[i]];
	int counter = 0;
	for (int i = 0; i < c.size(); i++)//igive siswrafisaa da gacilebit ufro gasagebia
	{
		while (c[i] != 0)
		{
			b[counter] = i;
			++counter;
			--c[i];
		}
	}

}





int main()
{
	vector<int> v1 = { 3,4,4,3,1 };
	vector<int> v2(v1.size());
	datos_countsort(v1, v2);
	print(v2);
	system("pause");
}