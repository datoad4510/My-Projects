#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <map>
#include <cassert>
#include <algorithm>
#include <stack>
#include <algorithm>
#include "Fractions.h"
using namespace std;//we can further optimise the calculate_all function by processing as we come across the parenthesized expressions. get combination -> parenthesize it-> calculate infix and check -> get next parenthesisation etc. (doesn't matter really, we'll just see the progress as it works instead of waiting for everything to be calculated)
//this will also be a huge memory improvement ^^^^

//helper functions, makes the code more verbose but easier to implement algorithms
fraction to_fraction(int x)
{
	fraction temp(x, 1);
	return temp;
}

fraction add(int x, fraction y)
{
	fraction temp(x, 1);
	return temp + y;
}
fraction add(fraction x, int y)
{
	fraction temp(y, 1);
	return x + temp;
}
fraction add(int x, int y)
{
	fraction temp(x + y,1);
	return temp;
}
fraction add(fraction x, fraction y)
{
	return x + y;
}

fraction subtract(int x, fraction y)
{
	fraction temp(x, 1);
	return temp - y;
}
fraction subtract(fraction x, int y)
{
	fraction temp(y, 1);
	return x - temp;
}
fraction subtract(int x, int y)
{
	fraction temp(x - y, 1);
	return temp;
}
fraction subtract(fraction x, fraction y)
{
	return x - y;
}

fraction multiply(int x, fraction y)
{
	fraction temp(x, 1);
	return temp * y;
}
fraction multiply(fraction x, int y)
{
	fraction temp(y, 1);
	return x * temp;
}
fraction multiply(int x, int y)
{
	fraction temp(x*y, 1);
	return temp;
}
fraction multiply(fraction x, fraction y)
{
	return x * y;
}

fraction divide(int x, fraction y)
{
	fraction temp(x, 1);
	return temp / y;
}
fraction divide(fraction x, int y)
{
	fraction temp(y, 1);
	return x / temp;
}
fraction divide(int x, int y)
{
	fraction temp(x, y);
	return temp;
}
fraction divide(fraction x, fraction y)
{
	return x / y;
}

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
		number += x * (digits[i] - '0');
		x *= 10;
	}
	return number;
}

bool calculate_postfix(string postfix, fraction& x)
{
	stack<fraction> stack;
	for (int i = 0; i < postfix.size(); ++i)//???????????? why doesnt this work as a for loop ????????????? imitoro jer umatebs da mere amowmebs while. for kidev piriqit!!
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
			stack.push(to_fraction(number_from_digits(digits)));
		}
		else
		{
			fraction x;
			fraction y;
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
				if (y.get_Num() == 0)
				{
					return false; //division by zero
				}
				stack.pop();
				x = stack.top();
				stack.pop();
				stack.push(x / y);
				break;

			}
		}
	}
	x = stack.top();
	return true;
}

bool calculate_infix(string infix, fraction& x)//bool is 1 if executed (e.g. no division by zero)
{
	if (calculate_postfix(infix_to_postfix(infix), x))
	{
		return true;
	}
	else
	{
		return false;
	}
}





vector<char> operations = { '+','-','*','/' };


