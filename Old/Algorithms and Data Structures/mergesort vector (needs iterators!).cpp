#include <iostream>
#include "limits.h"
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
void print(const vector<T>& v)
{
	cout << endl;
	for (auto m : v)
		cout << m << " ";
	cout << endl;
}

vector<int> merge(vector<int>& v1, vector<int>& v2) //ganzogadeba ar iqneba rtuli. v1 da v2 sortirebulebi unda iyvnen. reference rames apuchebs?
{
	vector<int> v3;
	int size3 = v1.size() + v2.size();
	v1.push_back(INT_MAX);//sentinel variables
	v2.push_back(INT_MAX);
	int j = 0;
	int k = 0;

	for (int i = 0; i < size3; i++)
	{
		if (v1[j] <= v2[k])
		{
			v3.push_back(v1[j]);
			++j;
		}
		else
		{
			v3.push_back(v2[k]);
			++k;
		}
	}
	v1.pop_back();//removing sentinels
	v2.pop_back();
	return v3;
}

vector<int> mergesort(vector<int>& v)//iteratorebze tu gadaviyvan merge-s argumentebs ar iqneba sajiro am veqtorebis sheqmna
{
	int q = v.size() / 2;
	if (q == 0)
		return v; //base case
	vector<int> v1;
	vector<int> v2;
	for (int i = 0; i < q; i++)
		v1.push_back(v[i]);
	for (int i = q; i < v.size(); i++)
		v2.push_back(v[i]);
	return merge(mergesort(v1), mergesort(v2)); //es v-s ar cvlis. bolos sajiroa v = mergesort(v). iteratorebs ar dasjirdeba.
}


int main()
{
	vector<int> v1 = { 2,7,1,2,5,3,10,4 };
	print(mergesort(v1));
	system("pause");
}