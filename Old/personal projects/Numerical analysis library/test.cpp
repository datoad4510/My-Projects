#include <iostream>//AQ SOL NUM DA RANK ARIS SHECVLILI. aq rom movrchebi mushaobas gadavitan mtavarshi. vazogadeb am or funqcias martkutxa matricebze. magis mere shemedzleba gausit amoxsna sistemis roca matrica martkutxaa.
#include <string> //Add compatibility with fractions and maybe even complex numbers, with complex adjugates!
#include <cassert>
#include <iomanip>    //!!!!! matrices can access columns out of range!!!! needs to be fixed (proxy classes)
using namespace std; //numerical errors gausshic sajiroa da albat determinantshic (return value daaxloebit 0 roa). gausshi sheileba titqmis nuli iyos full pivot-it archeuli elementi... magram mag shemtxvevashi matrix singular iqneba. anu data[i][i] == 0 ki ara data[i][i] < 0.00000001 !!

double absolute(double);//es funqciebi sawyis matricas cvlis, rom ar sheecvala, localuri matricis sheqmna dasjirdeboda. magas jobia localuri matricis sheqmna momxmarebels mivando
int GCD(int, int); //GCD indentifier not found amis gareshe... arada friend function declaration xo aris qvemot
class fraction
{
private:
	int num;
	int denom;
public:
	friend int GCD(int, int);
	friend int LCM(int, int);
	friend istream& operator >> (istream&, fraction&);
	friend ostream& operator << (ostream&, fraction&);
	void reduce(void);
	fraction operator + (fraction&);
	fraction operator - (fraction&);
	fraction operator * (fraction&);
	fraction operator / (fraction&);
	fraction& operator = (fraction&);
	fraction& operator += (fraction&);
	fraction& operator -= (fraction&);
	fraction& operator *= (fraction&);
	fraction& operator /= (fraction&);
	bool operator == (fraction&);
	bool operator != (fraction&);
	bool operator < (fraction&);
	bool operator <= (fraction&);
	bool operator > (fraction&);
	bool operator >= (fraction&);

	void operator = (double);
	fraction& operator ++();
	fraction operator ++(int);
	fraction();
	fraction(int x, int y);
	fraction(double x);
	int get_Num();
	int get_Denom();
	void input();
	void show();
	void adjust_sign();
};

fraction::fraction() {}

fraction::fraction(int x, int y)
{
	if (denom != 0)
	{
		num = x; denom = y;
		(*this).adjust_sign();
		(*this).reduce();
	}
	else { cout << "Can't divide by zero."; }
}

fraction::fraction(double x)
{
	*this = x;
}

int fraction::get_Num()
{
	return num;
}

int fraction::get_Denom()
{
	return denom;
}

