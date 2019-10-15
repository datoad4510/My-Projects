#include<iostream>
#include<cassert>
#include<vector>
#include<queue>
#include<random>
#include<ctime>
using namespace std;//minmax: is potlebi romlebsac igive mshobeli yavt chasvi calke masivebshi. BFS gamoiyene bolo donidan pirvel donemde.

//easy: random moves
//medium: perfect, but  makes 1 or 2 mistakes and then prolongs the game as much as possible (harder to implement, subtract depth)
//hard: perfect minmax

char player = 'X';//may change
char npc = 'O';

struct Board
{
	int win_state = 2;//2 means that the game continues
	char arr[3][3] = {
		{-1,-1,-1},
		{-1,-1,-1},
		{-1,-1,-1}
	};
	bool operator==(Board b)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (arr[i][j] != b.getVal(i, j))
					return 0;
			}
		}
		return 1;
	}
	char getVal(int i, int j)
	{
		assert(0 <= i && i <= 2 && 0 <= j && j <= 2);
		return arr[i][j];
	}
	void setVal(int i, int j, char val)
	{
		assert(0 <= i && i <= 2 && 0 <= j && j <= 2);
		arr[i][j] = val;
	}
	void draw()
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (arr[i][j] == -1)
				{
					cout << "-  ";
					if (j == 2)
						cout << "\n\n";
					continue;
				}
				cout << arr[i][j] << "  ";
				if (j == 2)
					cout << "\n\n";
			}
		}
	}
	void operator=(const Board& brd)
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				arr[i][j] = brd.arr[i][j];
			}
		}
		win_state = brd.win_state;
	}
};

struct node
{
	Board brd;
	int score = -100;//for minmax
	vector<node*> children;
	node* parent = nullptr;
};

short check_win(Board b)// -1 = x win, 0 = tie, 1 = O win, 2 = nothing
{
	for (int i = 0; i < 3; ++i)//horizontal lines
	{
		if (b.getVal(i, 0) == 'X' && b.getVal(i, 0) == b.getVal(i, 1) && b.getVal(i, 1) == b.getVal(i, 2))
		{
			return -1;
		}
		if (b.getVal(i, 0) == 'O' && b.getVal(i, 0) == b.getVal(i, 1) && b.getVal(i, 1) == b.getVal(i, 2))
		{
			return 1;
		}
	}
	for (int j = 0; j < 3; ++j)//vertical lines
	{
		if (b.getVal(0, j) == 'X' && b.getVal(0, j) == b.getVal(1, j) && b.getVal(1, j) == b.getVal(2, j))
		{
			return -1;
		}
		if (b.getVal(0, j) == 'O' && b.getVal(0, j) == b.getVal(1, j) && b.getVal(1, j) == b.getVal(2, j))
		{
			return 1;
		}
	}

	// \ diagonals
	if (b.getVal(0, 0) == 'X' && b.getVal(0, 0) == b.getVal(1, 1) && b.getVal(1, 1) == b.getVal(2, 2))
	{
		return -1;
	}
	if (b.getVal(0, 0) == 'O' && b.getVal(0, 0) == b.getVal(1, 1) && b.getVal(1, 1) == b.getVal(2, 2))
	{
		return 1;
	}

	// / diagonals
	if (b.getVal(0, 2) == 'X' && b.getVal(0, 2) == b.getVal(1, 1) && b.getVal(1, 1) == b.getVal(2, 0))
	{
		return -1;
	}
	if (b.getVal(0, 2) == 'O' && b.getVal(0, 2) == b.getVal(1, 1) && b.getVal(1, 1) == b.getVal(2, 0))
	{
		return 1;
	}

	//if it's full, it's a tie
	bool is_emptyslot = 0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (b.getVal(i, j) == -1)
			{
				is_emptyslot = 1;
				break;
			}
		}
		if (is_emptyslot == 1)
			break;
	}
	if (is_emptyslot == 0)
		return 0;

	return 2;//if none of these happen, just continue
}

