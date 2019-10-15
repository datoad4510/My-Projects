#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int test = 0;

template<typename InputIterator>
void print(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		cout << *first << " ";
		++first;
	}
	cout << endl;
}

template<typename InputIterator,typename UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate p)
{
	while (first != last)
	{
		if (!p(*first))
			return first;
		++first;
	}
	return first;
}

template<typename ForwardIterator,typename UnaryPredicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
{
	first = find_if_not(first, last, p);
	if (first == last)
		return first;
	ForwardIterator f = first;
	++first;
	while (first != last)
	{
		if (p(*first))
		{
			iter_swap(f, first);
			++f;
		}
		++first;
	}
	return f;
}


template<typename ForwardIterator>
void qsort(ForwardIterator first, ForwardIterator last)
{
	if (distance(first, last) == 1) return;
	++test;
	if (test == 30)
		return;
	auto y = *first;
	auto q = [=](decltype(y) x) {return x <= y; };//tavis tavze naklebi arasdros iqneba, amitom
	ForwardIterator it = partition(first, last, q);//it == first mainc iqneba tu arcerti araa masze patara.  find_if_not yoveltvis first-s daabrunebs
	print(first, last);//aq rom <= iyos, find_if_not-ma sheidzleba ar ipovos araferi da daabrunos last. mashin partition-ic daabrunebs last-s
	if (it == first) ++it;
	qsort(first, it);//amis gamo, isev qsort(first,last) gamoidzaxeba da icikleba
	qsort(it, last);
}



int main()
{
	vector<int> v{12,44,37,6,0,4, 3,23,1,6,5,3,11,21 };
	auto x = v[0];
	//int gap = *partition(v.begin(), v.end(), [=](int y) {return y <= x; });
	qsort(v.begin(), v.end());
	print(v.begin(), v.end());
	//cout << "\n" << gap << endl;
	cin.get();
}