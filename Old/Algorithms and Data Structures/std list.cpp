#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

template<typename InputIterator, typename T>
InputIterator my_find(InputIterator first, InputIterator last, T val)
{
	while (first != last && *first != val)
		++first;
	return first;
}

template<typename InputIterator, typename Predicate>
InputIterator my_find_if(InputIterator first, InputIterator last, Predicate pred)
{
	while (first != last && !pred(*first))
		++first;
	return first;
}

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

int main()
{
	list<int> l = { 5,1,2,3,12,4 };
	//sort(l.begin(), l.end(),[](int x, int y) {return x > y; }); std::sort requires random access iterators. std::list has bidirectional iterators,therefore this doesn't work.
	l.sort([](int x, int y) {return x > y; }); //reverses the order. the predicate determines whether x goes before y. 0 means no, otherwise yes. the list will be sorted using this binary relation
	print(l.begin(), l.end());
	system("pause");

}