void fill_children(node* ptr, bool XO)
{
	if (XO == 0)//O's turn
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if ((ptr->brd).getVal(i, j) == -1)
				{
					node* newnode = new node;
					newnode->brd = ptr->brd;
					(newnode->brd).setVal(i, j, 'O');
					(newnode->brd).win_state = check_win(newnode->brd);
					newnode->parent = ptr;
					(ptr->children).push_back(newnode);

				}
			}
		}
	}
	else//X's turn
	{
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if ((ptr->brd).getVal(i, j) == -1)
				{
					node* newnode = new node;
					newnode->brd = ptr->brd;
					(newnode->brd).setVal(i, j, 'X');
					(newnode->brd).win_state = check_win(newnode->brd);
					newnode->parent = ptr;
					(ptr->children).push_back(newnode);
				}
			}
		}
	}
}

void create_tree(node* rootptr, bool XO)//create a decision tree. XO = 0 -> it's O's turn. else it's X's turn
{
	short checkwin = check_win(rootptr->brd);
	//cout << checkwin;
	if (checkwin == 2)
	{
		fill_children(rootptr, XO);
		for (int i = 0; i < (rootptr->children).size(); ++i)
		{
			create_tree((rootptr->children)[i], !XO);// !XO is the next player
		}
	}
	else
		return;//the game has ended
}

void delete_tree(node* rootptr)//using postorder walk delete all the nodes in an m-ary tree
{
	for (int i = 0; i < (rootptr->children).size(); ++i)
	{
		delete_tree((rootptr->children)[i]);
	}
	delete rootptr;
}


int height(node* node)
{
	if ((node->children).size() == 0)
	{
		return 0;
	}
	else
	{
		/* compute the height of each subtree */
		vector<int> child_heights;
		for (int i = 0; i < (node->children).size(); ++i)
		{
			child_heights.push_back(height(node->children[i]));
		}

		/* use the largest one */
		int maximum = child_heights[0];
		for (int i = 1; i < child_heights.size(); ++i)
		{
			if (child_heights[i] > maximum)
				maximum = child_heights[i];
		}
		return maximum + 1;
	}
}

void reverseLevelOrder(node* root)//can be optimised for space. has the whole tree in memory at once copied. maybe keep a set of parent nodes? (might be a bit slower)
{
	vector<vector<node*>>  nodes;
	queue<node*> Q1;
	queue<node*> Q2;

	queue<node*>* ptr1 = &Q1;
	queue<node*>* ptr2 = &Q2;

	ptr1->push(root);
	vector<node*> temp = { root };
	nodes.push_back(temp);
	while (true)//ptr1 has the current level, ptr2 has the next level
	{
		vector<node*> v;
		while (ptr1->size() != 0)
		{
			for (int i = 0; i < ptr1->front()->children.size(); ++i)
			{
				ptr2->push(ptr1->front()->children[i]);
				v.push_back(ptr1->front()->children[i]);
			}
			ptr1->pop();
		}
		if (ptr2->size() == 0)
			break;
		nodes.push_back(v);
		swap(ptr1, ptr2);
	}


	for (int i = 0; i < nodes[nodes.size() - 1].size(); ++i)//we could actually maximise tieing or losing. other ai ideas?
	{	//winstate can't be 2, otherwise the tree would continue
		if (nodes[nodes.size() - 1][i]->brd.win_state == -1 && npc == 'X' || nodes[nodes.size() - 1][i]->brd.win_state == 1 && npc == 'O')
		{
			nodes[nodes.size() - 1][i]->score = 1;//npc wins
		}
		if (nodes[nodes.size() - 1][i]->brd.win_state == -1 && npc == 'O' || nodes[nodes.size() - 1][i]->brd.win_state == 1 && npc == 'X')
		{
			nodes[nodes.size() - 1][i]->score = -1;//npc loses
		}
		if (nodes[nodes.size() - 1][i]->brd.win_state == 0)
		{
			nodes[nodes.size() - 1][i]->score = 0;//tie
		}
	}

	int h = nodes.size() - 1;//will be 10 - 1 == 9
	bool maximising;
	if (npc == 'X')
	{
		maximising = h % 2;//1 if npc-s turn at the next to last level. therefore maximising. 0 otherwise, if 0 - minimising
	}
	else
	{
		maximising = (h + 1) % 2;
	}

	for (int i = nodes.size() - 2; i >= 0; --i)
	{
		for (int j = 0; j < nodes[i].size(); ++j)
		{
			if (maximising == 1)
			{
				if (nodes[i][j]->children.size() == 0)
				{
					if (nodes[i][j]->brd.win_state == -1 && npc == 'X' || nodes[i][j]->brd.win_state == 1 && npc == 'O')
					{
						nodes[i][j]->score = 1;//npc wins
					}
					if (nodes[i][j]->brd.win_state == -1 && npc == 'O' || nodes[i][j]->brd.win_state == 1 && npc == 'X')
					{
						nodes[i][j]->score = -1;//npc loses
					}
					if (nodes[i][j]->brd.win_state == 0)
					{
						nodes[i][j]->score = 0;//tie
					}
					//cout << "Board win state: " << nodes[i][j]->brd.win_state << " Score: " << nodes[i][j]->score << endl;
					continue;
				}
				node* max = nodes[i][j]->children[0];
				for (int k = 0; k < nodes[i][j]->children.size(); ++k)
				{
					if (nodes[i][j]->children[k]->score > max->score)
						max = nodes[i][j]->children[k];
				}
				//cout << "Max score of children: " << max->score << endl;
				nodes[i][j]->score = max->score;
			}
			else
			{
				if (nodes[i][j]->children.size() == 0)
				{
					if (nodes[i][j]->brd.win_state == -1 && npc == 'X' || nodes[i][j]->brd.win_state == 1 && npc == 'O')
					{
						nodes[i][j]->score = 1;//npc wins
					}
					if (nodes[i][j]->brd.win_state == -1 && npc == 'O' || nodes[i][j]->brd.win_state == 1 && npc == 'X')
					{
						nodes[i][j]->score = -1;//npc loses
					}
					if (nodes[i][j]->brd.win_state == 0)
					{
						nodes[i][j]->score = 0;//tie
					}
					//cout << "Board win state: " << nodes[i][j]->brd.win_state << " Score: " << nodes[i][j]->score << endl;
					continue;
				}
				node* min = nodes[i][j]->children[0];
				for (int k = 0; k < nodes[i][j]->children.size(); ++k)
				{
					if (nodes[i][j]->children[k]->score < min->score)
						min = nodes[i][j]->children[k];
				}
				//cout << "Min score of children: " << min->score << endl;
				nodes[i][j]->score = min->score;
			}
		}
		maximising = !maximising;
	}
}


