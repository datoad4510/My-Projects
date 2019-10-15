#include <iostream>
#include <thread>
using namespace std;// thread guarding ver gavige

class functor
{
	int num = 0;
public:
	functor(int n):num(n){}
	~functor(){}
	void operator()()
	{
		for (int i = 0; i < num; i++)
			cout << i << endl;
	}
};




int main()
{
	functor f(100), k(100);
	thread t1(f);//dinebashi am obieqtebis aslebi ketdeba da magatze gamoidzaxeba
	thread t2(k);
	//thread t3((functor(200)));//ese xdeba aslis gadawodeba, winaswar shemqnili obieqtis gareshe
	t1.join();//main function acdis damtavrebas
	t2.join();
	//t1.detach(); es gamoacalkevebda mainisgan. main romc damtavrdes es gaagrdzelebs. agaraa joinable     (t1.joinable() == false)
	thread t4([] { cout << 25 << endl; });//lambda
	t4.join();

	static int n = 10;
	class func
	{
		int k = n; //n static rom ar iyos amas ver vizamdit
	public:
		void operator()() { cout << k << endl; }
	};
	func temp();

	system("pause");
}