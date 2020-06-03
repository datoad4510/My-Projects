#include <iostream>
#include <iomanip>
using namespace std;
int main() {

	double b;
	double sum = 0;
	while (cin >> b)
	{
		sum = sum + b;
	}
	cout << fixed << setprecision(2) << sum;
}