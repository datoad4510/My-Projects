#include <iostream>
using namespace std;

bool is_lucky(int x)
{
	if(x < 0)
		x *= -1;
	if (x % 7 == 0)
		return true;

	int last_digit = x % 10;
	if (last_digit == 7)
		return true;
	while (x != 0)
	{
		x -= last_digit;
		x /= 10;
		last_digit = x % 10;
		if (last_digit == 7)
			return true;
	}
	return false;
}

int main()
{
	int size;
	cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		cin >> arr[i];
	}
	for (int i = 0; i < size; ++i)
	{
		cout << is_lucky(arr[i]) << endl;
	}
	delete[] arr;
}