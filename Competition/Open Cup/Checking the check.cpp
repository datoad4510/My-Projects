#include <iostream>
#include <string>
using namespace std;

int main()
{
	string name;
	string cost;
	int total;
	int true_total = 0;
	while (true)
	{
		getline(cin, name);
		if (name == "TOTAL")
		{
			cin >> total;
			break;
		}
		else
			getline(cin, cost);
		int x;
		int y;
		int idx = 0;
		while (cost[idx] != ' ')
			++idx;
		x = stoi(cost.substr(0,idx));
		y = stoi(cost.substr(idx + 1));
		true_total += x * y;
	}
	if (total <= true_total)
	{
		cout << "PAY";
	}
	else
		cout << "PROTEST";
}