fraction fraction::operator + (fraction& fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom) + denom * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator - (fraction& fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom) - denom * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator * (fraction& fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator / (fraction& fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom);
	new_denom = denom * (fr.num);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction& fraction::operator = (fraction& fr)
{
	num = fr.num;
	denom = fr.denom;
	return (*this);
}

fraction& fraction::operator += (fraction& fr)
{
	num = num * (fr.denom) + denom * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator -= (fraction& fr)
{
	num = num * (fr.denom) - denom * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator *= (fraction& fr)
{
	num = num * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator /= (fraction& fr)
{
	num = num * (fr.denom);
	denom = denom * (fr.num);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator ++()
{
	num++;
	denom++;
	(*this).adjust_sign();
	(*this).reduce();
	return *this;
}

fraction fraction::operator ++(int)
{
	fraction new_fr(num, denom);
	num++;
	denom++;
	(*this).adjust_sign();
	(*this).reduce();
	return new_fr;
}

bool fraction::operator ==(fraction& fr)
{
	if (num == fr.num && denom == fr.denom)
		return true;
	else
		return false;
}

bool fraction::operator !=(fraction& fr)
{
	if (num != fr.num || denom != fr.denom)
		return true;
	else
		return false;
}

bool fraction::operator <(fraction& fr)
{
	fraction temp = (*this) - fr;
	if (temp.num < 0)
		return true;
	else
		return false;
}

bool fraction::operator <=(fraction& fr)
{
	fraction temp = (*this) - fr;
	if (temp.num <= 0)
		return true;
	else
		return false;
}

bool fraction::operator >(fraction& fr)
{
	fraction temp = (*this) - fr;
	if (temp.num > 0)
		return true;
	else
		return false;
}

bool fraction::operator >=(fraction& fr)
{
	fraction temp = (*this) - fr;
	if (temp.num >= 0)
		return true;
	else
		return false;
}

void fraction::input()
{
	int x;
	int y;
	cin >> x;
	system("cls");
	cout << x << "/";
	cin >> y;
	num = x;
	denom = y;
	if (y != 0)
	{
		(*this).adjust_sign();
		(*this).reduce();
	}
	else
	{
		cout << "Can't divide by zero." << endl;
		return;
	}
}

void fraction::reduce()
{
	int temp = GCD(num, denom);
	num = num / temp;
	denom = denom / temp;
}

void fraction::adjust_sign()
{
	if (num == 0)
		return;
	num = abs(num) * (num / abs(num))*(denom / abs(denom)); //nishani gadavcet mricxvels
	denom = abs(denom);
}

void fraction::show()
{
	if (denom == 1)
		cout << num;
	else
		cout << num << "/" << denom;
}

void fraction::operator = (double x) // double to fraction
{
	denom = 1;
	int neg = 0;
	if (x < 0)
	{
		neg++;
		x = -x;
	}
	int y = x; //whole part
			   // while x - whole part != 0, exp++
	while (x - y != 0)
	{
		x *= 10;
		y = x;
		denom *= 10;
	}
	if (neg == 0)
		num = x;
	else
		num = -x;
	this->adjust_sign();
	this->reduce();

}

int GCD(int a, int b)
{
	if (a == 0)
		return 1;
	if (a > b)
	{
		int gasayofi = abs(a);
		int gamyofi = abs(b);
		int nashti = gamyofi;
		while (gasayofi%gamyofi != 0)
		{
			nashti = gasayofi % gamyofi;
			gasayofi = gamyofi;
			gamyofi = nashti;
		}
		return nashti;
	}
	else
	{
		int gasayofi = abs(b);
		int gamyofi = abs(a);
		int nashti = gamyofi;
		while (gasayofi%gamyofi != 0)
		{
			nashti = gasayofi % gamyofi;
			gasayofi = gamyofi;
			gamyofi = nashti;
		}
		return nashti;
	}
}

int LCM(int a, int b)
{
	return (a*b) / GCD(a, b);
}

istream& operator >> (istream& x, fraction& fr)
{
	x >> fr.num >> fr.denom;
	return x;
}

ostream& operator << (ostream& x, fraction& fr)
{
	x << fr.num << "/" << fr.denom;
	return x;
}

template<typename A>
class Matrix  //rows x columns
{
private:
	int rows = 0;
	int columns = 0;
	A** data = nullptr;
public:
	Matrix(int, int);
	Matrix(const Matrix<A>&); //not tested copy constructor must have keyword const
	Matrix(A**, int, int);
	~Matrix();
	Matrix();
	void input(istream& x);
	Matrix& operator=(const Matrix&);
	A* operator[](int);
	Matrix operator*(Matrix&);
	Matrix operator*(A);//eseti danarchenic unda chavamato
	Matrix operator+(Matrix&);
	Matrix operator-(Matrix&);
	bool operator==(Matrix&);
	bool operator!=(Matrix&);
	Matrix& operator*=(Matrix&);
	Matrix& operator+=(Matrix&);
	Matrix& operator-=(Matrix&);
	void exchange_row(int, int);
	void exchange_column(int, int);
	Matrix permutation(int, int);
	double determinant();
	Matrix det_inverse();
	Matrix gauss_inverse(); //es ratomga ar mushaobs????????
							//void LU(Matrix[2]);
							//void LUP(Matrix[3]);       minor aucileblad adjointamde unda iyos c++ standartit, template class type specialization itxovs rom gamoyenebamde gavaketot implementacia
							//void diagonalise(Matrix[3]);
	int rank();//generalize to rectangular matrices
	void sol_num(Matrix&);
	Matrix<double> gauss_solve_generalised(Matrix<double>&);
	Matrix<double> gauss_solve(Matrix<double>&); //damatebiti optimizaciis idea: ar gamoaklo pivot row tu magis qvesh elementi nulovania
	Matrix<fraction> gauss_solve(Matrix<fraction>&);
	Matrix<double> cofactor();//minoris gamo ar mushaobs								//add full pivoting!
	double minor(int, int); //rato ar mushaobs?!?! saxeli ushlida, minor dakavebulia?! axla mushaobs, uazro shecdoma mqonda, continue da jump tanmimdevroba ameria
	void transpose();
	void print(ostream&);
	void check(); //new function for finding numerical errors (not added to other functions yet)
};


template<typename A>
Matrix<A>::Matrix() {}

template<>
void Matrix<double>::check()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (absolute(data[i][j]) < 0.000000001)
			{
				data[i][j] = 0;
			}
		}
	}
}

template<typename A>
void Matrix<A>::input(istream& x)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			x >> data[i][j];
		}
	}
}

