#include<iostream>
#include<cassert>
#include<vector>
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

void ScoreGivenLevel(node* root, int level, bool maxmin)// maxmin == 1 means it's the CPU's turn(maxmimising). maxmin == 0 means it's the player's turn
{//maxmin -> whose turn it is on level 1
	if (level == 1 && (root->children.size()) == 0)//we are considering a leaf. this is not a part of minimax, these are initial values
	{
		int state = (root->brd).win_state;//-1 == x win, 0 == tie, 1 == o win, 2 == nothing
		//assert(state == 1 || state == -1 || state == 0);
		if ((state == -1 && npc == 'X') || (state == 1 && npc == 'O'))
			root->score = 1;
		else if ((state == -1 && npc == 'O') || (state == 1 && npc == 'X'))
			root->score = -1;
		else if (state == 0)
			root->score = 0;
		return;//only one node in tree
	}
	else if (level == 1 && (root->children.size()) != 0 && maxmin == 1)
	{
		node* max = (root->children)[0];
		for (int i = 1; i < (root->children).size(); ++i)
		{
			if ((root->children)[i]->score > max->score)
				max = (root->children)[i];
		}
		root->score = max->score;
	}
	else if (level == 1 && (root->children.size()) != 0 && maxmin == 0)
	{
		node* min = (root->children)[0];
		for (int i = 1; i < (root->children).size(); ++i)
		{
			if ((root->children)[i]->score < min->score)
				min = (root->children)[i];
		}
		root->score = min->score;
	}
	else if (level > 1)
	{
		for (int i = 0; i < (root->children).size(); ++i)
		{
			ScoreGivenLevel((root->children)[i], level - 1, !maxmin);
		}
	}
}

void reverseLevelOrder(node* root)//doesn't score all children!
{
	int h = height(root);
	//bool who = (h + 1) % 2;//whose turn it is during the last level: 0 means 'O', 1 means 'X'
	//bool maxmin;//is the final turn player's turn or cpu's?
	//if (who == player)
	//	maxmin = 0;//player's
	//else
	//	maxmin = 1;//cpu's
	bool maxmin;
	if (player == 'X')
		maxmin = 0;//first  turn is player's (at level 1)
	else
		maxmin = 1;//first  turn is cpu's (at level 1)
	int i;
	for (i = h; i >= 1; i--) //reverse level order traversal
	{
		ScoreGivenLevel(root, i, maxmin);
		maxmin = !maxmin;
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
	if (optimal_children.size() == 0)//tu frec ara, mokvdi sainteresods
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
		cout << "Choosing the " << temp << "-th one.\n\n\n";
		n = (n->children)[temp];
		(n->brd).draw();
		cout << "\n\n\n";
	}
	delete n;
	system("pause");
}

void playervscpu(char player)
{
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
		system("cls");
		cout << "You lose!" << endl;
		system("pause");
		return;
	}
	if (traversing->brd.win_state == -1 && npc == 'O' || traversing->brd.win_state == 1 && npc == 'X')
	{
		system("cls");
		cout << "How the hell did you win?!" << endl;
		system("pause");
		return;
	}
	if (traversing->brd.win_state == 0)
	{
		system("cls");
		cout << "It's a tie!" << endl;
		system("pause");
		return;
	}
	delete_tree(n);
}

void playervsplayer()
{
	bool turn = 0;//0 == player 1 (player), 1 == player 2 (npc)
	Board b;
	b.draw();
	while (check_win(b) == 2)
	{
		if (turn == 0)
		{
			int row;
			int column;
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
		}
	}
	return;
}


int main()//fill_children ,draw , create_tree and height work correctly. !!reverse traversal doesn't score evweything!!
{
	playervscpu(player);
}

/*
cout << "Do you want to be 'X' or 'O'? " << endl;
	char temp;
	cin >> temp;
	assert(temp == 'X' || temp == 'O');
	player = temp;
	if (player == 'X')
		npc = 'O';
	else
		npc = 'X';


	node* n = new node;
	create_tree(n, 1);
	node* traversing = n;
	bool turn = 0; //0 if npc, 1 if player
	if (npc == 'X')
		turn == 0;
	else
		turn == 1;
	while (true)
	{
		system("cls");
		traversing->brd.draw();
		if (turn == 0)
		{
			traversing = bestMove(traversing);
			turn = !turn;
			cout << "\n\n\n\n";
			continue;
		}
		else
		{
			int i;
			int j;
			cout << "Please enter valid indices of the place you want to fill:\n\n";
			cout << "Row: ";
			cin >> i;
			cout << "\n\nColumn: ";
			cin >> j;
			cout << "\n\n";
			//if ((traversing->brd).getVal(i, j) != -1) && 1 <= i && i <= 3 && 1 <= j && j <= 3)
			//{
			//    cout << "Invalid move! Try again.";
			//    continue;
			//}
			Board temp = traversing->brd;
			temp.setVal(i - 1, j - 1, player);
			for (int i = 0; i < (traversing->children).size(); ++i)
			{
				if (((traversing->children)[i])->brd == temp)
				{
					traversing->brd = temp;
					turn = !turn;
					cout << "\n\n\n\n";
					continue;
				}
			}
		}
	}
	delete_tree(n);
*/