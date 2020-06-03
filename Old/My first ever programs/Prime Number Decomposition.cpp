#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int isprime(unsigned long long int);
int isprime(unsigned long long int a) {
	unsigned long long int i, d, t;
	t = 0;
	i = 2;
	while (i <= a + 1)
	{
		d = a % i;
		if (a == 1) { return 0; break; }
		if (a == 2 || a == 3 || a == 5) { return 1; break; }
		if (a == 4) { return 0; break; }
		if (d != 0)
		{
			i++;
		}
		if (d == 0)
		{
			return 0;
			break;
		}
		if (a % i != 0 && i == (a / 2))
		{
			return 1;
			break;
		}
	}

}


int main()
{
	vector<int> v;
	unsigned long long int a, i, t, temp_a, m;
	t = 1;
	i = 2;
	cout << "Input a number: ";
	cin >> a;
	temp_a = a;
	while (i <= temp_a + 1)
	{
		if (a%i == 0 && isprime(i))
		{
			while (a % i == 0) { v.push_back(i); a = a / i; }
			i++;
			continue;
		}
		if (i >= temp_a / 2 && v.size() == 0)
		{
			cout << "The number is prime." << endl; break;
		}
		if (i >= (temp_a / 2))
		{
			cout << v[0];
			while (t < v.size())
			{
				cout << " * " << v[t];
				t++;
			}
			cout << " = " << temp_a << endl;
			break;
		}
		i++;

	}
	system("PAUSE");
}

