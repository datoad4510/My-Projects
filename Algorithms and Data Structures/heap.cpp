#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/*
template<typename T>
bool less(T x, T y)
{
	return x < y;
}


template<typename Iterator> // val<Iterator> == iterator_traits<Iterator>::value_type shevamoklet
using val = typename iterator_traits<Iterator>::value_type;

template< typename RandomIterator, typename Container = vector< val<RandomIterator> >, typename BinaryPred = less >
class heap
{
	Container heap;
public:
	heap();
	heap(RandomIterator, RandomIterator);
	~heap();
	friend void make_heap();
	friend void pop_heap();
	friend void push_heap(RandomIterator, RandomIterator);
	friend void sort_heapRandomIterator, RandomIterator); //amis mere heap agaraa
	int depth(RandomIterator);
	RandomIterator left(RandomIterator);
	RandomIterator right(RandomIterator);
	RandomIterator parent(RandomIterator);
	bool is_heap();
	friend void heapify(RandomIterator, RandomIterator, RandomIterator);
};
*/

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

int parent(int i)
{
	return (i - 1) / 2;
}

int depth(int i) // depth(i) == log(i + 1)
{
	int counter = 0;
	int k = i + 1;
	while (k != 1)
	{
		k /= 2;
		++counter;
	}
	return counter;
}

template<typename RandomIterator>
void heapify(RandomIterator first, RandomIterator last, int i) //make sure subtree with root i is a heap
{
	int l = left(i);
	int r = right(i);
	int largest;
	if (l < last - first && first[l] > first[i])
		largest = l;
	else largest = i;
	if (r  < last - first && first[r] > first[largest])
		largest = r;
	if (largest != i)
	{
		swap(first[i], first[largest]);
		heapify(first, last, largest);
	}
}

template<typename RandomIterator>
void make_heap(RandomIterator first, RandomIterator last)
{
	int n = last - first - 1;
	for (int i = parent(n); i >= 0; --i)
		heapify(first, last, i);
}

template<typename RandomIterator>
void pop_heap(RandomIterator first, RandomIterator last)
{
	swap(first[0], first[last - first - 1]);
	heapify(first, last - 1, 0);
}

template<typename RandomIterator>
void push_heap(RandomIterator first, RandomIterator last)
{
	int i = last - first - 1;
	while (i > 0 && a[parent(i)] < a[i])
	{
		swap(a[i], a[parent]);
		i = parent(i);
	}
}

template<typename RandomIterator>
void sort_heap(RandomIterator first, RandomIterator last)
{
	while (last - first - 1 > 0)
	{
		pop_heap(first, last);
		--last;
	}
}


int main()
{
	vector<int> v{ 2,3,1,-11,43,2,99,23,1,23,90 };
	for (const auto& m : v)
		cout << m << " ";
	cout << endl;
	make_heap(v.begin(), v.end());
	for (const auto& m : v)
		cout << m << " ";
	cout << endl;
	sort_heap(v.begin(), v.end());
	for (const auto& m : v)
		cout << m << " ";
	cout << endl;
	system("pause");
}