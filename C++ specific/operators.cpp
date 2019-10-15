#include <iostream>
#include <random>
#include <ctime>
using namespace std;

class myvec
{
	double x = 0;
	double y = 0;
	double z = 0;
public:
	myvec(){}
	myvec(double my_x, double my_y, double my_z) { x = my_x; y = my_y; z = my_z; }
	myvec operator +(myvec&);
	myvec& operator ++();
	myvec operator ++(int);
	myvec operator -(myvec&);
	double operator *(myvec&);
	myvec& operator +=(myvec&);
	myvec& operator =(myvec&);
	friend istream& operator >> (istream&, myvec&);
	friend ostream& operator << (ostream&, myvec&);
	friend void print_vec(myvec&);
};

myvec myvec::operator +(myvec& v)
{
	myvec temp((*this).x + v.x, (*this).y + v.y, (*this).z + v.z);
	return temp;
}

myvec myvec::operator -(myvec& v)
{
	myvec temp((*this).x - v.x, (*this).y - v.y, (*this).z - v.z);
	return temp;
}

double myvec:: operator *(myvec& v)
{
	return (*this).x*v.x + (*this).y*v.y + (*this).z*v.z;
}

myvec& myvec::operator =(myvec& v)
{
	(*this).x = v.x;
	(*this).y = v.y;
	(*this).z = v.z;
	return (*this);
}

myvec& myvec::operator +=(myvec& v)
{
	(*this).x += v.x;
	(*this).y += v.y;
	(*this).z += v.z;
	return (*this);
}

myvec& myvec::operator ++()
{
	((*this).x)++;
	((*this).y)++;
	((*this).z)++;
	return (*this);
}

myvec myvec::operator ++(int)
{
	myvec temp = (*this);
	((*this).x)++;
	((*this).y)++;
	((*this).z)++;
	return temp;
}

double average(double*,int);
istream& operator >> (istream&, myvec&);
ostream& operator << (ostream&, myvec&);

int main()
{
	int size;
	cout << "Input the size of the array: ";
	cin >> size;
	default_random_engine dre;
	uniform_real_distribution<double> urd(0, 100);
	double *p = new(nothrow) double[size];
	if (p == nullptr)
	{
		cout << "Memory allocation failed." << endl;
		system("pause");
	}
	for (int i = 0; i < size; i++)
		p[i] = urd(dre);
	cout << "\nAverage = " << average(p, size) << endl;
	delete[] p;

	int x, y, z;
	cout << "\nPlease input the coordinates of the vector: x = ";
	cin >> x;
	cout << " y = ";
	cin >> y;
	cout << " z = ";
	cin >> z;
	myvec v(x, y, z);
	cout << "\n";
	cout << "v = ";
	print_vec(v);
	cout << "\nv++ = ";
	print_vec(v++);
	cout << "\n++v = ";
	print_vec(++v);
	cout << endl;
	system("pause");
}

double average(double* arr, int size)
{
	double average = 0;
	for (int i = 0; i < size; i++)
		average += arr[i];
	average /= size;
	return average;
}

istream& operator >> (istream& x, myvec& v)
{
	x >> v.x >> v.y >> v.z;
	return x;
}


ostream& operator << (ostream& x, myvec& v)
{
	x << v.x << v.y << v.z;
	return x;
}

void print_vec(myvec& v)
{
	cout << "(" << v.x << "," << v.y << "," << v.z << ")";
}