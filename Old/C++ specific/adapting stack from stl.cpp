#include<iostream>
#include<vector>
#include<deque>
#include<list>
using namespace std; //adapterit stack-is sheqmna
template<typename T, typename Container = deque<T> >
class myStack {
private:
	Container a;
public:
	void push(T t) {
		a.push_back(t);
	}
	void pop(void) {
		a.pop_back();
	}
	int size() {
		return a.size();
	}
	T& top() {
		return a.back();
	}
	bool empty() {
		return (0 == a.size());
	}
};
int main()
{
	myStack<int, deque<int> > a;
	a.push(11);
	a.push(22);
	a.push(4444);
	a.push(555);
	while (!a.empty())
	{
		cout << a.top() << endl;
		a.pop();
	}
	cout << "Stack with default container:" << endl;
	myStack<double> s;
	s.push(1.1);
	s.push(22);
	s.push(44.44);
	s.push(55.5);
	while (!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}
}