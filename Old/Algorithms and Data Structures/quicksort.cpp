#include <iostream>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

template<class InputIterator, class UnaryPredicate>
InputIterator my_find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first != last) {
		if (!pred(*first)) return first;
		++first;
	}
	return last; //last arasdros dabrundeba quicksortshi
}

template<class ForwardIt, class UnaryPredicate>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
	first = my_find_if_not(first, last, p);
	if (first == last) return first; //es quicksortshi ar gamoiyeneba, radgan yoveltvis pirvelives idzleva quicksort
	for (ForwardIt i = std::next(first); i != last; ++i) {
		if (p(*i)) {
			std::iter_swap(i, first);
			++first;
		}
	}
	return first;
}




template<class ForwardIt>
ForwardIt my_partition_forqs(ForwardIt first, ForwardIt last)//gacilebit ufro gasagebi funqcia
{
	for (ForwardIt i = std::next(first); i != last; ++i) { //radgan pivotad sul pirvel elements virchevt containershi
		if (*i < *first) {
			std::iter_swap(i, first);
			++first;
		}
	}
	return first;
}





template<class ForwardIt>
ForwardIt my_partition_forqs_randompivot(ForwardIt first, ForwardIt last)//igive random pivotit
{
	ForwardIt pivot = first;
	default_random_engine dre(time(NULL));
	uniform_int_distribution<short> uid(0, distance(first, last));
	for (int i = 0; i < uid(dre); ++i)
		++pivot;
	std::iter_swap(pivot, first);

	for (ForwardIt i = std::next(first); i != last; ++i) {
		if (*i < *first) {
			std::iter_swap(i, first);
			++first;
		}
	}
	return first;
}


template<typename ForwardIt>
void qSort(ForwardIt first, ForwardIt last)
{
	if (distance(first, last) > 1)
	{
		auto x = *first;

		//auto lm = [=](decltype(x) y) {return (y < x); };
		//auto q = partition(first, last, lm);

		//auto q = my_partition_forqs(first, last);

		auto q = my_partition_forqs_randompivot(first, last);
		if (q == first) q = std::next(q);
		qSort(first, q);
		qSort(q, last);
	}
}template<typename InputIterator>void print(InputIterator first, InputIterator last){	while (first != last)	{		cout << *first << " ";		++first;	}	cout << endl;}int main(){
	vector<int> v = { 33,1,2,7,3,4,5 };	qSort(v.begin(), v.end());	print(v.begin(), v.end());	system("pause");}