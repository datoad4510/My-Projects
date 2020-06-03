#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
using namespace std;
const int max_tries = 6;
void print(int try_num)
{
	cout << "\n";
	if (try_num == 0)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << "        |" << endl;
		cout << "\t" << "        |" << endl;
		cout << "\t" << "        |" << endl;
	}
	if (try_num == 1)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "        |" << endl;
		cout << "\t" << "        |" << endl;
	}
	if (try_num == 2)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "/       |" << endl;
		cout << "\t" << "        |" << endl;
	}
	if (try_num == 3)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "/ \\     |" << endl;
		cout << "\t" << "        |" << endl;
	}
	if (try_num == 4)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "/|\\     |" << endl;
		cout << "\t" << "        |" << endl;
	}
	if (try_num == 5)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "/|\\     |" << endl;
		cout << "\t" << "/       |" << endl;
	}
	if (try_num == 6)
	{
		cout << "\t" << " ________" << endl;
		cout << "\t" << " |      |" << endl;
		cout << "\t" << " O      |" << endl;
		cout << "\t" << "/|\\     |" << endl;
		cout << "\t" << "/ \\     |" << endl;
	}
}

string random_element(vector<string> v)
{
	default_random_engine dre(time(NULL));
	uniform_int_distribution<int> uid(0, v.size() - 1);
	int index = uid(dre);
	return v[index];
}

bool game(vector<string> v)
{
	string word = random_element(v);
	string asteriks;
	for (int i = 0; i < word.size(); i++)
	{
		asteriks.push_back('*');
	}
	int try_num = 0;
	print(try_num);
	cout << "\n\n" << asteriks << "\n\n";
	while (try_num < max_tries)
	{
		if (word == asteriks)
		{
			return true;
		}
		char c;
		string s;
		cout << "\n\nGuess a letter: ";
		cin >> s;
		c = s[0];
		if ((c <= 'A'&& c >= 'Z') && (c <= 'a'&& c >= 'z'))
		{
			continue;
		}
		int temp = 0;
		for (int index = 0; index < word.size(); index++)
		{
			if (word[index] == c)
			{
				asteriks[index] = c;
				temp++;
			}
		}
		if (temp == 0)
		{
			try_num++;
		}
		system("cls");
		print(try_num);
		cout << "\n\n" << asteriks << "\n\n";
		if (temp != 0)
		{
			if (temp == 1)
				cout << "Nice job! You guessed " << temp << " letter!";
			else
				cout << "Nice job! You guessed " << temp << " letters!";
		}
		else
		{
			cout << "There are no such letters!";
		}
	}
	return false;
}

int main()
{
	vector<string> easy = { "film","zoo","calm","doll","jazz","junk" };
	vector<string> medium = { "garage","scared","shallow","species" };
	vector<string> hard = { "zigzagging","occasionally","independent","university" };
	string difficulty;
	cout << "What difficulty do you want? (easy,medium,hard)" << endl;
	cin >> difficulty;
	if (difficulty == "easy")
	{
		if (game(easy))
		{
			cout << "\n\nYou win!\n\n";
			system("pause");
			return 0;
		}
		else
		{
			system("cls");
			print(6);
			cout << "\n\n\n\n";
			cout << "\nYou lost!\n\n";
			system("pause");
			return 0;
		}
	}
	if (difficulty == "medium")
	{
		if (game(medium))
		{
			cout << "\n\nYou win!\n\n";
			system("pause");
			return 0;
		}
		else
		{
			system("cls");
			print(6);
			cout << "\n\n\n\n";
			cout << "\nYou lost!\n\n";
			system("pause");
			return 0;
		}
	}
	if (difficulty == "hard")
	{
		if (game(hard))
		{
			cout << "\n\nYou win!\n\n";
			system("pause");
			return 0;
		}
		else
		{
			system("cls");
			print(6);
			cout << "\n\n\n\n";
			cout << "\nYou lost!\n\n";
			system("pause");
			return 0;
		}
	}
	else
	{
		cout << "\n\nWrite either easy, medium or hard.\n\n";
		system("pause");
	}
}