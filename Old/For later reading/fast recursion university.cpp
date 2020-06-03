#include<iostream>
#include<vector>
#include<map>
#include<time.h>
using namespace std;
int f(int i);
int f(int i, map<int, int> & a);
int read(int i, map<int, int> & a);
const int N = 390;
int main()
{
	clock_t st, fin;
	st = clock();
	vector<int> v(N + 1);
	for (int i = 0; i<v.size(); i++)
	{
		int a, b;
		if (i - 11 >= 0)
			a = v[i - 11];
		else
			a = 1;
		if (i - 22 >= 0)
			b = v[i - 22];
		else
			b = 1;
		v[i] = a + b;
	}
	fin = clock();
	cout << "\n veqtoris DRO: " << ((double)(fin - st)) / CLOCKS_PER_SEC << endl << endl;

	for (int i = 0; i<v.size(); i++)
	{
		cout << "i=" << i << "\t" << "v[" << i << "]=" << v[i] << endl;
	}
	map<int, int> m;
	cout << endl << endl;
	system("PAUSE");
	st = clock();
	m[N] = f(N, m);
	fin = clock();
	cout << "\n asaxvis DRO: " << ((double)(fin - st)) / CLOCKS_PER_SEC << endl << endl;
	map<int, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
	{
		cout << "i=" << it->first << "\t" << "m[" << it->first << "]=" << it->second << endl;
	}
	cout << endl << endl;
	system("PAUSE");
	st = clock();
	cout << "esaa martivi rekursiit: " << f(N) << endl;
	fin = clock();
	cout << "martivi rekursiis dro " << ((double)(fin - st)) / CLOCKS_PER_SEC << endl;
}
int f(int i) {
	if (i<0) return 1;
	return f(i - 11) + f(i - 22);
}
int f(int i, map<int, int> & a) {
	if (i<0) return 1;
	return read(i - 11, a) + read(i - 22, a);
}
int read(int i, map<int, int> & a) {
	if (i<0) return 1;
	if (a.find(i) != a.end())
		return a[i];
	return a[i] = f(i, a);
}