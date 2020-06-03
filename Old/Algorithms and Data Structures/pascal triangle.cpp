#include <iostream> //we are choosing speed at the cost of memory. the approach is dynamic
#include <vector>
#include <cassert>
using namespace std;

unsigned long long factorial(unsigned long long n)
{
	assert(n >= 0);
	if (n == 0)
		return 1;
	unsigned long long temp = 1;
	while (n > 0)
	{
		temp *= n;
		--n;
	}
	return temp;
}

unsigned long long combination(unsigned long long k,unsigned long long n)
{
	return factorial(n) / ((factorial(k))*(factorial(n - k)));
}

vector<vector<unsigned long long int>> pascal_full(int rows) //this calculates the whole triangle, not optimised
{
	assert(rows > 0);
	vector<vector<unsigned long long int>> triangle(rows);
	for (int i = 0; i < rows; i++)
	{
		triangle[i].push_back(1);
		for (int j = 1; j < i; j++)
		{
			triangle[i].push_back(triangle[i - 1][j - 1] + triangle[i - 1][j]);
		}
		triangle[i].push_back(1);
	}
	return triangle;
}

void print_triangle(vector<vector<unsigned long long int>> tr)
{
	int spaces = tr.size();
	for (int i = 0; i < tr.size(); i++)
	{
		for (int t = 0; t < spaces; t++)
			cout << " ";
		--spaces;
		for (int j = 0; j < i + 1; j++) //assuming it's a triangle
		{
			cout << tr[i][j] << " ";
		}
		cout << endl;
	}
}

void lowmem_pascal(int rows)//this only keeps two rows in memory
{
	assert(rows > 0);
	vector<vector<unsigned long long int>> pair(2);

	pair[0].push_back(1);
	for (int i = 0; i < rows; i++)
		cout << " ";
	cout << 1 << endl;
	int temp = rows - 1;

	for (int i = 1; i < rows; i++)
	{
		pair[1].push_back(1);
		for (int j = 1; j < i; j++)
		{
			pair[1].push_back(pair[0][j - 1] + pair[0][j]);
		}
		pair[1].push_back(1);
		for (int j = 0; j < temp; j++)
			cout << " ";
		for (int j = 0; j < i + 1; j++)
			cout << pair[1][j] << " ";
		cout << endl;
		pair[0] = pair[1];
		pair[1] = {};
		--temp;
	}
}

void slowverylowmem_pascal(int rows) //this is after knowing the closed form solution to the pascal triangle
{
	int spaces = rows;
	for (int i = 0; i < rows; i++)
	{

		for (int j = 0; j < spaces; j++)
			cout << " ";
		--spaces;

		for (int j = 0; j < i + 1; j++)
		{
			cout << combination(j, i) << " ";
		}
		cout << endl;
	}
}

int main()
{
	int rows;
	cout << "Input the number of rows: ";
	cin >> rows;
	cout << "\nHere are the first " << rows << " rows of the Pascal Triangle:\n\n";
	//print_triangle(pascal_full(rows));
	//lowmem_pascal(rows);
	slowverylowmem_pascal(rows);
	cout << endl;
	system("pause");
}