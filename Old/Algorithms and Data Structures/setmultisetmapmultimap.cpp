#include <set>//set/map bidirectional
#include <map>
#include <list>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

template<typename InputIterator>
void print(InputIterator first, InputIterator last)
{
	while (first != last)
	{
		cout << *first << " ";
		++first;
	}
	cout << endl;
}


template<typename T>
class mygreater
{
public:
	bool operator()(T x, T y) const { return x > y; }
};


template<typename T1, typename T2>
class greatersecond
{
public:
	bool operator()(pair<T1, T2> p1, pair<T1, T2> p2) const { return p1.second > p2.second; }
};


int main()
{
	cout << "Set:\n\n";
	set<int> s = { 5,2,3,1,4,5 };
	print(s.begin(), s.end());

	int x[] = { 2,4,10 };
	s.insert(x, x + 3); //[x,x+3)
	print(s.begin(), s.end());

	list<int> l = { -3,27 };
	s.insert(l.begin(), l.end());//aseti insert arafers ar abrunebs
	s.insert(-1);
	print(s.begin(), s.end());

	auto it = s.end();
	--it;
	cout << "it utitebs " << *it << "-ze, rac 15-is shemdegi elementi iqneba misi chamatebis shemdeg." << endl;
	s.insert(it, 15);//aseti insert abrunebs 15-is iterators set-shi chamatebis shemdeg(tu ukve iyo magas abunebs)
	print(s.begin(), s.end());

	s.insert(399);
	pair<set<int>::iterator, bool> p = s.insert(11);//aseti insert abrunebs wyvils. multisetshi esec iterators abrunebs
	if (p.second == true)
		cout << "Successfully added 11 to the set." << endl;
	else
		cout << "11 was already in the set." << endl;
	s.insert(++p.first, 12);//fast insertion
	print(s.begin(), s.end());

	auto it2 = s.find(5);
	/*			^^^^^^^^
	Searches the container for an element equivalent to val and returns an iterator to it if found, otherwise it returns an iterator to set::end.

	Two elements of a set are considered equivalent if the container's comparison object returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).

	*/
	auto it3 = find(s.begin(), s.end(), 5);//igives abrunebs, O(n) aris. zeda O(logn)

	s.erase(399);
	s.erase(s.begin());
	print(s.begin(), s.end());

	multiset<int> ms(s.begin(), s.end());
	cout << "\n\n\Multiset:\n\n";
	print(ms.begin(), ms.end());
	ms.insert(11);
	ms.insert(11);
	auto it4 = ms.insert(4);
	print(ms.begin(), ms.end());
	ms.erase(11);//returns number of elements erased (for set too)
	auto it5 = ms.erase(it4);//returns the iterator to the element that follows the last element that was deleted
	print(ms.begin(), ms.end());
	ms.erase(it5, ms.end());
	print(ms.begin(), ms.end());


	cout << "Maximum: " << *ms.rbegin() << endl;
	cout << "Minimum: " << *ms.begin() << "\n\n\n\n";

	set<int, mygreater<int>> s_pred(ms.begin(), ms.end());//gulisxmobit less<int>
	print(s_pred.begin(), s_pred.end());
	cout << "\n\n\n" << "Map:\n\n";

	map<string, int, mygreater<string>> m; //predikati yoveltvis first-it alagebs (key-ti). tu meoreti gvinda davalagot, set unda gavaketot.
	m.insert(make_pair("Dato", 100));//multimaps ar aqvs mm["Jumberi"], ar icis ra daabrunos.
	m.insert(make_pair("Irakli", 99));//pairebi dardeba lexikografiulad,gulisxmobit less<int>
	m["Jumberi"] = 121;//amistvis sachiroa, rom predikatis () operacia iyos const
	cout << "\n\n" << m["Jumberi"] << "\n\n";//multimaps es rom ar sheudzlia, amis gamo araaq [] operacia.
	auto first = m.begin();//map aris pair-ebis set.
	auto last = m.end();
	while (first != last)
	{
		cout << first->first << ":" << first->second << endl;
		++first;
	}
	cout << "\n\n\n";

	set<pair<string, int>, greatersecond<string, int>> pairset;//!!!set-shi pair-ebi lexicografiulad (jer firstit, tu tolia mere secondit) dardeba jer pirveli elementit, mere meoreti. map-shi marto pirvelit!!!
	pairset.insert(make_pair("Dato", 100));//!!!map-shi shesadzlebelia second-is shecvla, set-shi ara, set-shi unda washalo da axali chaamato!!!
	pairset.insert(make_pair("Irakli", 99));
	pairset.insert(make_pair("Jumberi", 121));
	auto it_ = pairset.find(make_pair("", 100));//find iyenebs aset tolobas: tu !greatersecond(a,b) da !greatersecond(b,a), mashin a == b da abrunebs. first-s radganac ar iyenebs mnishvneloba ar aq
	if (it_ == pairset.end())
		cout << "p.second == 100 not found\n\n\n";
	else
		cout << it_->first << ":" << it_->second << "\n\n\n";

	multimap<string, int> mulm = { { "Dato",100 },{ "Irakli",99 },{ "Jumberi",121 } };//initialzer list initialization. set<string>-shi iqneba {{"abc"},{"cb"}}

	mulm.insert({ { "aa",2 },{ "bb",3 } });//initializer list insertion

	system("pause");
}