#include<iostream>
#include<fstream>
#include<string>
using namespace std;

unsigned long long int rec_fibonacci(int x) //recursive fibonacci, exponential time
{
	if (x == 1)
		return 1;
	if (x == 2)
		return 1;
	return rec_fibonacci(x - 1) + rec_fibonacci(x - 2);
}

unsigned long long int fibonacci(int x)//dynamic with temporary memory
{
	if (x == 1)
		return 1;
	if (x == 2)
		return 1;
	unsigned long long int* arr = new unsigned long long int[x];
	arr[0] = 1;
	arr[1] = 1;
	for (int i = 2; i < x; i++)
	{
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return arr[x - 1];
}

int find(int x, string s)
{
	ifstream ifs(s);
	int num;
	int ind;
	while (ifs >> num >> ind)
	{
		if (ind == x)
			return num;
	}
	return 0;
}

unsigned long long int d_fibonacci(int x, string s) //permanent memory
{
	unsigned long long int num = find(x, s);
	if (num == 0)//bolo orze wvdoma ar vici rogor unda tore ufro swrafi iqneboda
	{
		ofstream ofs(s, ios::app);
		ifstream ifs(s);
		if (x == 1)
		{
			ofs << "1" << " " << "1" << "\n";
			return 1;
		}
		if (x == 2)
		{
			ofs << "1" << " " << "1" << "\n";
			return 1;
		}

		int temp;
		int counter = 0;
		while (ifs >> temp)
		{
			counter++;
		}
		counter /= 2; //orjer meti striqonia vidre ricxvi

		unsigned long long int* arr = new unsigned long long int[x]; //ise gaakete rom tavidan datvla ar mouwios!!
		arr[0] = 1;
		arr[1] = 1;
		for (int i = 2; i < x; i++)
		{
			arr[i] = arr[i - 1] + arr[i - 2];
		}
		for (int i = counter; i < x; i++)
		{
			ofs << arr[i] << " " << i + 1 << "\n";
		}
		return arr[x - 1];
	}
	return num;
}

int main()
{
	int n;
	cout << "Which Fibonacci number? : ";
	cin >> n;
	cout << "\n\n" << d_fibonacci(n,"data.txt") << "\n\n";
	system("pause");

}