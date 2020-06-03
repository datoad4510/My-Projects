#include <iterator>
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

template<typename Iterator>
void print(Iterator first, Iterator last)
{
	while (first != last)
	{
		cout << *first << " ";
		++first;
	}
	cout << endl;
}


template<typename Iterator>
typename iterator_traits<Iterator>::value_type accumulate(Iterator first, Iterator last)
{
	iterator_traits<Iterator>::value_type x{};
	while (first != last)
	{
		x += *first;
		++first;
	}
	return x;
}


template<typename Iterator, typename UnaryPredicate>
void replace_if(Iterator first, Iterator last,typename iterator_traits<Iterator>::value_type value, UnaryPredicate p)
{
	while (first != last)
	{
		if (p(*first))
			*first = value;
		++first;
	}
}



template<typename Iterator, typename UnaryPredicate>
Iterator find_if_not(Iterator first, Iterator last, UnaryPredicate p)
{
	while (first != last)
	{
		if (!p(*first))
			return first;
		++first;
	}
	return first;
}

template<typename Iterator, typename UnaryPredicate>
Iterator partition(Iterator first, Iterator last, UnaryPredicate p)
{
	Iterator it1 = find_if_not(first, last, p);
	Iterator it2 = it1;
	++it2;
	while (it2 != last)
	{
		if (p(*it2))
		{
			iter_swap(it1, it2);
			++it1;
		}
		++it2;
	}
	return it1;
}

template<typename Iterator>
void qsort(Iterator first, Iterator last)
{
	if (distance(first, last) == 1) return;
	auto lambda = [=](typename iterator_traits<Iterator>::value_type y) {return y < *first; };
	Iterator q = partition(first, last, lambda);
	if (q == first) ++q;
	qsort(first, q);
	qsort(q, last);
}

int main()
{
	vector<int> v{ 1,2,3,200,21,11,32343,12,32423,3212,1 };
	auto lambda = [](int x) {return x % 2 == 0; };
	//replace_if(v.begin(), v.end(), 0, lambda);
	qsort(v.begin(), v.end());
	print(v.begin(), v.end());
	//cout << lambda(5) << endl;
	system("pause");
}