template<typename A>
Matrix<A>& Matrix<A>::operator*=(Matrix& m)
{
	assert(columns == m.rows);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			for (int t = 0; t < columns; t++)
			{
				data[i][j] += ((*this)[i][t])*m[t][j];
			}
		}
	}
	return (*this);
}

template<typename A>
Matrix<A>& Matrix<A>::operator+=(Matrix& m)
{
	assert(rows == m.rows && columns == m.columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = (*this)[i][j] + m[i][j];
		}
	}
	return (*this);
}

template<typename A>
Matrix<A>& Matrix<A>::operator-=(Matrix& m)
{
	assert(rows == m.rows && columns == m.columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = (*this)[i][j] - m[i][j];
		}
	}
	return (*this);
}


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

	for (int i = 0; i < x; i++)
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
Matrix<A>::Matrix(const Matrix<A>& m)
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
	assert(x < rows && x >= 0);
	return (*this).data[x];
}

template<typename A>
Matrix<A>::Matrix(A** m, int r, int c)
{
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
	for (int i = 0; i < rows; i++)
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
			x << setw(10) << (*this)[i][j] << " ";
			if (j == columns - 1)
				cout << "\n\n";

		}
	}
}

template<typename A>
Matrix<A> Matrix<A>::operator*(Matrix& m)
{
	assert(columns == m.rows);
	Matrix<A> Mat(rows, m.columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			for (int t = 0; t < columns; t++)
			{
				Mat[i][j] += ((*this)[i][t])*m[t][j];
			}
		}
	}
	return Mat;
}

template<typename A>
Matrix<A> Matrix<A>::operator*(A c)
{
	Matrix<A> Mat(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Mat[i][j] = data[i][j];
			Mat[i][j] *= c;
		}
	}
	return Mat;
}


template<typename A>
Matrix<A> Matrix<A>::operator+(Matrix& m)
{
	assert(rows == m.rows && columns == m.columns);
	Matrix<A> Mat(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Mat[i][j] = (*this)[i][j] + m[i][j];
		}
	}
	return Mat;
}

template<typename A>
Matrix<A> Matrix<A>::operator-(Matrix& m)
{
	assert(rows == m.rows && columns == m.columns);
	Matrix<A> Mat(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Mat[i][j] = (*this)[i][j] - m[i][j];
		}
	}
	return Mat;
}

template<typename A>
bool Matrix<A>::operator==(Matrix& m)
{
	assert(rows == m.rows && columns == m.columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if ((*this)[i][j] != m[i][j])
			{
				if (absolute((*this)[i][j] - m[i][j]) < 0.000000001) //because of numerical errors
				{
					continue;
				}
				return false;
			}
		}
	}
	return true;
}

template<typename A>
bool Matrix<A>::operator!=(Matrix& m)
{
	return !((*this) == m);
}

template<typename A>
void Matrix<A>::exchange_row(int m, int n) //first row and column have 0 index
{
	assert(0 <= m && m < rows && 0 <= n && n < rows);
	A* temp = new A[columns];
	for (int j = 0; j < columns; j++)
	{
		temp[j] = data[m][j];
		data[m][j] = data[n][j];
		data[n][j] = temp[j];
	}
	delete[] temp;
}

template<typename A>
void Matrix<A>::exchange_column(int m, int n) //same comment
{
	assert(0 <= m && m < columns && 0 <= n && n < columns);
	A* temp = new A[rows];
	for (int i = 0; i < rows; i++)
	{
		temp[i] = data[i][m];
		data[i][m] = data[i][n];
		data[i][n] = temp[i];
	}
	delete[] temp;
}

template<typename A>
Matrix<A> Matrix<A>::permutation(int m, int n)
{
	assert(rows == columns);
	Matrix<double> M(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		M.data[i][i] = 1;
	}
	M.data[m][m] = 0;
	M.data[m][n] = 1;
	M.data[n][n] = 0;
	M.data[n][m] = 1;
	return M;
}