node* bestMove(node* root)//returns the node that maximises the score.
{
	assert(root->children.size() != 0);
	if (root->children.size() == 0)//tu shvilebi ar yavs, anu tamashi agar grdzeldeba(redundant)
	{
		return nullptr;
	}
	vector<node*> optimal_children;
	for (int i = 0; i < (root->children).size(); ++i)//sheecade moigo
	{
		if ((root->children)[i]->score == 1)
			optimal_children.push_back((root->children)[i]);
	}
	if (optimal_children.size() == 0)//tu ver igeb, fre mainc iyos
	{
		for (int i = 0; i < (root->children).size(); ++i)
		{
			if ((root->children)[i]->score == 0)
				optimal_children.push_back((root->children)[i]);
		}
	}
	if (optimal_children.size() == 0)//tu frec ara, mokvdi sainteresod
	{
		for (int i = 0; i < (root->children).size(); ++i)
		{
			if ((root->children)[i]->score == -1)
				optimal_children.push_back((root->children)[i]);
		}
	}


	cout << "\n\nScores of children: ";
	for (int i = 0; i < (root->children).size(); ++i)
	{
		cout << root->children[i]->score << " ";
	}
	cout << "\n\n";


	default_random_engine dre(time(NULL));
	assert(optimal_children.size() > 0);
	uniform_int_distribution<short> uid(0, optimal_children.size() - 1);
	return optimal_children[uid(dre)];
}

void cpuvscpu()//basically the same as random moves
{
	system("cls");
	node* n = new node;
	player = 'X';
	npc = 'O';
	create_tree(n, 1);
	cout << "Height of the decision tree: " << height(n) << "\n\n";
	int i = 0;
	default_random_engine dre(time(NULL));
	(n->brd).draw();
	cout << "\n\n";
	while ((n->brd).win_state == 2)
	{
		cout << "Number of possible game developments == " << (n->children).size() << endl;
		++i;
		assert((n->children).size() > 0);
		uniform_int_distribution<int> uid(0, (n->children).size() - 1);
		int temp = uid(dre);
		if (temp == 1)
			cout << "Choosing the " << temp << "-st one.\n\n\n";
		if (temp == 2)
			cout << "Choosing the " << temp << "-nd one.\n\n\n";
		if (temp == 3)
			cout << "Choosing the " << temp << "-rd one.\n\n\n";
		if (temp > 3 || temp == 0) 
			cout << "Choosing the " << temp << "-th one.\n\n\n";
		n = (n->children)[temp];
		(n->brd).draw();
		cout << "\n\n\n";
	}
	delete n;
	system("pause");
}


