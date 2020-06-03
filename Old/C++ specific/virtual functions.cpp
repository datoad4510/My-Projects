#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;


class Book
{
protected:
	int pages;
	double cost;
	string name;
public:
	virtual void print() = 0;
	virtual void input() = 0;
	virtual double get_cost() = 0;
	

	virtual void foutput(string str) = 0;
};

class Special : public Book
{
protected:
	double typo;
public:
	Special() {}
	Special(int p, double t, string n) { pages = p; typo = t; name = n; cost = p*t; } //list inicializeba ar sheileba aq.
	void print() { cout << "Name: " << name << " Pages: " << pages << " Cost: " << cost << endl; }
	void input() { cout << "Pages: "; cin >> pages; cout << "Typographic: "; cin >> typo; cout << " Name: "; cin >> name; cost = typo*pages; }
	double get_cost() { return cost; }



	void foutput(string str) { ofstream ofs(str); ofs << "Name: " << name << " Pages: " << pages << " Cost: " << cost << " SPECIAL " << endl; }
};

class Art : public Book
{
protected:
	double typo;
	double poly;
public:
	Art() {}
	Art(int p, double t, double po, string n) { pages = p; typo = t; poly = po; name = n; cost = (t + po)*p; } //list inicializeba ar sheileba aq.
	void print() { cout << "Name: " << name << " Pages: " << pages << " Cost: " << cost << endl; }
	void input() { cout << "Pages: "; cin >> pages; cout << " Typographic: "; cin >> typo; cout << " Polygraphic: "; cin >> poly;  cout << " Name: "; cin >> name; cost = (typo + poly)*pages; }
	double get_cost() { return cost; }

	void foutput(string str) { ofstream ofs(str); ofs << "Name: " << name << " Pages: " << pages << " Cost: " << cost << " ART " << endl; }
};


int file_input(string str, Book** b, int size);

void file_output(string str, Book** b, int true_size);

int main()
{
	//	Book** b = new Book*[15000];
	//	string str;
	//	int counter = 0;
	//	cout << "Input the type of the book: ";
	//	cin >> str;
	//	while (str != "exit")
	//	{
	//		if (str == "special")
	//		{
	//			b[counter] = new Special;
	//			b[counter]->input();
	//			counter++;
	//		}
	//		if (str == "art")
	//		{
	//			b[counter] = new Art;
	//			b[counter]->input();
	//			counter++;
	//		}
	//		cout << "Input the type of the book: ";
	//		cin >> str;
	//	}
	//	sort(b, b + counter, [](Book* x, Book* y) {return (x->get_cost() > y->get_cost()); });
	//	for (int i = 0; i < counter; i++)
	//	{
	//		b[i]->print();
	//	}
	//	for (int i = 0; i < 15000; i++)
	//		delete[] b[i];
	//	delete[] b;


	cout << "\n\n\nSecond part of testing will now commence.";
	const int size = 15000;
	Book* a[size];
	int true_size = file_input("books.info", a, size);
	file_output("cost_decrease.out", a, true_size);


	system("pause");
}



int file_input(string str, Book** b, int size)
{
	ifstream ifs(str);
	int pages;
	double typo;
	double poly;
	string name;
	int true_size = 0;
	for (int i = 0; i < size; i++)
	{
		if (ifs >> pages >> typo >> name)
		{
			b[i] = new Special(pages, typo, name);
			true_size++;
			ifs.clear();
		}
		if (ifs >> pages >> typo >> poly >> name)
		{
			b[i] = new Art(pages, typo, poly, name);
			true_size++;
		}
	}
	return true_size;

}

void file_output(string str, Book** b, int true_size)
{
	sort(b, b + true_size, [](Book* x, Book* y) {return (x->get_cost() > y->get_cost()); });
	for (int i = 0; i < true_size; i++)
	{
		b[i]->foutput(str);
	}
}