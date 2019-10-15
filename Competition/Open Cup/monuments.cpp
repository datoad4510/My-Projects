#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

int main()
{
	unordered_set<string> places;
	int different_places = 0;
	string temp;
	while (getline(cin,temp))
	{
		string temp1 = temp.substr(11, temp.size());
		auto it = places.find(temp1);
		if (it == places.end())
		{
			places.insert(temp1);
			++different_places;
		}
	}
	cout << different_places << endl;
	system("pause");
}