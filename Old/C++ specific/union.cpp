#include <iostream>
using namespace std;

union employee 
{
	int number;
	struct pay
	{
		int pay_dollar;
		int pay_ruble;
	}pay;

}emp[1]; //მასივის ზომაა 1, მაგრამ რატომღაც ნებისმიერი რიცხვის ჩასმაც მუშაობს, სადაც არ არის არაფერი ჩაწერილი 0-ია

void change_dollar(employee& emp)
{	
	cin >> emp.pay.pay_dollar;
}

void change_ruble(employee& emp)
{
	cin >> emp.pay.pay_ruble;
}

int main()
{	
	int num,temp;
	cout << "Which employee?" << endl;
	cin >> num;
	cout << "Input 0 for dollar, anything else for ruble" << endl;
	cin >> temp;
	if (temp)
	{
		cout << "What should the pay be?" << endl;
		change_ruble(emp[num]);
		cout << "Employee number " << num << " has a pay of " << emp[num].pay.pay_ruble << " rubles." << endl;
	}
	else
	{
		cout << "What should the pay be?" << endl;
		change_dollar(emp[num]);
		cout << "Employee number " << num << " has a pay of " << emp[num].pay.pay_dollar << " dollars." << endl;
	} 
	system("pause");
}