void possible_operations(vector<string>& v, vector<string>& number, string combination)//choosing means we are choosing the choosing-th operation, ops is the combination we chose up until now
{//this will negatively affect readability though
	if (combination.size() == number.size() - 1)//choosing == combination.size()
	{
		string s;
		for (int i = 0; i < number.size() - 1; ++i)
		{
			s.append(number[i]);
			if (combination[i] != ' ')
				s.push_back(combination[i]);
		}
		s.append(number[number.size() - 1]);//the last one doesn't have an operation after it, so we consider it separately
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


bool calculate_all(vector<string> analyse, int to_get)
{
	vector<string> v;
	string temp;

	possible_operations(v, analyse, temp);
	vector<string> all_parenthesized;
	for (auto& m : v)
	{
		vector<string> result;
		vector<string> parenthesized = FullyParenthesize(m, result);
		for (auto& k : parenthesized)
		{
			all_parenthesized.push_back(k);
		}
	}
	bool found = false;
	for (auto& m : all_parenthesized)
	{
		fraction calculated_expression;
		if (calculate_infix(m, calculated_expression) && calculated_expression == to_get)
		{
			found = true;
			cout << m << " == " << calculated_expression.get_Num() << endl;
		}
		else
		{
			continue;
		}
	}
	return found;
}

//.................after this everything is for calculating just one.............................//

vector<string> FullyParenthesize_one(string s,vector<string>& result,const int& original_size,const int& to_get)//it's optimised!!
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (find(operations.begin(), operations.end(), s[i]) != operations.end())//"last binary operator" is s[i]
		{
			vector<string> lps;
			FullyParenthesize_one(s.substr(0, i), lps, original_size, to_get);
			vector<string> rps;
			FullyParenthesize_one(s.substr(i + 1), rps, original_size, to_get);
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
					if(s.size() != original_size)
					{
						result.push_back(str1);
					}
					else
					{
						fraction exp;
						if (calculate_infix(str1, exp) && exp == to_get)
						{
							cout << str1 << " == " << exp.get_Num() << endl;
							vector<string> nul = { "N" };
							return nul;
						}
					}
					
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

void possible_operations_one(vector<string>& number, string combination, int& to_get, bool& found)
{
	if (found == true)
		return;
	if (combination.size() == number.size() - 1)
	{
		string s;
		for (int i = 0; i < number.size() - 1; ++i)
		{
			s.append(number[i]);
			if (combination[i] != ' ')
				s.push_back(combination[i]);
		}
		s.append(number[number.size() - 1]);//the last one doesn't have an operation after it, so we consider it separately

		//we have a combination ready. immediatelly process it!!
		vector<string> temp;
		int size = s.size();
		temp = FullyParenthesize_one(s, temp, size, to_get);
		if (temp.size() == 1 && temp[0] == "N")
			found = true;
		return;//backtrack when we can't choose anything else
	}
	//now we recursively call the function for all operations (including the nonexistent one)
	combination.push_back(' ');
	possible_operations_one(number, combination, to_get, found);//we chose ' '
	combination.pop_back();
	for (auto m : operations)//choose everything else
	{
		combination.push_back(m);
		possible_operations_one(number, combination, to_get, found);
		combination.pop_back();
	}
}


bool calculate_one(vector<string> analyse, int to_get)//we scan make this faster if we alternate combination + parenthesize + calculate + repeat instead of doing all the same time each
{
	bool found = false;
	string combination;
	possible_operations_one(analyse, combination, to_get, found);
	return found;
	cout << "\n\n\n";
}

void input_to_vector(const string& s, vector<string>& v)
{
	for (int i = 0; i < s.size(); ++i)
	{
		if (s[i] == ' ')
			continue;
		string str;
		while (i < s.size() && s[i] != ' ')
		{
			str.push_back(s[i]);
			++i;
		}
		v.push_back(str);
	}
}

bool countdown(vector<string> analyse, int to_get)
{
	vector<string> temp = analyse;
	bool found = false;
	next_permutation(analyse.begin(), analyse.end());
	while (analyse != temp)
	{
		found = calculate_all(analyse, to_get);
		next_permutation(analyse.begin(), analyse.end());
	}
	return found;
}

int main()//when it cant find anything doesnt say!
{
	vector<string> analyse;
	int to_get;
	string numbers;
	int choose = 0;
	while (choose != 1 && choose != 2 && choose != 3)
	{
		cout << "1. Find all answers" << "\n\n2.Find an answer" << "\n\n3.Countdown problem (meaning permutations are allowed, all answers)" << "\n\nChoose either 1, 2 or 3 (input)\n\n";
		cin >> choose;
		system("cls");
	}
	if (choose == 1)
	{
		cout << "Input numbers which need to be analysed (put space between them): ";
		cin.ignore();
		getline(cin, numbers);
		input_to_vector(numbers, analyse);
		cout << "\n\nInput the answer we should get: ";
		cin >> to_get;
		cout << "\n\n\n";
		bool found = calculate_all(analyse, to_get);
		if (found == false)
		{
			cout << "Answer doesn't exsist\n\n";
		}
		system("pause");
	}
	else if (choose == 2)
	{
		cout << "Input numbers which need to be analysed (put space between them): ";
		cin.ignore();
		getline(cin, numbers);
		input_to_vector(numbers, analyse);
		cout << "\n\nInput the answer we should get: ";
		cin >> to_get;
		cout << "\n\n\n";
		bool found = calculate_one(analyse, to_get);
		if (found == false)
		{
			cout << "Answer doesn't exsist\n\n";
		}
		system("pause");
	}
	else if (choose == 3)
	{
		cout << "Input numbers which need to be analysed (put space between them): ";
		cin.ignore();
		getline(cin, numbers);
		input_to_vector(numbers, analyse);
		cout << "\n\nInput the answer we should get: ";
		cin >> to_get;
		cout << "\n\n\n";
		bool found = countdown(analyse, to_get);
		if (found == false)
		{
			cout << "Answer doesn't exsist\n\n";
		}
		system("pause");
	}
}