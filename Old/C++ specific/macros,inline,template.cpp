#include <iostream>
#include <random>
#include <ctime>
#include <vector>
using namespace std;
// #define pi 3.14
// #define min(a,b) (a<b?a:b) ტექსტად ჩასვავს
// inline ტექსტად სვავს, არ მიდის ფუნქციისთვის მეხსიერების გამოყოფა და ლოკალური ცვლადების შექმნა და მათთვის მნიშვნელობების მინიჭება
template <typename A>
inline A  Min(A, A);

template <typename B>
inline B Max(B, B);

int main()
{
	default_random_engine dre(time(NULL));
	uniform_int_distribution<int> uid(1, 100000);
	vector<int> v;
	for (int i = 0; i < 100; i++)
	{
		v.push_back(uid(dre));
	}
	int a = 0;
	for (int i = 0; i < v.size(); i++)
	{
		a = Max(a, v[i]);
	}
	sort(v.begin(), v.end());
	cout << "\n\n" << a << endl;
	system("pause");
}

template <typename A>
inline A Min(A x, A y)
{
	return x < y ? x : y;
}

template <typename B>
inline B Max(B x, B y)
{
	return x > y ? x : y;
}