#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <map>
#include <cassert>
#include <algorithm>
#include <stack>
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


double absolute(double);
fraction absolute(fraction);

string priorities = "+-*/(";

string operators = "+-*/";

bool less_priority(char x, char y)
{
	auto it = find(priorities.begin(), priorities.end(), x);
	auto temp = next(it);
	while (temp != priorities.end())
	{
		if (*it == y)
		{
			return true;
		}
		++it;
		++temp;
	}
	return false;
}

string infix_to_postfix(string infix)
{
	string output;
	stack<char> stack;
	int i = 0;
	while (i < infix.size())
	{
		auto it = find(priorities.begin(), priorities.end(), infix[i]);
		if (i < infix.size() && it == priorities.end() && infix[i] != ')')//if there are one or more numbers in a row
		{
			while (i < infix.size() && it == priorities.end() && infix[i] != ')')
			{
				output.push_back(infix[i]);
				++i;
				it = find(priorities.begin(), priorities.end(), infix[i]);
			}
			output.push_back(' ');
		}
		else
		{
			if (i < infix.size() && infix[i] != ')')
			{
				if (stack.size() == 0)
				{
					stack.push(infix[i]);
					++i;
					continue;
				}
				if (less_priority(stack.top(), infix[i]))
				{
					stack.push(infix[i]);
					++i;
					continue;
				}


				while (stack.size() != 0 && less_priority(infix[i], stack.top()))
				{
					output.push_back(stack.top());
					output.push_back(' ');
					stack.pop();
				}
				stack.push(infix[i]);
				++i;

			}
			else if (i < infix.size() && infix[i] == ')')
			{
				while (stack.top() != '(')//if it becomes empty, expression is invalid
				{
					output.push_back(stack.top());
					output.push_back(' ');
					stack.pop();
				}
				stack.pop();
				++i;
				continue;
			}
		}
	}
	while (stack.size() != 0)
	{
		output.push_back(stack.top());
		output.push_back(' ');
		stack.pop();
	}
	//output.pop_back(); to remove the extra ' ' at the end 
	return output;
}

int number_from_digits(vector<char> digits)
{
	int x = 1;
	int number = 0;
	for (int i = digits.size() - 1; i >= 0; --i)
	{
		number += x*(digits[i] - '0');
		x *= 10;
	}
	return number;
}

int calculate_postfix(string postfix)
{
	stack<int> stack;
	for (int i = 0; i < postfix.size(); ++i)
	{
		auto it = find(operators.begin(), operators.end(), postfix[i]);
		if (it == operators.end())
		{
			if (postfix[i] == ' ')
				continue;
			vector<char> digits;
			while (i < postfix.size() && postfix[i] != ' ')
			{
				digits.push_back(postfix[i]);
				++i;
			}
			stack.push(number_from_digits(digits));
		}
		else
		{
			int x;
			int y;
			switch (postfix[i]) {
			case '+':
				y = stack.top();
				stack.pop();
				x = stack.top();
				stack.pop();
				stack.push(x + y);
				break;
			case '-':
				y = stack.top();
				stack.pop();
				x = stack.top();
				stack.pop();
				stack.push(x - y);
				break;
			case '*':
				y = stack.top();
				stack.pop();
				x = stack.top();
				stack.pop();
				stack.push(x * y);
				break;
			case '/':
				y = stack.top();
				stack.pop();
				x = stack.top();
				stack.pop();
				stack.push(x / y);
				break;
			}
		}
	}
	return stack.top();
}

int calculate_infix(string infix)
{
	return calculate_postfix(infix_to_postfix(infix));
}





vector<char> operations = { '+','-','*','/'};


void possible_operations(vector<string>& v, string& number, string combination)//choosing means we are choosing the choosing-th operation, ops is the combination we chose up until now
{
	if (combination.size() == number.size() - 1)//choosing == combination.size()
	{
		string s;
		for (int i = 0; i < number.size() - 1; ++i)
		{
			s.push_back(number[i]);
			if (combination[i] != ' ')
				s.push_back(combination[i]);
		}
		s.push_back(number[number.size() - 1]);//the last one doesn't have an operation after it, so we consider it separately
		v.push_back(s);
		return;//backtrack when we can't choose anything else
	}
	//now we recursively call the function for all operations (including the nonexistent one)
	combination.push_back(' ');
	possible_operations(v, number, combination);//we chose ' '
	combination.pop_back();
	for (auto m : operations)//choose everything else
	{
		combination.push_back(m);
		possible_operations(v, number, combination);
		combination.pop_back();
	}
}


/*
FullyParenthesize(expression[1...n])

	result = {}

	// looking for operators
	for p = 1 to n do

		// binary operator; parenthesize LHS and RHS
		// parenthesize the binary operation
		if expression[p] is a binary operator then
			lps = FullyParenthesize(expression[1 ... p - 1])
			rps = FullyParenthesize(expression[p + 1 ... n])
			for each lp in lps do
				for each rp in rps do
					result = result U {"(" + lp + expression[p] + rp + ")"}

	// no binary operations <=> single variable
	if result == {} then
		result = {"(" + expression + ")")}

	return result
*/

vector<string> FullyParenthesize(string s, vector<string>& result)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (find(operations.begin(), operations.end(), s[i]) != operations.end())
		{
			vector<string> lps;
			FullyParenthesize(s.substr(0, i), lps);
			vector<string> rps;
			FullyParenthesize(s.substr(i + 1), rps);
			for (auto& lp : lps)
			{
				for (auto& rp : rps)
				{
					string str1 = "(";
					string str2 = ")";
					str1.append(lp);
					str1.push_back(s[i]);
					str1.append(rp);
					str1.append(str2);
					//cout << "(" << " o " << lp << " o " << s[i] << " o " << rp << " o " << str2 << " == " << str1 << endl;
					result.push_back(str1);
				}
			}
		}
	}
	if (result.size() == 0)
	{
		result.push_back(s);//not "(" + s + ")", that's redundant. we don't want (a)+(b)
	}
	return result;
}


void calculate_all(int analyse, int to_get)
{
	string number = to_string(analyse);
	vector<string> v;
	string temp;

	possible_operations(v, number, temp);
    vector<string> all_parenthesized;
	for (auto& m : v)
	{
        vector<string> result;
        vector<string> parenthesized = FullyParenthesize(m,result);
        for(auto& k : parenthesized)
        {
            all_parenthesized.push_back(k);
        }
    }
    for(auto& m : all_parenthesized)
    {
        cout << m << " == " << calculate_infix(m) << endl;
    }
}



int main()
{
	int analyse;
	int to_get;
	cout << "Input a number which needs to be analysed: ";
	cin >> analyse;
	cout << "\n\nInput the answer we should get: ";
	cin >> to_get;
	cout << "\n\n\n";
	vector<pair<string,double> answers = calculate_all(analyse, to_get);
    if(answer.size() == 0)
    {
        cout << "Cannot get " << to_get << " from these numbers." << endl;
        system("pause");
        return 0;
    }
    else
    {
        for(const auto& m : v)
        {
            cout << m.first << " == " << m.second << endl;
        }
        system("pause");
        return 0;
    }
}