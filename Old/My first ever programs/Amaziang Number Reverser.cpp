#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main()
{
	vector<long long int> v;
	long long int a,temp(1),result(0),counter(0);
	cout << "Input a number: ";
	cin >> a;
	while (temp != 0)
	{	
		if (a < 10) { v.push_back(a); break; }
		temp = a % 10;
		v.push_back(temp);
		a = (a - a % 10)/10;
	}
	while (counter < v.size())
	{
		result = result + v[v.size() - counter - 1] * pow(10, counter);
		counter++;
	}
	cout << "\n" << result << endl;
	system("PAUSE");



}