template<>
Matrix<double> Matrix<double>::gauss_solve(Matrix<double>& b)
{
	assert(rows == columns);
	assert(b.columns == 1 && b.rows == rows);
	for (int i = 0; i < rows - 1; i++) //aq rows iyo
	{
		double max = data[i][i];
		int max_index = i;
		for (int k = i + 1; k < rows; k++) //rows da ara rows - 1, ese ipovis bolo row tu nulovania da gvetyvis aris tu ara singular
		{
			if (absolute(data[k][i]) > absolute(max))
			{
				max = data[k][i];
				max_index = k;
			}
		}
		if (max_index != i)
		{
			this->exchange_row(i, max_index);
			b.exchange_row(i, max_index);
		}
		if (data[i][i] <= 0.000000001)
		{
			cout << "The matrix is singular!";
			assert(data[i][i] <= 0.000000001); //maybe a more lenient error?
		}

		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
				if (absolute(data[k][j]) <= 0.000000001)
					data[k][j] = 0;
			}
			b[k][0] -= b[i][0] * m;
			if (absolute(b[k][0]) <= 0.000000001)
				b[k][0] = 0;
		}
	}

	Matrix<double> x(rows, 1);
	x[rows - 1][0] = b[rows - 1][0] / data[rows - 1][rows - 1];
	for (int i = rows - 1; i >= 0; i--) //backward substitution
	{
		double temp = 0;
		for (int j = i + 1; j < rows; j++)
		{
			assert(i < rows && i >= 0);
			assert(j < rows && j >= 0);
			temp += data[i][j] * x[j][0];
		}
		x[i][0] = (b[i][0] - temp) / data[i][i];
		if (absolute(x[i][0]) <= 0.000000001)
			x[i][0] = 0;
	}
	return x;
}

template<>
Matrix<fraction> Matrix<fraction>::gauss_solve(Matrix<fraction>& b)
{
	assert(rows == columns);
	assert(b.columns == 1 && b.rows == rows);
	for (int i = 0; i < rows - 1; i++) //aq rows iyo
	{
		fraction max = data[i][i];
		int max_index = i;
		for (int k = i + 1; k < rows; k++) //rows da ara rows - 1, ese ipovis bolo row tu nulovania da gvetyvis aris tu ara singular
		{
			if (absolute(data[k][i]) > absolute(max))
			{
				max = data[k][i];
				max_index = k;
			}
		}
		if (max_index != i)
		{
			this->exchange_row(i, max_index);
			b.exchange_row(i, max_index);
		}
		for (int k = i + 1; k < rows; k++)
		{
			fraction m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
			}
			b[k][0] -= b[i][0] * m;
		}
	}

	Matrix<fraction> x(rows, 1);
	x[rows - 1][0] = b[rows - 1][0] / data[rows - 1][rows - 1];
	for (int i = rows - 1; i >= 0; i--) //backward substitution
	{
		fraction temp = 0;
		for (int j = i + 1; j < rows; j++)
		{
			assert(i < rows && i >= 0);
			assert(j < rows && j >= 0);
			temp += data[i][j] * x[j][0];
		}
		x[i][0] = (b[i][0] - temp) / data[i][i];
	}
	return x;
}


