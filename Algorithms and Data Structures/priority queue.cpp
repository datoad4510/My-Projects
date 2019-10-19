#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

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

template<typename RandomIterator> //es araa <algorithm>-shi
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



template<typename T, typename Container = deque<T> >
class my_priority_queue //iterator-ebze xom ar gadaviyvano rom ar iyos damokidebuli ".end()", ".size()"... metodebze? magram mashin push_back-s rogor shevcvli? new array..? mashin agar imushavebs stl container-ebze
						//
{
private:
	Container a;
public:
	my_priority_queue() {}
	template<typename InIt>
	my_priority_queue(InIt first, InIt last);
	void show();
	int size();
	bool empty();
	void pop();
	void push(T t);
	T top();
	void increase_key(int i, T k);
	void decrease_key(int i, T k);
};

template<typename T, typename Container = deque<T> >
template<typename InIt>
my_priority_queue<T, Container>::my_priority_queue(InIt first, InIt last)
{
	while (first != last)
	{
		a.push_back(*first);
			++first;
	}
	make_heap(a.begin(), a.end());
}
template<typename T, typename Container = deque<T> >
void my_priority_queue<T, Container>::show()
{
	for (int i = 0; i < a.size(); ++i)
		cout << a[i] << '\t';
	cout << endl;
}
template<typename T, typename Container = deque<T> >
int my_priority_queue<T, Container>::size()
{
	return a.size();
}
template<typename T, typename Container = deque<T> >
bool my_priority_queue<T, Container>::empty()
{
	return (0 == a.size());
}
template<typename T, typename Container = deque<T> >
void my_priority_queue<T, Container>::pop()
{
	if (a.size() == 0)
	{
		cout << "Error! queue is empty!" << endl;
		return;
	}
	pop_heap(a.begin(), a.end());
	a.pop_back();
}
template<typename T, typename Container = deque<T> >
void my_priority_queue<T, Container>::push(T t)
{
	a.push_back(t);
	push_heap(a.begin(), a.end());
}
template<typename T, typename Container = deque<T> >
T my_priority_queue<T, Container>::top()
{
	return a[0];
}
template<typename T, typename Container = deque<T> >
void my_priority_queue<T, Container>::increase_key(int i, T k)
{
	if (i < 0 || i >= a.size() || k <= a[i])
		cout << "Error!" << endl;
	else
	{
		a[i] = k;
		while (i>0 && a[parent(i)] < a[i])//daaxloebit push_heap-ia
		{
			T tmp = a[i]; //swap(a[i], a[parent(i)]); i = parent(i); weria realurad
			a[i] = a[parent(i)];
			a[parent(i)] = tmp;
			i = parent(i);
		}
	}
}
template<typename T, typename Container = deque<T> >
void my_priority_queue<T, Container>::decrease_key(int i, T k) //chemi funqcia
{
	if (i < 0 || i >= a.size() || k >= a[i])
		cout << "Error!" << endl;
	else
	{
		a[i] = k;
		heapify(a.begin(), a.end(), i);
	}
}


int main()
{
	vector<int> v{ 2,5,21,1,17,23 };
	my_priority_queue<int> pq(v.begin(), v.end());
	pq.show();
	pq.increase_key(3, 30);
	pq.show();
	pq.decrease_key(0, 15);
	pq.show();
	cout << pq.top() << endl;
	system("pause");
}