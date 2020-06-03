#include <iostream>
using namespace std;

const int a = 5;
//int& b = a; arasworia.
const int& b = a; // sworia
				  //int* c = &a; arasworia.
const int* c = &a; //sworia
int d = a; //sworia
const int e = a; //sworia
const int const *f = nullptr; //sworia
const int* g = f; //sworia (?!)


class Circle
{
public:
	//Circle():radius(0){ count++; }	aq araa sajiro uparametro konstruqtori,radgan parametriania gulisxmobis principit		// :radius = 0 shecdomaa. radius(0) ara. es sawyis mnishvnelobas adzlevs gulisxmobis principit. shegvedzlo amis magivrad privateshi double radius = 0;
	Circle(double = 0);		//parametriani gulisxmobis principit, radius = x = 0
	~Circle() { count--; } //klasis shignit implementirebuli funqcia avtomaturad inline aris. kidev ertxel miwera arafers cvlis
	static int getCount();
	double getRadius()const;
	void setRadius(double);
	double getArea()const;
	double getPerimeter()const;
private:
	double radius;
	const double PI = 3.14159;
	static int count;						//klasis shignit statikuri cvladis inicializeba marto mashin sheidzleba tu constia. metodi unda iyos static tu static cvlads iyenebs. prototips unda static, implementacias ara. (tu implementacia klasshia, mashin unda).
};		// member variable ar unda iyos meoreze damokdiebuli torem uazrobebi xdeba. jobia marto radius iyos
		//radgan getCount ar iyenebs obieqtis monacemebs, es funqcia shegvidzlia gamovidzaxot ornairad: Test::getCount() an (nebismieriobieqti).getCount()


const Circle* max_radius_pointer(const Circle *, const Circle *);    //es klasze ganacxadis shemdeg unda iyos.
const Circle& max_radius_reference(const Circle*, const Circle*);
Circle max_radius_value(const Circle, const Circle);

int Circle::count = 0;

Circle::Circle(double x)
{
	radius = x;
	count++;
}

int Circle::getCount()
{
	return count;
}

double Circle::getRadius()const				//aq const tu ar dawer shecdomaa. shegvidzlia gadavtvirtot const da ara const. const Circle c obieqtze mushaoba marto const metodebs sheudzliat. es nishnavs rom radius ar icvleba
{
	return radius;
}

double Circle::getArea()const
{
	return PI*radius*radius;
}

double Circle::getPerimeter()const
{
	return 2 * PI*radius;
}

void Circle::setRadius(double x)
{
	radius = x;
}

int main()
{
	Circle c1(5), c2(7);
	Circle c3 = max_radius_reference(&c1, &c2);
	Circle c4 = max_radius_value(c1, c2);
	cout << c4.getRadius() << max_radius_value(c1, c2).getRadius() << endl;
	cout << &c3 << " " << &max_radius_reference(&c1, &c2) << endl; //roca funqcia abrunebs references, e.i. abrunebs im cvladis saxels. references gareshe es iqneboda rogorc c3 = 7. referenceti es aris c3 = c2. Circle x = c3 da Circle x = 7 -s shoris gansxvaveba araa, magram Circle& x = c3 sxva ramea, Circle& x = 7 arasworia
	cout << c3.getRadius() << max_radius_reference(&c1, &c2).getRadius() << max_radius_pointer(&c1, &c2)->getRadius() << endl;

	system("pause");

}


const Circle* max_radius_pointer(const Circle *x, const Circle *y) //aqac
{
	if (x->getRadius() > y->getRadius())
		return x;
	else
		return y;
}

const Circle& max_radius_reference(const Circle *x, const Circle *y)  //aq ratom ver vuwer constebs rogorc value-shi? konspeqtshi saertod ar ewera constebi. sul zemot naxe da mixvdebi ratomac
{
	if (x->getRadius() > y->getRadius())   //tavi rom ar aitkio, constebi ar daabruno,jobs lokaluri cvladi gaxsna
		return *x;
	else
		return *y;
}

Circle max_radius_value(const Circle x, const Circle y)
{
	if (x.getRadius() > y.getRadius())
		return x;
	else
		return y;
}
