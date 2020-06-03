#include<iostream> //sorting algorithms
#include<string>
#include<vector>
using namespace std;

template<typename T>
void swap(const T& x, const T& y)
{
	T temp = x;
	x = y;
	y = temp;
}

template<typename InputIterator>
void print(InputIterator first,InputIterator last)
{
	while (first != last)
	{
		cout << *first << " ";
		++first;
	}
	cout << endl;
}

template<typename RandomAccessIterator> //container is located in [first,last)
void bubble(RandomAccessIterator first, RandomAccessIterator last)
{
	bool sorted;
	Iterator tfirst;
	Iterator tlast;
	while (true)
	{
		tfirst = first;
		tlast = last;
		sorted = true;
		while (tfirst != tlast - 1)
		{
			if (*tfirst > *(tfirst + 1))
			{
				sorted = false;
				swap(*tfirst, *(tfirst + 1));
			}
			++tfirst;
		}
		if (sorted == true)
			break;
	}
}


int main()
{
	int arr[5] = { 1,7,4,3,2 };
	vector<int> v = { 5,4,3,2,1 };
	bubble(&arr[0], &arr[5]);//pointer is a valid random access iterator
	print(&arr[0], &arr[5]);
	bubble(v.begin(), v.end());
	print(v.begin(), v.end());
	string s = "aslkdfjasldkf";
	bubble(&s[0], &s[s.length()]);
	print(&s[0], &s[s.length()]);
	system("pause");
}