template<>
Matrix<double> Matrix<double>::gauss_solve_generalised(Matrix<double>& b)
{
	assert(b.columns == 1 && b.rows == rows);
	Matrix<double> temp1 = *this;
	Matrix<double> temp2 = b;

	int sol; //0 - none, 1 - one, 2 - inf
	int rank;
	int w;
	if (rows > columns) //0 - no solutions, 1 - one solution, 2 - infinite number of solutions.
		w = columns;
	else
		w = rows;

	for (int i = 0; i < w; i++) //rank calculation modified
	{
		double max = temp1[i][i];
		int max_row = i;
		int max_col = i;
		for (int k = i; k < rows; k++)
		{
			for (int p = i; p < columns; p++) //full pivoting. amis gareshe bolos mogviwevda shemowmeba romeli striqonebia ganulebuli, tanac full pivoting zrdis sizusted
				if (absolute(temp1[k][p]) > absolute(max))
				{
					max = data[k][p];
					max_row = k;
					max_col = p;
				}
		}
		if (max_row != i || max_col != i)
		{
			temp1.exchange_row(i, max_row);
			temp2.exchange_row(i, max_row); //modification
			temp1.exchange_column(i, max_col);
		}
		if (temp1[i][i] == 0)
		{
			rank = i;
			break;
		}
		for (int k = i + 1; k < rows; k++)
		{
			double m = temp1[k][i] / temp1[i][i];
			for (int j = i; j < columns; j++)
			{
				temp1[k][j] -= temp1[i][j] * m;
				if (absolute(temp1[k][j]) <= 0.000000001)
					temp1[k][j] = 0;
			}
			temp2[k][0] -= temp2[i][0] * m;
			if (absolute(temp2[k][0]) <= 0.000000001)
				temp2[k][0] = 0;
		}
		if (i == w - 1)
		{
			rank = w;
			break;
		}
	}
	double sum = 0;
	for (int i = rank; i < rows; i++)
	{
		sum += absolute(temp2[i][0]);
	}
	if (sum != 0)
	{
		sol = 0;
	}
	else
	{
		if (rank == columns)
		{
			sol = 1;
		}
		else
		{
			sol = 2;
		}
	}



	if (sol == 0)
	{
		cout << "There are no solutions!" << endl; //how to make this better?
		assert(sol != 0);
	}
	if (sol == 2)
	{
		int free_var = columns - rank;
		cout << "There is an infinite number of solutions. The number of free variables is " << free_var << endl; //this is even worse
		assert(sol != 2);
	}

	//exla,radgan ertaderti amonaxsnia, unda dagvijdes martkutxa matricashi patara kvadrati. tan, im patara kvadratis diagonalze nulebi ar gveqneba, anu shemowmeba arc ki gvinda
	//rank = columns, anu ramdeni ucnobicaa, imdeni wrfivad damoukidebeli striqonia. tu rows >= columns, es kvadrati zemot dajdeba striqonebis gadaadgilebit. rows < columns sheudzlebelia. (eseti rame sheileba moxdes, rom kvadrati marcxena kutxeshi iyos, magram mashin amonaxsnta raodenoba usasrulo iqneba! yvela nul sveti tavisufal cvlads sheesabameba)
	for (int i = 0; i < columns - 1; i++) //aq rows iyo  aq unda chavwero min(rows,columns) = columns     //e.i. rows>=columns ( tu = es igive kvadratuli matricaa)
	{
		double max = data[i][i];
		int max_index = i;
		for (int k = i + 1; k < rows; k++) //rows da ara rows - 1, ese ipovis bolo row tu nulovania da gvetyvis aris tu ara singular
		{
			if (absolute(data[k][i]) > absolute(max)) //partial pivoting sakmarisia, radgan kvadrati unda dajdes qvemot nulebit
			{
				max = data[k][i];
				max_index = k;
			}
		}
		if (max_index != i)
		{
			this->exchange_row(i, max_index);
			b.exchange_row(i, max_index);
		}
		if (data[i][i] <= 0.000000001) //yvela elementi diagonalqvesha (da titon diagonalis romlis qveshac arian) 0-ia, gadavidet shemdegze
		{
			cout << "ERROR! algorithm not working properly! kvadrati ar dajda!";
			assert(0 == 1);
		}

		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
				if (absolute(data[k][j]) <= 0.000000001)
					data[k][j] = 0;
			}
			b[k][0] -= b[i][0] * m;
			if (absolute(b[k][0]) <= 0.000000001)
				b[k][0] = 0;
		}
	}

	Matrix<double> x(columns, 1);
	x[columns - 1][0] = b[columns - 1][0] / data[columns - 1][columns - 1];
	for (int i = columns - 1; i >= 0; i--) //backward substitution
	{
		double temp = 0;
		for (int j = i + 1; j < columns; j++)
		{
			assert(i < rows && i >= 0);
			assert(j < rows && j >= 0);
			temp += data[i][j] * x[j][0];
		}
		x[i][0] = (b[i][0] - temp) / data[i][i];
		if (absolute(x[i][0]) <= 0.000000001)
			x[i][0] = 0;
	}
	return x;
}

