#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	vector<int> v;
	long long int a, i, d, t;
	t = 0;
	i = 2;
	cout << "Input a number: ";
	cin >> a;
	while (i <= a + 1)
	{
		d = a%i;
		if (a == 1) { cout << "\n1 is neither prime nor composite.\n\n"; break; }
		if (a == 2 || a == 3 || a == 5) { cout << "\nThe number is prime.\n\n"; break; }
		if (a == 4) { cout << "\n2*2 = 4\nThe number isn't prime.\n"; cout << "\nIt has 1 divisor not including the number 1.\n\n";  break; }
		if (d != 0)
		{
			i++;
		}
		if (d == 0)
		{
			v.push_back(i);
			i++;
		}
		if (v.size() == 0 && i == (a / 2))
		{
			cout << "\nThe number is prime.\n\n";
			break;
		}
		if (i > (a / 2))
		{
			sort(v.begin(), v.end());
			while (t < v.size())
			{
				cout << "\n" << v[t] << " * " << a / (v[t]) << " = " << a << endl;
				t++;
			}
			cout << "\nThe number isn't prime.\n";
			cout << "\nIt has " << v.size() << " divisors not including the number 1.\n\n";
			break;
		}
	}
	system("PAUSE");
}
