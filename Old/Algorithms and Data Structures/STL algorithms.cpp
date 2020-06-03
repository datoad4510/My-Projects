#include<iostream>
#include<iterator>
#include<cassert>
#include<vector>
using namespace std;


template<typename InputIterator>
InputIterator find(InputIterator first, InputIterator last,iterator_traits<InputIterator>::value_type value)
{
	while (first != last)
	{
		if (*first == value)
			return first;
		++first;
	}
	return first;
}

template<typename InputIterator,typename UnaryPredicate>
InputIterator find_if(InputIterator first, InputIterator last,UnaryPredicate p)
{
	while (first != last)
	{
		if (p(*first))
			return first;
		++first;
	}
	return first;
}

template<typename InputIterator, typename UnaryPredicate>
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

template<typename InputIterator>
int count(InputIterator first, InputIterator last,iterator_traits<InputIterator>::value_type value)
{
	int count = 0;
	while (first != last)
	{
		if (first == value)
		{
			++count;
			++first;
		}
	}
	return count;
}

template<typename InputIterator, typename UnaryPredicate>
int count_if(InputIterator first, InputIterator last, UnaryPredicate p)
{
	int count = 0;
	while (first != last)
	{
		if(p(*first))
		{
			++count;
			++first;
		}
	}
	return count;
}

template<typename InputIterator>
iterator_traits<InputIterator>::value_type accumulate(InputIterator first, InputIterator last)
{
	iterator_traits<InputIterator>::value_type acc{};
	while (first != last)
	{
		acc += *first;
		++first;
	}
	return acc;
}

template<typename InputIterator>
typename iterator_traits<InputIterator>::value_type scalar_product(InputIterator first1, InputIterator last1, InputIterator first2,InputIterator last2)
{
	assert(distance(first1, last1) == distance(first2, last2));
	typename iterator_traits<InputIterator>::value_type temp{};
	while (first1 != last1)
	{
		temp += (*first1) * (*first2);
		++first1;
		++first2;
	}
	return temp;
}

template<typename ForwardIterator,typename UnaryPredicate>
ForwardIterator partition(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
{
	first = find_if_not(first, last, p);
	if (first == last) return first;
	for (ForwardIt i = next(first); i != last; ++i) {
		if (p(*i)) {
			iter_swap(i, first);
			++first;
		}
	}
	return first;
}


template<typename BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last)
{
	while (first != last && first != --last) //[first,last) raxancaa last gvkidia.
	{
		iter_swap(first, last);
		++first;
	}
}

template<typename InputIterator,typename OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
	while (first != last)
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}



int main()
{
	vector<int> v1 = { 1,2,3 };
	vector<int> v2 = { 4,5,6 };
	cout << scalar_product(v1.begin(), v1.end(), v2.begin(), v2.end()) << endl;
	system("pause");
}