template<>
double Matrix<double>::determinant()
{
	int perm = 0;
	assert(rows == columns);
	for (int i = 0; i < rows; i++)
	{
		double max = data[i][i];
		int max_index = i;
		for (int k = i + 1; k < rows; k++) //rows da ara rows - 1, ese ipovis bolo row tu nulovania da gvetyvis aris tu ara singular
		{
			if (absolute(data[k][i]) > absolute(max))
			{
				max = data[k][i];
				max_index = k;
			}
		}
		if (max_index != i)
		{
			this->exchange_row(i, max_index);
			perm++;
		}
		if (data[i][i] == 0)
		{
			return 0;
		}
		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
				if (absolute(data[k][j]) <= 0.000000001)
					data[k][j] = 0;
			}
		}
	}
	double det;
	if (perm % 2 == 0)
	{
		det = 1;
	}
	else
	{
		det = -1;
	}
	for (int i = 0; i < rows; i++)
	{
		det *= data[i][i];
	}
	if (absolute(det) <= 0.000000001)
		det = 0;
	return det;
}


template<>
double Matrix<double>::minor(int m, int n)
{
	assert(rows == columns);
	assert(0 <= m && m < rows && 0 <= n && n < columns);
	Matrix<double> temp(rows - 1, columns - 1);
	bool jump1 = false;
	for (int i = 0; i < rows; i++)
	{
		if (i == m)
		{
			jump1 = true;
			continue;
		}
		bool jump2 = false;
		for (int j = 0; j < columns; j++)
		{
			if (j == n)
			{
				jump2 = true;
				continue;
			}
			if (jump2 == true && jump1 == true)
			{
				temp[i - 1][j - 1] = data[i][j];
				continue;
			}
			if (jump2 == true && jump1 == false)
			{
				temp[i][j - 1] = data[i][j];
				continue;
			}
			if (jump2 == false && jump1 == true)
			{
				temp[i - 1][j] = data[i][j];
				continue;
			}
			temp[i][j] = data[i][j];
		}
	}
	return temp.determinant();
}

template<>
Matrix<double> Matrix<double>::cofactor()
{
	assert(rows == columns);
	Matrix<double> temp(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int factor;
			if ((i + j) % 2 == 0)
				factor = 1;
			else
				factor = -1;
			temp[i][j] = factor * (this->minor(i, j));
		}
	}
	return temp;
}

template<>
int Matrix<double>::rank()
{
	int w;
	if (rows > columns)
		w = columns;
	else
		w = rows;
	for (int i = 0; i < w; i++)
	{
		double max = data[i][i];
		int max_row = i;
		int max_col = i;
		for (int k = i; k < rows; k++)
		{
			for (int p = i; p < columns; p++) //full pivoting. amis gareshe bolos mogviwevda shemowmeba romeli striqonebia ganulebuli, tanac full pivoting zrdis sizusted
				if (absolute(data[k][p]) > absolute(max))
				{
					max = data[k][p];
					max_row = k;
					max_col = p;
				}
		}
		if (max_row != i || max_col != i)
		{
			this->exchange_row(i, max_row);
			this->exchange_column(i, max_col);
		}
		if (data[i][i] == 0)
			return i;
		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
				if (absolute(data[k][j]) <= 0.000000001) //maybe will help errors...
					data[k][j] = 0;
			}
		}
		if (i == w - 1)
			return w;
	}
}

template<>//temp*(1/det) ratom ar shveba pirdapir?? imitorm rom reference ar aris 1/det... cvladi ar aris, ubralod mnishvnelobaa... exla shevcvale, manamde refereence qonda funqcias parametrad
Matrix<double> Matrix<double>::det_inverse()
{
	Matrix<double> temp = this->cofactor();
	temp.transpose();
	double det = this->determinant(); //es cvlis sawyis matricas
	assert(det != 0);
	temp = temp * (1 / det);
	(*this) = temp; //amitomac es unda vqnat
	return temp;
}


template<>
Matrix<double> Matrix<double>::gauss_inverse() //new
{
	assert(rows == columns);
	Matrix<double> temp = (*this);
	int rank = temp.rank();
	if (rank != columns)
	{
		cout << "The matrix is singular!" << endl;
		assert(rank == columns);
	}
	Matrix<double> col(rows, 1);
	Matrix<double>* ptr = new Matrix<double>[columns];
	Matrix<double> original1 = (*this);
	for (int j = 0; j < columns; j++)
	{
		Matrix<double> original = original1;
		ptr[j] = col;
		(ptr[j])[j][0] = 1; //columns of the identity matrix
		Matrix<double> temp1 = ptr[j]; //rom ar sheicvalos ptr[j]
		ptr[j] = original.gauss_solve(temp1); //LU factorizaciit ufro gaswrafdeba, amdenjer amoxsna agar dasjirdeba!
		for (int i = 0; i < rows; i++)
		{
			data[i][j] = (ptr[j])[i][0];
		}
	}
	return (*this);
}


