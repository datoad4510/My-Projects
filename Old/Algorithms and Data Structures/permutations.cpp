#include <iostream>
#include <list>
#include <vector>
using namespace std;

template<typename T>
void print_list(list<T> l)
{
	if (l.size() == 0)
	{
		cout << "{ }";
		return;
	}
	cout << "{ ";
	auto it1 = l.begin();
	auto it2 = it1;
	++it2;
	while (it2 != l.end())
	{
		cout << *it1 << ", ";
		++it1;
		++it2;
	}
	cout << *it1 << " }";
}

template<typename T>
void permute(list<T> to_permute, vector<list<T>>& permutations, int number, list<T> running_permutation = {})//list for fast insertion/deletion
{
	if (running_permutation.size() == number)//
	{
		permutations.push_back(running_permutation);
		return;//backtrack
	}

	for (int i = 0; i < to_permute.size(); ++i)
	{

		auto it1 = to_permute.begin();
		advance(it1, i);
		T temp1 = *it1;
		to_permute.erase(it1);
		running_permutation.push_back(temp1);
		permute(to_permute, permutations, number,running_permutation);
		running_permutation.pop_back();
		auto it2 = to_permute.begin();
		advance(it2, i);
		to_permute.insert(it2, temp1);
	}
}

int main()//additional problem: what if we don't want to permute certain elements? (they're equal in some sense, like skipping duplicates. in this case we can sort and remove duplicates)
{
	list<int> to_permute = { 1,2,3,4 };
	vector<list<int>> vl;
	permute(to_permute, vl,to_permute.size());//the third argument is how many items we are choosing from to_permute. if its to_permute.size(), that's just permutations. if we are choosing less, it's arrangements
	cout << "\n\n";
	for (auto m : vl)
	{
		print_list(m);
		cout << "\n\n";
	}
	system("pause");
}