#include <iostream>
#include <iterator>
#include "limits.h"
#include <vector>
using namespace std;

template<typename InputIterator>
void print(InputIterator first,InputIterator last)
{
	cout << endl;
	while (first != last)
	{
		cout << *first << " ";
		++first;
	}
	cout << endl;
}

/*
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


template<typename InputIterator1,typename InputIterator2,typename OutputIterator>
void merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator first3)//make sure we can write stuff after first3
{
	*last1 = INT_MAX;//this won't work for objects. one has to recreate the function by writing here the maximum possible value for an object. or, we can create a slower general algorithm
	*last2 = INT_MAX;//also, this might be dangerous. we don't know what's written in last.

	while (first1 != last1 || first2 != last2)
	{
		if (*first1 < *first2)
		{
			*first3 = *first1;
			++first1;
			++first3;
		}
		else
		{
			*first3 = *first2;
			++first2;
			++first3;
		}
	}
}

*/

template<typename InputIterator1, typename InputIterator2, typename OutputIterator>//first3 aucileblad amat shoris ar unda iyos.
void merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator first3)//make sure we can write stuff after first3
{

	while (first1 != last1 || first2 != last2)
	{
		if (first1 == last1)//this is slower because of these comparisons. but now, it's more general
		{
			while (first2 != last2)
			{
				*first3 = *first2;
				++first2;
				++first3;
			}
			return;
		}
		if (first2 == last2)
		{
			while (first1 != last1)
			{
				*first3 = *first1;
				++first1;
				++first3;
			}
			return;
		}
		if (*first1 < *first2)
		{
			*first3 = *first1;
			++first1;
			++first3;
		}
		else
		{
			*first3 = *first2;
			++first2;
			++first3;
		}
	}
}

/*
template<typename ForwardIterator>
void mergesort(ForwardIterator first,ForwardIterator last)
{
	int q = distance(first,last) / 2;
	if (q == 0)
		return; //base case

	vector<iterator_traits<ForwardIterator>::value_type> v;//bevr mexsierebas iyenebs...
	ForwardIterator First = first;



	while (first != last) //v.size() == distance(first,last) amis mere
	{
		v.push_back(*first);
		++first;
	}


	mergesort(v.begin(), v.begin() + q);// [first,middle) U [middle,last)- ad daiyofa
	mergesort(v.begin() + q, v.end());
	merge(v.begin(), v.begin() + q, v.begin() + q, v.end(), First);
}
*/

template<typename ForwardIterator>//without using any libraries!
void mergesort(ForwardIterator first, ForwardIterator last)
{
	int q = distance(first, last) / 2;
	if (q == 0)
		return; //base case

	int size = distance(first, last);

	iterator_traits<ForwardIterator>::value_type* arr = new iterator_traits<ForwardIterator>::value_type[distance(first,last)];//bevr mexsierebas iyenebs...
	ForwardIterator First = first;


	int i = 0;
	while (first != last)
	{
		arr[i] = *first;
		++first;
		++i;
	}


	mergesort(arr, arr + q);// [first,middle) U [middle,last)- ad daiyofa
	mergesort(arr + q, arr + size);//arr + size == arr[size] (anu ertit zedmeti, lastis pontshi)
	merge(arr, arr + q, arr + q, arr + size, First);
	delete[] arr;
}

int main()
{
	vector<int> v1 = { 2,7,1,2,5,3,10,4 };
	mergesort(v1.begin(),v1.end());
	print(v1.begin(), v1.end());
	system("pause");
}