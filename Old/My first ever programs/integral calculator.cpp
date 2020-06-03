#include <iostream>
#include <cmath>
using namespace std;
double function(double);
int main()
{
	double i, a, b, width, number, area(0);
	cout << "Please input the lower bound: ";
	cin >> a;
	cout << "\nPlease input the upper bound: ";
	cin >> b;
	cout << "\nPlease input the number of rectangles for riemman integration: ";
	cin >> number;
	width = (b - a) / number;
	i = a;
	while (i >= a && i <= b)
	{
		area = area + function(i)*width;
		i = i + width;
	}
	cout << "\nThe integral from " << a << " to " << b << " is " << area << endl << endl;

	system("pause");

}
double function(double i)
{
	return i*i*i;
}