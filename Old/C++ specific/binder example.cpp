#include <iostream>
#include <functional>
#include <string>
using namespace std;


int main()
{
	greater<int> g;
	cout << "1 > 2 == " << g(1,2) << endl;
	cout << "1 > 2 == " << bind2nd(greater<int>(), 2)(1) << endl; //turns a binary functor into a unary one by fixing the second argument
	system("pause");
}