template<>
void Matrix<double>::sol_num(Matrix<double>& x) //very prone to numerical errors. DONE AT LAST FFS. this and rank both.
												//kronecker-capelli theorem (this takes care of overdetermined systems as well, but has to calculate the rank of 2 matrices
{	//albat kronecker capellis gareshec sheileba mara ar maq damtkicebuli da ar var darwmumenubli (tore ese nelia cota)
	//int rank = this->rank();//ise aq text-s jobs int-s abrunebdes
	//memgoni prosto ese: gauss elimination, shevxedot 0 = 6 and rame maseti dajda tu ara, tu ar dajda, tu rank == columns ertaderti amonaxsnia (chatvale kvadratuli dajda), tu rank < columns uamravi (trapeciuli formaa igive, araoverdetermined.). rank > columns sheudzlebelia tu gausis algoritms shevxedavt, maximum samkutxa sheileba dajdes qvemot nulebit tu overdetermined aris! tu ar aris overdetermined cxadia sheudzlebelia rank > columns. (aseve, 0 = 0-is damateba ar cvlis sistemis amonaxsns. 0 = 0-s nebismieri amonaxni veqtori akmayofilebs, amitomac rac iqneba danarchenis amonaxsni is iqneba amisac. (amasac unda akmayofilebdes da imatac, amas kide yvela akmayofilebs. imat rac akmayofilebs yvela akmayofilebs amas, piriqit arasworia. gantolebis damatebam sheileba sheamciros amonaxsnebis raodenoba magram ara gazardos, im wina nakrebs rac akmayofilebda yvela amasac sheileba ar akmayofilebdes.) )
	int rank; //i < columns ki ara, max(rows,columns). shesaswavlia.
	int w;
	if (rows > columns)
		w = columns;
	else
		w = rows;

	for (int i = 0; i < w; i++) //rank calculation modified
	{
		double max = data[i][i];
		int max_row = i;
		int max_col = i;
		for (int k = i; k < rows; k++)
		{
			for (int p = i; p < columns; p++) //full pivoting. amis gareshe bolos mogviwevda shemowmeba romeli striqonebia ganulebuli, tanac full pivoting zrdis sizusted
				if (absolute(data[k][p]) > absolute(max))
				{
					max = data[k][p];
					max_row = k;
					max_col = p;
				}
		}
		if (max_row != i || max_col != i)
		{
			this->exchange_row(i, max_row);
			x.exchange_row(i, max_row); //modification
			this->exchange_column(i, max_col);
		}
		if (data[i][i] == 0)
		{
			rank = i;
			break;
		}
		for (int k = i + 1; k < rows; k++)
		{
			double m = data[k][i] / data[i][i];
			for (int j = i; j < columns; j++)
			{
				data[k][j] -= data[i][j] * m;
				if (absolute(data[k][j]) <= 0.000000001)
					data[k][j] = 0;
			}
			x[k][0] -= x[i][0] * m;
			if (absolute(x[k][0]) <= 0.000000001)
				x[k][0] = 0;
		}
		if (i == w - 1)
		{
			rank = w;
			break;
		}
	}
	double sum = 0;
	for (int i = rank; i < rows; i++)
	{
		sum += absolute(x[i][0]);
	}
	if (sum != 0)
	{
		cout << "There are no solutions." << endl;
		return;
	}
	else
	{
		if (rank == columns)
		{
			cout << "There is only one solution." << endl;
			return;
		}
		else
		{
			cout << "There is an infinite number of solutions. The number of free variables is " << columns - rank << endl;
			return;
		}
	}
}

template<typename A>
Matrix<A>& Matrix<A>::operator=(const Matrix<A>& m)
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
	return (*this);
}

double absolute(double x)
{
	if (x >= 0)
		return x;
	else
		return x * (-1);
}

fraction absolute(fraction x)
{
	if (x.get_Num() >= 0)
		return x;
	else
	{
		fraction temp(-1 * x.get_Denom(), x.get_Num());
		return temp;
	}
}

int main()
{
	fraction fr1(1, 2);
	fraction fr2(3, 4);
	fr1 > fr2;
	cout << fr1 << endl;
	getchar();
}