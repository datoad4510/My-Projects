#include <iostream>
#include <iterator>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
bool mygreater(T x, T y)
{
	if (x > y)
		return true;
	else
		return false;
}

template<typename T>
class clgreater
{
public:
	bool operator()(T x, T y)
	{
		if (x > y)
			return true;
		else
			return false;
	}
};

template<typename InputIterator,typename UnaryPredicate>
int my_count_if(InputIterator first, InputIterator last, UnaryPredicate p)
{
	int count = 0;
	while (first != last)
	{
		if (p(*first))
			++count;
		++first;
	}
	return count;
}

int main()
{
	/*
	ostream_iterator<int> out(cout, "\n");
	for (int i = 0; i < 10; i++)
	{
		*out = i;
		++out;
	}
	*/
	vector<int> v{ 1,2,3,4,5,6,7,8,9,10 };
	//cout << count_if(v.begin(), v.end(), bind2nd(mygreater<int>,3)) << endl; funqciebze ar mushaobs
	//cout << count_if(v.begin(), v.end(), bind2nd(clgreater<int>(), 3)) << endl; classebze ar mushaobs
	//cout << count_if(v.begin(), v.end(), bind2nd(greater<int>(), 3)) << endl;//adaptable classebze mushaobs
	auto lambda = [](auto& x) {if (x % 2 == 0) return true; else return false; };
	cout << my_count_if(v.begin(), v.end(), lambda) << endl;
	cin.get();
}