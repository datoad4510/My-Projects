#include <iostream>
#include <string>
#include <unordered_set>

#include <unordered_map>
#include <algorithm>
#include <random>

using namespace std;

template<typename InputIterator>
void print(InputIterator first, InputIterator last)
{
	while (first != last) {
		cout << *first << " ";
		++first;
	}
	cout << endl;
}


template <typename T1, typename T2>
ostream& operator << (ostream& strm, const pair<T1, T2>&p)
{
	return strm << "{" << p.first << "," << p.second << "}";
}

template<typename T>
void info(const unordered_set<T>& us)
{
	cout << "\n\nBucket count == " << us.bucket_count() << endl;
	cout << "Size == " << us.size() << endl;
	cout << "Max Bucket count == " << us.max_bucket_count() << endl;
	cout << "Load factor == " << us.load_factor() << endl;
	cout << "Max load factor == " << us.max_load_factor() << endl;
	//iterator category inside buckets:
	if (typeid(us.begin(0))//es chemit vcade, swori xom araa
		== typeid(bidirectional_iterator_tag))
	{
		std::cout << "Chaining style: doubly-linked" << "\n\n";
	}
	else
	{
		std::cout << "Chaining style: singly-linked" << "\n\n";
	}


	auto it = us.begin();
	while (it != us.end())
	{
		cout << "Hash(" << *it << ") == " << us.hash_function()(*it) << "\tkey(" << *it << ") == " << us.hash_function()(*it) % (us.bucket_count()) << endl;
		++it;
	}
	cout << "\n\n";

	for (int i = 0; i < us.bucket_count(); ++i)
	{
		cout << "Bucket[" << i << "] == ";
		auto temp = us.begin(i);
		while (temp != us.end(i))
		{
			cout << *temp << " ";
			++temp;
		}
		cout << endl;
	}
}

template<typename T1,typename T2>
void info(const unordered_multimap<T1,T2>& umm)
{
	cout << "\n\nBucket count == " << umm.bucket_count() << endl;
	cout << "Size == " << umm.size() << endl;
	cout << "Max Bucket count == " << umm.max_bucket_count() << endl;
	cout << "Load factor == " << umm.load_factor() << endl;
	cout << "Max load factor == " << umm.max_load_factor() << endl;
	//iterator category inside buckets (not sure how this works...):
	if (typeid(typename iterator_traits<typename T1::iterator::iterator_category>)
		== typeid(bidirectional_iterator_tag))
	{
		std::cout << "Chaining style: doubly-linked" << "\n\n";
	}
	else
	{
		std::cout << "Chaining style: singly-linked" << "\n\n";
	}

	auto it = umm.begin();
	while (it != umm.end())
	{
		cout << "Hash(" << *it << ") == " << umm.hash_function()((*it).first) << "\tkey(" << *it << ") == " << umm.hash_function()((*it).first) % (umm.bucket_count()) << endl;//hash function mushaobs marto gasagebze, anu first-ze!
		++it;
	}
	cout << "\n\n";

	for (int i = 0; i < umm.bucket_count(); ++i)
	{
		cout << "Bucket[" << i << "] == ";
		auto temp = umm.begin(i);
		while (temp != umm.end(i))
		{
			cout << *temp << " ";
			++temp;
		}
		cout << endl;
	}
}

int main()
{
	unordered_set<string> us = { "Dato","Irakli","Sopo","Vano" };
	cout << "Unordered set: ";
	print(us.begin(), us.end());
	cout << "\nInserting Gosha:\n\n";
	us.insert("Gosha");
	print(us.begin(), us.end());

	info(us);

	us.insert({ "abc","gcd","lcm","aaa","asdasd","quantum physics" });
	cout << endl;
	print(us.begin(), us.end());
	info(us);

	unordered_multimap<string, int> umm;
	auto it = us.begin();
	while (it != us.end())
	{
		umm.insert({ *it,rand() % 10 });
		++it;
	}
	cout << "\n\n\n";
	print(umm.begin(), umm.end());
	info(umm);
	
	auto max = max_element(umm.begin(), umm.end());
	cout << "\nMax element: " << *max << endl;


	system("pause");
}