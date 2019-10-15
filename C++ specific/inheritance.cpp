#include <iostream>
using namespace std;

class Point 
{
protected:
	double x = 0;
	double y = 0;
public:
	Point() {}
	Point(double a, double b):x(a),y(b){}
	double getX() { return x; }
	double getY() { return y; }
	void setPoint(double a, double b) { x = a; y = b; }
	friend istream& operator >> (istream&, Point&);
	friend ostream& operator << (ostream&, Point&);
};

class Circle : public Point 
{
protected:
	double radius = 0;
public:
	double getR() { return radius; }
	double getArea(){ return (radius*radius*(3.14159)); }
	void setRadius(double r) { radius = r; }
	Circle(double a, double b, double r):Point(a,b),radius(r){}
	Circle(){}
	friend istream& operator >> (istream&, Circle&);
	friend ostream& operator << (ostream&, Circle&);
};

class Cylinder : public Circle
{
protected:
	double height = 0;
public:
	double getH() { return height; }
	double getVolume() { return (*this).getArea()*height; }
	void setHeight(double h) { height = h; }
	Cylinder(){}
	Cylinder(double a, double b, double r, double h):Circle(a,b,r),height(h){}
	friend istream& operator >> (istream&, Cylinder&);
	friend ostream& operator << (ostream&, Cylinder&);
};

istream& operator >> (istream& x, Point& p)
{
	x >> p.x >> p.y;
	return x;
}

ostream& operator << (ostream& x, Point& p)
{
	x << p.x << p.y;
	return x;
}
istream& operator >> (istream& x, Circle& c)
{
	Point* ptr = &c;
	x >> (*ptr) >> c.radius;
	return x;
}

ostream& operator << (ostream& x, Circle& c)
{
	Point* ptr = &c;
	x << (*ptr) << c.radius;
	return x;
}

istream& operator >> (istream& x, Cylinder& c)
{
	Circle* ptr = &c;
	x >> (*ptr) >> c.height;
	return x;
}

ostream& operator << (ostream& x, Cylinder& c)
{
	Circle* ptr = &c;
	x << (*ptr) << c.height;
	return x;
}

int main()
{
	Circle c1(4.5, 6.7, 8.9);
	cout << c1 << endl;
	Cylinder c2(10, 7, 3, 10);
	cout << c2 <<  endl;
	Point* ptr1 = &c2;
	Point p1(1, 2);
	Cylinder* ptr2 = (Cylinder*) &p1;
	cout << endl << (*ptr).getX() << " " << *ptr2->getX() << endl;
	system("pause");
}