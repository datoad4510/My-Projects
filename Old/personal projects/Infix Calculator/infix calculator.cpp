#include <string>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

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

int main()
{
    while(true) {
        cout << "Input an expression to calculate:\n\n";
        string input;
	    int output;
	    cin >> input;
	    output = calculate_infix(input);
	    cout << "\n" << input << " == " << output << "\n\n";
    }
	
}