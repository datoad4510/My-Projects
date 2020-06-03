#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class stack
{
	vector<T> v;
public:
	int size();
	void push(T);
	T top();
	void pop();
	bool empty();
};

template<typename T>
int stack<T>::size()
{
	return v.size();
}

template<typename T>
void stack<T>::push(T x)
{
	v.push_back(x);
}

template<typename T>
void stack<T>::pop()
{
	v.pop_back();

}

template<typename T>
bool stack<T>::empty()
{
	return v.size() == 0;
}

template<typename T>
T stack<T>::top()
{
	return v[v.size() - 1];
}

template<typename T>
class queue
{
	vector<T> v;
public:
	int size();
	void push(T);
	T front();
	T back();
	void pop();
	bool empty();
};

template<typename T>
int queue<T>::size()
{
	return v.size();
}

template<typename T>
void queue<T>::push(T x)
{
	v.push_back(x);
}

template<typename T>
void queue<T>::pop()
{
	v.pop_front();

}

template<typename T>
bool queue<T>::empty()
{
	return v.size() == 0;
}

template<typename T>
T queue<T>::front()
{
	return v[0];
}

template<typename T>
T queue<T>::back()
{
	return v[v.size() - 1];
}
