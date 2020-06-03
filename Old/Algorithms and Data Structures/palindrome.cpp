#include <iostream>
#include <string>
using namespace std;
bool palindrome(string str)
{
	for (int i = 0; i < str.size()/2 ; i++)
	{
		if (str[i] != str[str.size() - i - 1])
		{
			return false;
		}
	}
	return true;
}
int main()
{
	string str;
	cout << "Write a string: ";
	getline(cin, str);
	cout << "\n\n";
	if (palindrome(str))
	{
		cout << str << " is a palindrome. " << "\n\n";
	}
	else
	{
		cout << str << " isn't a palindrome. " << "\n\n";
	}
	system("pause");
}