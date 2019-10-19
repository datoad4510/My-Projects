#include <iostream>
#include <new>
using namespace std;
const int N = 3, M = 4;
int main()
{
	int* p = new(nothrow) int(50);  //new operatori ert mtel ricxvs gaunawilebs dinamikur mexsierebas da masshi chawers 50-s, xolo p-s mianichebs mis misamarts.
	if (p == nullptr)
	{
		cout << "Memory allocation failed." << endl;
		system("pause"); //return 0;
	}
	delete p;
	int* q = new(nothrow) int[5]; //q utitebs 5 sigrdzis masivis pirvel elementze. aq q aris dinamikuri masivis saxeli. masivis saxeli xom mis pirvel elementze misamarti aris. es daaxloebit igivea, rac int q[5];
	cout << q[2]; //q[2] iqneba meore elementi am masivis. q[2] == (q+2)*
	if (q == nullptr)
	{
		cout << "Memory allocation failed." << endl;
		system("pause"); //return 0;
	}
	delete[]q;

	int ** A = new (nothrow) int*[N];    // int *ptr[5] aris masivi shemdgari 5 pointerisgan intze. A aris pointeri N elementisgan shemdgari int pointerebis masivisa, anu pointeri N=0-ze. Mashin A[i] iqneba N=i-ze pointeri. amas vaketebt inicializebis gareshe, inicializebas vaketebt shemdeg xazshi.
	for (int i = 0; i < N; i++)
		A[i] = new (nothrow) int[M]; // N elementisgan shemdgari masivis i-uri elementi iyos pointeri M elementisgan shemdgar intebis masivze(inicializeba).
	int i, j;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			A[i][j] = i + j;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	for (int i = 0; i < N; i++)
		delete[] A[i];
	delete[] A;
	A = nullptr;


	max = Array[0];
	for (int i = 1; i < N; ++i)
		if (Array[i] == max) counter++;   //ramdeni maximaluri elementia, algoritmi
		else if (Array[i] > max) {
			max = Array[i];
			counter = 1;
		}
}