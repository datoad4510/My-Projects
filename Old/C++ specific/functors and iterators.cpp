#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<typename T> //function
T add_f(T x, T y)
{
	return x + y;
}

template<typename T> //functor
class add_c
{
public:
	T operator()(T x, T y)const { return x + y; }
};

template<typename InputIt>
auto f(InputIt first, InputIt last)
{
	//zogadad auto-s aucileblad chirdeba inicializeba. tipi sheqmnisasve unda mititdes. magalitad, auto x = *first; sheileba.
	//aq auto ar sheileba, radgan v{} damokidebulia tipze, autom ki jer tipi ar icis.
	typename std::iterator_traits<InputIt>::value_type v{}; //v{} aris default inicializacia. v{5} rom dagvewera magalitad, intebs miscemda sawyis mnishvnelobas 5. stringistvis v{} aris carieli stringit inicializeba, "".
	cout << v << endl;
	while (first != last)
	{
		v += *first;
		++first;
	}
	return v;
}

int main()
{
	/*
	add_c<int> add;
	cout << add_f(2, 3) << endl;
	cout << add(2, 3) << endl;;
	*/
	vector<int> a{ 1,2,3,4,5 };
	auto sum = f(a.begin(), a.end());
	cout << sum << endl;
	vector<string> b{ "we ","work ", "at ", "TSU " };
	auto conc = f(b.begin(), b.end());
	cout << conc << endl;
	system("pause");
}