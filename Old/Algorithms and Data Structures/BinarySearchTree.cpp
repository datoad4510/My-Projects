#include<memory>
#include<iostream>
#include<queue>
using namespace std;


typedef struct tree_node* link;

struct tree_node
{
	link left;
	link right;
	link p;
	int data;
	tree_node() {}
	tree_node(int k)
	{
		data = k;
		left = right = p = nullptr;
	}
};
class BinarySearchTree
{
private:
	link root;
	int size;
	void inorder(link, void vf(link)) noexcept;
	void preorder(link, void vf(link)) noexcept;
	void postorder(link, void vf(link)) noexcept;
	void outorder(link, void vf(link)) noexcept;
	void levelorder(link, void vf(link)) noexcept;
	link successor(link) noexcept;
	link predecessor(link) noexcept;
	link minimum(link) noexcept;
	link maximum(link) noexcept;
	int height(link) noexcept;
	//void delete(link) noexcept;
	//select da rank ordered tree-tvisaa marto
public:
	//operator= konteinerebze
	BinarySearchTree() : root(nullptr), size(0) {}
	~BinarySearchTree();

	template<typename InputIterator>
	void fill(InputIterator, InputIterator) noexcept;

	link tree_root() noexcept { return root; }//ar daarqva igive saxeli vels da metods... ar imushavebs.
	int tree_size() noexcept { return size; }
	bool isEmpty() const noexcept { return root == nullptr; }
	void print_preorder() noexcept;
	void print_inorder() noexcept;
	void print_postorder() noexcept;
	void print_outorder() noexcept;
	void print_levelorder() noexcept;
	link search(int k) noexcept;
	void insert(int) noexcept;
	void succprint() noexcept;
	void predprint() noexcept;
	int treemin() noexcept;
	int treemax() noexcept;
	int treeheight() noexcept;
};

int BinarySearchTree::height(link x) noexcept
{
	if (x == nullptr) return -1;
	int u = height(x->left);
	int v = height(x->right);
	return (u < v) ? (v + 1) : (u + 1);
}

int BinarySearchTree::treeheight() noexcept
{
	return height(root);
}

template<typename InputIterator>
void BinarySearchTree::fill(InputIterator first, InputIterator last) noexcept
{
	while (first != last)
	{
		(*this).insert(*first);
		++first;
	}
}

void BinarySearchTree::insert(int d) noexcept
{
	++size;
	//create new node with key = d
	link t = new tree_node(d);
	link y = nullptr;
	link x = root;
	// Find the Node's parent
	while (nullptr != x)
	{
		y = x;
		if (t->data > x->data) x = x->right;
		else x = x->left;
	}
	t->p = y;
	if (nullptr == y)
	{
		root = t;
		return;
	}
	if (d < y->data)
		y->left = t;
	else
		y->right = t;
}

void BinarySearchTree::print_inorder() noexcept
{
	inorder(root, [](tree_node* p) {std::cout << " " << p->data << " "; });
}

void BinarySearchTree::print_preorder() noexcept
{
	preorder(root, [](tree_node* p) {std::cout << " " << p->data << " "; });
}

void BinarySearchTree::print_postorder() noexcept
{
	postorder(root, [](tree_node* p) {std::cout << " " << p->data << " "; });
}

void BinarySearchTree::print_outorder() noexcept
{
	outorder(root, [](tree_node* p) {std::cout << " " << p->data << " "; });
}

void BinarySearchTree::print_levelorder() noexcept
{
	levelorder(root, [](tree_node* p) {std::cout << " " << p->data << " "; });
}

BinarySearchTree::~BinarySearchTree()
{
	inorder(root, [](link p) { delete p; });
	root = nullptr;
	size = 0;
}
void BinarySearchTree::inorder(link p, void vf(link)) noexcept
{
	if (p != nullptr)
	{
		inorder(p->left, vf);	  //memgoni mugami isaa, rom vf(p) rom ar cvlides xis topologias ra tanmimdevrobitac shesruldeboda (vtqvat print_inorder), im tanmimdevrobit unda damushavdes yoveltvis
		tree_node* tmp(p->right);//ristvisaa? vf(p) sheileba shvilebi shecvalos? vtqvat marto marcxena qvexis da marjvena shvilis shecvla sheudzlia vf(p)-s, mashin gasagebia ristvisacaa.
		vf(p);					//sxva marjvenebis shecvlac rom sheedzlos, magati damaxsovrebac dagvchirdeboda rogorme... saertod memgoni marto marcxena da marjvena shvilis shecvlis ufleba unda qones.
		inorder(tmp, vf);	   //marto *p-s unda vcvlidet? mis mshoblebs cxadia ar unda vcvlidet, imitoro inorder(p->left, vf)-m sheidzleba p-c shecvalos da masin ar imushavebs kodi.
	}
}

