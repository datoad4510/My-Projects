#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
	int input,temp = 1; // inicializeba sachiroa while-is pirobistvis
	string ataseuli , aseuli, ateuli , erteuli;
	cout << "I = 1 , V = 5 , X = 10 , L = 50 , C = 100 , D = 500 , M = 1000.\n\n\n";
	cout << "Please input a decimal number from 1 to 3999: "; // eseti wesia romaulshi, rom 3-ze meti ertnairi simbolo zedized ar iwereba, amitomac 3999 yvelaze didi ricxvia romlis gamosaxvac sheidzleba
	vector<int> v;
	cin >> input;
	if (input > 0 && input < 4000)
	{
		while (temp != 0)
		{	
			temp = input % 10;
			v.push_back(temp);
			input /= 10;
			temp = input % 10; // meored imitom davwere, rom axali mnishvneloba sheamowmos, torem ise vectorshi zedmeti 0-iani darcheba
		}
		for (int i = 0; i < 4; i++)
		{
			v.push_back(0); // es sachiroa imistvis, rom tu vectors ataseuli, aseuli an ateuli ar gaachnia, mis magivrad 0 chaiweros
		}
		
		switch (v[3])
		{
		case 0: ataseuli = ""; break;
		case 1: ataseuli = "M"; break;
		case 2: ataseuli = "MM"; break;
		case 3: ataseuli = "MMM"; break;
		}

		switch (v[2])
		{
		case 0: aseuli = ""; break;
		case 1: aseuli = "C"; break; 
		case 2: aseuli = "CC"; break;
		case 3: aseuli = "CCC"; break;
		case 4: aseuli = "CD"; break;
		case 5: aseuli = "D"; break;
		case 6: aseuli = "DC"; break;
		case 7: aseuli = "DCC"; break;
		case 8: aseuli = "DCCC"; break;
		case 9: aseuli = "CM"; break; 
		}

		switch (v[1])
		{
		case 0: ateuli = ""; break;
		case 1: ateuli = "X"; break;
		case 2: ateuli = "XX"; break;
		case 3: ateuli = "XXX"; break;
		case 4: ateuli = "XL"; break;
		case 5: ateuli = "L"; break;
		case 6: ateuli = "LX"; break;
		case 7: ateuli = "LXX"; break;
		case 8: ateuli = "LXXX"; break;
		case 9: ateuli = "XC"; break;
		}

		switch (v[0])
		{
		case 0: erteuli = ""; break;
		case 1: erteuli = "I"; break;
		case 2: erteuli = "II"; break;
		case 3: erteuli = "III"; break;
		case 4: erteuli = "IV"; break;
		case 5: erteuli = "V"; break;
		case 6: erteuli = "VI"; break;
		case 7: erteuli = "VII"; break;
		case 8: erteuli = "VIII"; break;
		case 9: erteuli = "IX"; break;
		}
		cout << ataseuli << aseuli << ateuli << erteuli << "\n\n\n";
	}
	else
	{
	
		cout << "Invalid input." << endl;
	}
	system("pause");

}