void playervscpu_optimal(char player)
{
	system("cls");
	assert((player == 'X' || player == 'O') && (npc == 'X' || npc == 'O'));
	node* n = new node;//use this for tree deletion
	node* traversing = n;//use this for traversing
	create_tree(n, 1);
	reverseLevelOrder(n);
	bool iscputurn;
	if (npc == 'X')
		iscputurn = true;
	else
		iscputurn = false;
	system("cls");
	traversing->brd.draw();
	while (traversing->brd.win_state == 2)
	{
		if (iscputurn)
		{
			iscputurn = !iscputurn;
			traversing = bestMove(traversing);
			system("cls");
			traversing->brd.draw();
		}
		else
		{
			iscputurn = !iscputurn;
			int row = -1;
			int column = -1;
			Board b = traversing->brd;
			while (true)
			{
				cout << "\n\n\nWhere do you want to put an " << player << " ?\n\n";
				cout << "Row: ";
				cin >> row;
				cout << "\n\nColumn: ";
				cin >> column;
				if (row < 1 || 3 < row || column < 1 || 3 < column || (b.getVal(row - 1, column - 1) != -1))
				{
					system("cls");
					b.draw();
					continue;
				}
				break;
			}
			b.setVal(row - 1, column - 1, player);
			for (int i = 0; i < traversing->children.size(); ++i)
			{
				if (traversing->children[i]->brd == b)
				{
					traversing = traversing->children[i];
					break;
				}
			}
			system("cls");
			traversing->brd.draw();
		}


	}
	if (traversing->brd.win_state == -1 && npc == 'X' || traversing->brd.win_state == 1 && npc == 'O')
	{
		cout << "You lose!" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (traversing->brd.win_state == -1 && npc == 'O' || traversing->brd.win_state == 1 && npc == 'X')
	{
		cout << "How the hell did you win?!" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (traversing->brd.win_state == 0)
	{
		cout << "It's a tie!" << endl;
		system("pause");
		system("cls");
		return;
	}
	delete_tree(n);
}

void playervscpu(char player, int x)
{
	if (x == 100)
	{
		playervscpu_optimal(player);
		return;
	}
	system("cls");
	assert((player == 'X' || player == 'O') && (npc == 'X' || npc == 'O'));
	node* n = new node;//use this for tree deletion
	node* traversing = n;//use this for traversing
	create_tree(n, 1);
	reverseLevelOrder(n);
	bool iscputurn;
	if (npc == 'X')
		iscputurn = true;
	else
		iscputurn = false;
	system("cls");
	traversing->brd.draw();
	while (traversing->brd.win_state == 2)
	{
		if (iscputurn)
		{
			iscputurn = !iscputurn;

			default_random_engine dre(time(NULL));
			uniform_int_distribution<short> uid(1, 100);
			if (uid(dre) < x)
			{
				traversing = bestMove(traversing);
				system("cls");
				traversing->brd.draw();
			}
			else
			{
				uniform_int_distribution<short> uid1(0, 2);
				Board b = traversing->brd;
				while (true)
				{
					int x = uid1(dre);
					int y = uid1(dre);
					if (b.getVal(x, y) == -1)
					{
						b.setVal(uid1(dre), uid1(dre), npc);
						vector<node*> v = traversing->children;
						for (auto& m : v)
						{
							if (m->brd == b)
							{
								traversing = m;
								break;
							}
						}
						break;
					}
					else
						continue;
				}
				system("cls");
				traversing->brd.draw();
			}
		}
		else
		{
			iscputurn = !iscputurn;
			int row = -1;
			int column = -1;
			Board b = traversing->brd;
			while (true)
			{
				cout << "\n\n\nWhere do you want to put an " << player << " ?\n\n";
				cout << "Row: ";
				cin >> row;
				cout << "\n\nColumn: ";
				cin >> column;
				if (row < 1 || 3 < row || column < 1 || 3 < column || (b.getVal(row - 1, column - 1) != -1))
				{
					system("cls");
					b.draw();
					continue;
				}
				break;
			}
			b.setVal(row - 1, column - 1, player);
			for (int i = 0; i < traversing->children.size(); ++i)
			{
				if (traversing->children[i]->brd == b)
				{
					traversing = traversing->children[i];
					break;
				}
			}
			system("cls");
			traversing->brd.draw();
		}


	}
	if (traversing->brd.win_state == -1 && npc == 'X' || traversing->brd.win_state == 1 && npc == 'O')
	{
		cout << "You lose!" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (traversing->brd.win_state == -1 && npc == 'O' || traversing->brd.win_state == 1 && npc == 'X')
	{
		cout << "You win!" << endl;
		system("pause");
		system("cls");
		return;
	}
	if (traversing->brd.win_state == 0)
	{
		cout << "It's a tie!" << endl;
		system("pause");
		system("cls");
		return;
	}
	delete_tree(n);
}

void playervsplayer()
{
	system("cls");
	bool turn = 0;//0 == x, 1 == o
	Board b;
	b.draw();

	int row;
	int column;
	while (check_win(b) == 2)
	{
		if (turn == 0)
		{
			
			cout << "\n\n\nWhere do you want to put an 'X' ?\n\n";
			cout << "Row: ";
			cin >> row;
			cout << "\n\nColumn: ";
			cin >> column;
			if (1 <= row && row <= 3 && 1 <= column && column <= 3 && (b.getVal(row - 1, column - 1) == -1))
			{
				b.setVal(row - 1, column - 1, 'X');
				system("cls");
				b.draw();
				turn = !turn;
			}
			system("cls");
			b.draw();
		}
		else
		{
			cout << "\n\n\nWhere do you want to put an 'O' ?\n\n";
			cout << "Row: ";
			cin >> row;
			cout << "\n\nColumn: ";
			cin >> column;
			if (1 <= row && row <= 3 && 1 <= column && column <= 3 && (b.getVal(row - 1, column - 1) == -1))
			{
				b.setVal(row - 1, column - 1, 'O');
				system("cls");
				b.draw();
				turn = !turn;
			}
			system("cls");
			b.draw();
		}
	}
	int winstate = check_win(b);
	if (winstate == -1)
	{
		cout << "\n\n'X' wins!\n\n";
	}
	else if (winstate == 0)
	{
		cout << "\n\nIt's a tie!\n\n";
	}
	else
	{
		cout << "\n\n'O' wins!\n\n";
	}
	system("pause");
	return;
}

int main()//fill_children ,draw , create_tree and height work correctly. !!reverse traversal doesn't score evweything!!
{
	while (true)
	{
		cout << "1. Player versus player\n\n";
		cout << "2. Player versus CPU\n\n";
		cout << "3. CPU versus CPU (test)\n\n";
		cout << "Choose a mode:\n\n";
		int mode;
		cin >> mode;
		if (mode == 1)
		{
			playervsplayer();
		}
		if (mode == 2)
		{
			system("cls");
			char c;
			cout << "Do you want to be X or O ?\n\n";
			cin >> c;
			if (c == 'X' || c == 'x')
			{
				player = 'X';
				npc = 'O';
			}
			else if (c == 'O' || c == 'o')
			{
				player = 'O';
				npc = 'X';
			}
			else
			{
				system("cls");
				continue;
			}
			system("cls");
			short diff;
			cout << "What difficulty do you want? Input a number between 1 and 100 (Higher is harder. 1 is almost random, 100 is impossible)\n\n";
			cin >> diff;
			if (!(1 <= diff && diff <= 100))
			{
				system("cls");
				continue;
			}
			playervscpu(player, diff);
		}
		if (mode == 3)
		{
			cpuvscpu();
		}
		system("cls");
		continue;
	}
}

//ai modes: medium: plays optimally but makes mistakes (random moves sometimes)
//random: self explanatory
//wants to tie: two types: tie or win and tie or lose
//wants to lose or tie (easy)
//wants to lose or win (doesnt want to tie)

