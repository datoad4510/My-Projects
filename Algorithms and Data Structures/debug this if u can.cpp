#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

template<typename A>
class Matrix  //rows x columns
{
private:
	int rows = 0;
	int columns = 0;
	bool det_calculated = 1;
	double determinant = 0;
	A** data = nullptr;
public:
	Matrix(int, int);
	Matrix(Matrix<A>&);
	Matrix(A**);
	~Matrix();
	A* operator[](int);
	void transpose();
	void print(ostream&);
};

template<typename A>
Matrix<A>::Matrix(int x, int y)
{
	rows = x;
	columns = y;

	data = new A*[x];
	for (int i = 0; i < x; i++)
	{
		data[i] = new A[y];
	}

	for(int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
		{
			data[i][j] = 0;
		}
}

template<typename A>
Matrix<A>::~Matrix()
{
	for (int i = 0; i < rows; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}

template<typename A>
Matrix<A>::Matrix(Matrix<A>& m)
{
	if (rows == m.rows && columns == m.columns)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
			{
				data[i][j] = m.data[i][j];
			}
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		rows = m.rows;
		columns = m.columns;

		data = new A*[m.rows];
		for (int i = 0; i < m.rows; i++)
		{
			data[i] = new A[m.columns];
		}

		for (int i = 0; i < m.rows; i++)
			for (int j = 0; j < m.columns; j++)
			{
				data[i][j] = m.data[i][j];
			}
	}
}

template<typename A>
A* Matrix<A>::operator[](int x)
{
	return (*this).data[x];
}

template<typename A>
Matrix<A>::Matrix(A** m)
{
	int r = sizeof(m) / sizeof(A);
	int c = sizeof(m[0]) / sizeof(A);
	if (rows == r && columns == c)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
			{
				data[i][j] = m[i][j];
			}
	}
	else
	{
		for (int i = 0; i < rows; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		rows = r;
		columns = c;

		data = new A*[r];
		for (int i = 0; i < r; i++)
		{
			data[i] = new A[c];
		}

		for (int i = 0; i < c; i++)
			for (int j = 0; j < c; j++)
			{
				data[i][j] = m[i][j];
			}
	}
}

template<typename A>
void Matrix<A>::transpose()
{
	A** temp = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		temp[i] = new A[columns];
	}
	for(int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			temp[i][j] = data[i][j];
		}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = temp[j][i];
		}
	for (int i = 0; i < rows; i++)
		delete[] temp[i];
	delete[] temp;
}

template<typename A>
void Matrix<A>::print(ostream& x)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			x << setw(10) << (*this)[i][j] <<" ";
			if (j == columns - 1)
				cout << "\n\n";

		}
	}
}


int main()
{
	double** ptr = new double*[5];
	for (int i = 0; i < 5; i++)
	{
		ptr[i] = new double[5];
		for (int j = 0; j < 5; j++)
		{

			ptr[i][j] = i + j;
		}
	}
	Matrix<double> M(ptr);
	cout << M[0][0];
	M.transpose();
	M.print(cout);
	for (int i = 0; i < 5; i++)
		delete[] ptr[i];
	delete[] ptr;
	system("pause");
}
