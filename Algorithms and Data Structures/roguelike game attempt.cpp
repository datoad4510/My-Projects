#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>
using namespace std;

class Map
{
	vector<vector<char>> v;
	int length = 0;//columns
	int height = 0;//rows
	int x1_showing;
	int y1_showing;
	int x2_showing;
	int y2_showing;
	int x_player; //x1 + x2/2
	int y_player;//y1 + y2/2
public:
	Map(){}
	~Map(){}
	Map(int l, int h)
	{
		length = l;
		height = h;
		vector<char> temp;
		for (int i = 0; i < height; i++)
		{
			v.push_back(temp);
			for (int j = 0; j < length; j++)
			{
				v[i].push_back(' ');
			}
		}
	}
	void show()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << v[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
	void load(istream& is)
	{
		char temp;
		int i = 0;
		int j = 0;
		while (is >> noskipws >> temp)
		{
			v[j][i] = temp;
			++i;
			if (i == length)
			{
				i = 0;
				++j;
			}
			if (j == height)
				break;
		}
	}
	void north()
	{
		++y1_showing;
		++y2_showing;
		system("cls");
		Map::show();
	}
	void south()
	{
		--y1_showing;
		--y2_showing;
		system("cls");
		Map::show();
	}
	void west()
	{
		--x1_showing;
		--x2_showing;
		system("cls");
		Map::show();
	}
	void east()
	{
		++x1_showing;
		++x2_showing;
		system("cls");
		Map::show();
	}
};

int main()
{
	string input;
	Map start(20, 10);
	ifstream ifs("map.txt");
	start.load(ifs);
	start.show();//show ragac nawili

	while (cin >> input)
	{
		if (input == "n")
		{
			start.north();
			continue;
		}
		if (input == "s")
		{
			start.south();
			continue;
		}
		if (input == "w")
		{
			start.west();
			continue;
		}
		if (input == "e")
		{
			start.east();
			continue;
		}
		if (input == "exit")
			return 0;
		/*
		if (input == "save")
		{
			menu.save(); //prints the save menu
			cout << "Which slot? ";
			short n;
			cin >> n;
			assert(1 <= n && n <= 5);
			save("savefile", n);//saves to savefile in the n-th slot
			continue;
		}
		*/
		else
		{
			cout << "Type 'help' to see available commands.";
			system("cls");
			start.show();
		}
	}
}


/*
####################
#                  #
#				   #
#				   #
#				   #
#				   #
#				   #
#				   #
#				   #
####################
*/