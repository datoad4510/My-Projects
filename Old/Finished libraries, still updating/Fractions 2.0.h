#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int GCD(int, int);
int LCM(int, int); // double = fraction ar gamodis....

class fraction
{
private:
	int num;
	int denom;
public:
	friend int GCD(int, int);
	friend int LCM(int, int);
	friend istream& operator >> (istream&, fraction);
	friend ostream& operator << (ostream&, fraction);
	void reduce(void);
	fraction operator + (fraction);
	fraction operator - (fraction);
	fraction operator * (fraction);
	fraction operator / (fraction);
	fraction& operator = (fraction);
	fraction& operator += (fraction);
	fraction& operator -= (fraction);
	fraction& operator *= (fraction);
	fraction& operator /= (fraction);
	bool operator == (fraction);
	bool operator != (fraction);
	bool operator < (fraction);
	bool operator <= (fraction);
	bool operator > (fraction);
	bool operator >= (fraction);

	void operator = (double);
	fraction& operator ++();
	fraction operator ++(int);
	fraction() {}
	fraction(int x, int y) { if (denom != 0) { num = x; denom = y; (*this).adjust_sign(); (*this).reduce(); } else { cout << "Can't divide by zero."; } }
	fraction(double x) { *this = x; }
	int get_Num() { return num; }
	int get_Denom() { return denom; }
	void set_Num(int x) { num = x; (*this).adjust_sign(); (*this).reduce();}
	void set_Denom(int y) { denom = y; (*this).adjust_sign(); (*this).reduce(); }
	void input();
	void show();
	void adjust_sign();
};

fraction fraction::operator + (fraction fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom) + denom * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator - (fraction fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom) - denom * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator * (fraction fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.num);
	new_denom = denom * (fr.denom);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction fraction::operator / (fraction fr)
{
	int new_num;
	int new_denom;
	new_num = num * (fr.denom);
	new_denom = denom * (fr.num);
	fraction new_fr(new_num, new_denom);
	return new_fr;
}

fraction& fraction::operator = (fraction fr)
{
	num = fr.num;
	denom = fr.denom;
	return (*this);
}

fraction& fraction::operator += (fraction fr)
{
	num = num * (fr.denom) + denom * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator -= (fraction fr)
{
	num = num * (fr.denom) - denom * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator *= (fraction fr)
{
	num = num * (fr.num);
	denom = denom * (fr.denom);
	(*this).adjust_sign();
	(*this).reduce();
	return (*this);
}

fraction& fraction::operator /= (fraction fr)
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

bool fraction::operator ==(fraction fr)
{
	if (num == fr.num && denom == fr.denom)
		return true;
	else
		return false;
}

bool fraction::operator !=(fraction fr)
{
	if (num != fr.num || denom != fr.denom)
		return true;
	else
		return false;
}

bool fraction::operator <(fraction fr)
{
	fraction temp = (*this) - fr;
	if (temp.num < 0)
		return true;
	else
		return false;
}

bool fraction::operator <=(fraction fr)
{
	fraction temp = (*this) - fr;
	if (temp.num <= 0)
		return true;
	else
		return false;
}

bool fraction::operator >(fraction fr)
{
	fraction temp = (*this) - fr;
	if (temp.num > 0)
		return true;
	else
		return false;
}

bool fraction::operator >=(fraction fr)
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

istream& operator >> (istream& x, fraction fr)
{
	x >> fr.num >> fr.denom;
	return x;
}

ostream& operator << (ostream& x, fraction fr)
{
	x << fr.num << "/" << fr.denom;
	return x;
}

string fraction_to_decimal(fraction f, int precision, bool capture_period = true)
{
	string decimal;//list xom araa uketesi
	int x = f.get_Num();
	int y = f.get_Denom();
	int temp = 0;
	while (x >= 0)
	{
		x -= y;
		++temp;
	}
	decimal.append(to_string(temp - 1));
	int whole_length = temp;//used for precision, not a part of the algorithm
	x += y;
	if (x == 0)
		return decimal;
	else
		decimal.push_back(',');
	unordered_map<int, int> unique_xes;
	while (x != 0)
	{
		if (decimal.size() - 1 - whole_length == precision)
			return decimal;
		x *= 10;
		while (x < y)
		{
			x *= 10;
			decimal.push_back('0');
		}
		temp = 0;

		if (capture_period == true)
		{
			//looking for a period
			auto it = unique_xes.find(x);
			if (it == unique_xes.end())
			{
				unique_xes.insert(make_pair(x, decimal.size()));
			}
			else
			{
				decimal.push_back(')');
				decimal.insert(decimal.begin() + it->second, '(');
				return decimal;//found period
			}
			//stopping to look for a period, resuming algorithm
		}
		while (x >= 0)
		{
			x -= y;
			++temp;
		}
		decimal.append(to_string(temp - 1));
		x += y;
	}
	return decimal;
}

fraction decimal_to_fraction(string s)//NOT WORKING
{
	int numerator = 0;//whole number gained by shifting the ',' to right before the period
	int i = 0;//iterating variable
	int j = 0;//from ',' to '('
	int k = 0;//size of the whole part
	int t = 0;//size of the period
	while (i < s.size() && s[i] != ',' && s[i] != '(')
	{
		++i;
		++k;
	}
	if (i < s.size() && s[i] == ',')
		++i;
	while (i < s.size() && s[i] != '(')
	{
		++i;
		++j;
	}
	if (i < s.size() && s[i] == '(')
		++i;
	while (i < s.size() && s[i] != ')')
	{
		++i;
		++t;
	}
	int x = 1;
	for (int temp = k + j; temp >= 0; --temp)
	{
		if (s[i] == ',')
			continue;
		numerator += (s[temp] - '0') * x;
		x *= 10;
	}
	//calculating the fraction representation of 0.(period)
	int period_numerator = 0;
	int y = 1;
	for (int temp = t; temp >= 0; --temp)
	{
		period_numerator += (s[temp] - '0') * y;
		y *= 10;
	}
	fraction fr1(numerator, 1);
	fraction period(period_numerator, x - 1);
	fraction fr2(1, x);
	return (fr1 + period)*fr2;
}

double absolute(double);
fraction absolute(fraction);