#include <iostream>
#include <cassert>
using namespace std;

long long factorial(long long n)
{
	assert(n >= 0);
	if (n == 0)
		return 1;
	long long temp = 1;
	while (n > 0)
	{
		temp *= n;
		--n;
	}
	return temp;
}

long long power(long long a, long long n)
{
	long long tmp = 1;
	for (int i = 0; i < n; i++)
	{
		tmp *= a;
	}
	return tmp;
}

long long combination(long long k, long long n)
{
	return factorial(n) / ((factorial(k))*(factorial(n - k)));
}




long long k_partition_repetition_withzeros(long long k, long long n)
{
	return ((factorial(n + k - 1))) / ((factorial(n))*(factorial(k - 1)));
}

long long k_partition_repetition(long long k, long long n)
{
	return combination(k - 1, n - 1);
}

long long k_partition(long long k, long long n) //incorrect
{
	return k_partition_repetition(k, n) / (factorial(k));
}

int main()
{
	long long k;
	cout << "k = ";
	cin >> k;
	assert(k > 0);
	long long n;
	cout << "\nn = ";
	cin >> n;
	assert(n > 0);
	cout << "\n\n\n";
	cout << k_partition(k, n) << endl;
	system("pause");
}