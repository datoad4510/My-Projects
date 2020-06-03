#include <iostream>
struct func //public by default
{
	int& i; //reference can be uninitialised by default in classes/structs
	func(int& i_):i(i_){} //aseti initialization pirdapir wers i-shi i_-s. int& i_-s magivrad int i_ cudi iqneboda, localuri cvladi romaa imis gamo
	func(int* p):i(*p){}//asec shegvedzlo values nacvlad.
	//func(int& i_){ i = i_} araswori iqneboda. es pirdaprir ar wers, jer default initializerit qmnis i-s (am shemtxvevashi marto ganacxads aketebs) da shemdeg wers masshi i_-s. reference uninitialised ar sheidzleba iyos, amitom arasworia
	//igivenairad
	void operator()()
	{
		std::cout << " i = " << i << std::endl;
	}
};

int main()
{
	int x = 5;
	int& ref1 = x;
	int& ref2 = ref1;
	int* p1 = &ref1;//pointer to a reference is illegal. this just gives &x, therefore we can write this.
	int* p2 = &x;
	func f1(p1);
	func f2(p2);
	func f(x);
	f1();
	f2();
	f();
	system("pause");
	//ref1 = 5 ar sheidzleba amitom
	//func f(1); ar sheidzleba of course
}