void BinarySearchTree::preorder(link p, void vf(link)) noexcept
{
	if (p != nullptr)
	{
		//tree_node* tmp1(p->left);//wina principit, vf(p)-m mxolod sheidzleba misi marcxena da marjvena shvili shecvalos
		//tree_node* tmp2(p->right);
		vf(p);
		preorder(p->left, vf);
		preorder(p->right, vf);
	}
}

void BinarySearchTree::postorder(link p, void vf(link)) noexcept
{
	if (p != nullptr)
	{
		//tree_node* tmp(p);
		postorder(p->left, vf);
		postorder(p->right, vf);
		vf(p);
	}
}

void BinarySearchTree::outorder(link p, void vf(link)) noexcept
{
	if (p != nullptr)
	{
		//tree_node* tmp(p);
		outorder(p->right, vf);
		vf(p);
		outorder(p->left, vf);
	}
}

void BinarySearchTree::levelorder(link p, void vf(link)) noexcept
{
	queue<link> q;
	q.push(p);
	link current = nullptr;
	while (!q.empty())
	{
		current = q.front();
		q.pop();
		vf(current);

		if (current->left != nullptr)
			q.push(current->left);
		if (current->right != nullptr)
			q.push(current->right);

	}
}

link BinarySearchTree::search(int k) noexcept
{
	link x = root;
	while (nullptr != x && x->data != k)
	{
		if (k < x->data)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}

link BinarySearchTree::minimum(link x) noexcept
{
	while (x->left != nullptr) {
		x = x->left;
	}
	return x;
}

int BinarySearchTree::treemin() noexcept
{
	return minimum(root)->data;
}

link BinarySearchTree::maximum(link x) noexcept
{
	while (x->right != nullptr) {
		x = x->right;
	}
	return x;
}

int BinarySearchTree::treemax() noexcept
{
	return maximum(root)->data;
}

link BinarySearchTree::successor(link x) noexcept
{
	if (nullptr != x->right) return minimum(x->right);
	while (nullptr != x->p && x == (x->p)->right)
	{
		x = x->p;
	}
	return x->p;
}

link BinarySearchTree::predecessor(link x) noexcept
{
	if (nullptr != x->left) return maximum(x->left);
	while (nullptr != x->p && x == (x->p)->left)
	{
		x = x->p;
	}
	return x->p;
}

void BinarySearchTree::succprint() noexcept
{
	link x = minimum(root);
	while (nullptr != x)
	{
		cout << " " << x->data << " ";
		x = successor(x);
	}
}

void BinarySearchTree::predprint() noexcept
{
	link x = maximum(root);
	while (nullptr != x)
	{
		cout << " " << x->data << " ";
		x = predecessor(x);
	}
}


int main()
{
	BinarySearchTree b;
	int ch, tmp, tmp1;
	link node_address;

	vector<int> v = { 23,5,11,97,18,-27,15,1,33,5,18,33,11 };
	b.fill(v.begin(), v.end());
	while (1)
	{
		cout << endl << endl;
		cout << " Binary Search Tree Operations " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insertion/Creation " << endl;
		cout << " 2. Minimum " << endl;
		cout << " 3. Maximum " << endl;
		cout << " 4. Pre-Order Traversal " << endl;
		cout << " 5. In-Order Traversal " << endl;
		cout << " 6. Post-Order Traversal " << endl;
		cout << " 7. Level-Order Traversal " << endl;
		cout << " 8. Out-Order Traversal " << endl;
		cout << " 9. Ordered print using successor " << endl;
		cout << " 10. Reversed print using predecessor " << endl;
		cout << " 11. search " << endl;
		cout << " 12. Height " << endl;
		cout << " 13. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << " Enter Number to be inserted : ";
			cin >> tmp;
			b.insert(tmp);
			break;
		case 2:
			cout << endl;
			cout << " Minimum = " << b.treemin() << endl;
			break;
		case 3:
			cout << endl;
			cout << " Maximum = " << b.treemax() << endl;
			break;
		case 4:
			cout << endl;
			cout << " Pre-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_preorder();
			break;
		case 5:
			cout << endl;
			cout << " In-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_inorder();
			break;
		case 6:
			cout << endl;
			cout << " Post-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_postorder();
			break;
		case 7:
			cout << endl;
			cout << " Level-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_levelorder();
			break;
		case 8:
			cout << endl;
			cout << " Out-Order Traversal " << endl;
			cout << " -------------------" << endl;
			b.print_outorder();
			break;
		case 9:
			cout << endl;
			cout << " Successor Print " << endl;
			cout << " -------------------" << endl;
			b.succprint();
			break;
		case 10:
			cout << endl;
			cout << " Predecessor Print " << endl;
			cout << " -------------------" << endl;
			b.predprint();
			break;
		case 11:
			cout << " Enter Number to be searched : ";
			cin >> tmp;
			node_address = b.search(tmp);
			if (node_address != nullptr)
				cout << "Found node with data " << tmp << endl;
			else
				cout << "Not found..." << endl;
			break;
		case 12:
			cout << " Height = " << b.treeheight() << endl;
			break;
		case 13:
			return 0;
			break;
		}
	}
}