#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159265359;
class Complex
{
private:
	double a;
	double b;
public:
	Complex(){}
	Complex(double x, double y) { a = x; b = y; }
	void set(double x, double y) { a = x; b = y; }
	Complex operator+(Complex&);
	Complex operator-(Complex&);
	Complex operator*(Complex&);
	Complex operator/(Complex&);
	Complex power(double);
	Complex* root(double);
	bool operator==(Complex&);
	bool operator!=(Complex&);
	Complex conjugate();
};

Complex Complex::operator+(Complex& c)
{
	Complex x(a + c.a, b + c.b);
	return x;
}

Complex Complex::operator-(Complex& c)
{
	Complex x(a - c.a, b - c.b);
	return x;
}

Complex Complex::operator*(Complex& c)
{
	Complex x(a*c.a-b*c.b, b*c.a+a*c.b);
	return x;
}

Complex Complex::operator/(Complex& c)
{
	Complex x((a*c.a + b * c.b) / (c.a*c.a + c.b*c.b), (b*c.a - a * c.b) / (c.a*c.a + c.b*c.b));
	return x;
}

Complex Complex::power(double n)
{
	double  m = sqrt((a * a + b * b));
	double x = asin(a / m);
	Complex c(m*sin(n*x), m*cos(n*x));
	return c;
}

Complex* Complex::root(double n)
{
	Complex* ptr = new Complex[n];
	double  m = sqrt((a * a + b * b));
	double  r = pow(m,1/n);
	double x = asin(a/m);
	for (int k = 0; k < n; k++)
	{
		ptr[k].set(r*sin((x + 2*PI*k)/n), r*cos((x + 2 * PI*k) / n));
	}
}

Complex Complex::conjugate()
{
	Complex c(a, -b);
	return c;
}