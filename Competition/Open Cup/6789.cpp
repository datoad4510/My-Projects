#include <vector>
#include <string>
#include <fstream>
using namespace std;

inline bool check(int& i, int& j, vector<string>& matrix, int& minimum)
{
	char x = matrix[i][j];
	char y = matrix[matrix.size() - i - 1][matrix[0].size() - j - 1];
	if ((x == '6' && y == '9') || (x == '9' && y == '6') || (x == '8' && y == '8'))
	{
		return true;
	}
	else if ((x == '6' && y == '6') || (x == '9' && y == '9') || (x == '7' && y == '7'))
	{
		++minimum;
		return true;
	}
	else
		return false;
}


int main()
{
	int dummy1;
	int dummy2;
	ifstream ifs("Standard input.txt");
	ofstream ofs("Standard output.txt");
	ifs >> dummy1;
	ifs >> dummy2;
	vector<string> matrix;
	string temp;
	while (ifs >> temp)
	{
		matrix.push_back(temp);
	}
	int N = matrix.size();
	int M = matrix[0].size();
	int minimum = 0;
	if (N % 2 == 1 && M % 2 == 1)//checking for the middle card if it exists
	{
		if (matrix[N / 2][M / 2] != '8')
		{
			ofs << -1 << endl;
			return 0;
		}
	}
	for (int i = 0; i < N / 2; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (!check(i, j, matrix, minimum))
			{
				ofs << -1 << endl;
				return 0;
			}
		}
	}

	if (N % 2 == 1)
	{
		int i = N / 2;
		int border = M / 2;
		for (int j = 0; j < border; ++j)
		{
			if (!check(i, j, matrix, minimum))
			{
				ofs << -1 << endl;
				return 0;
			}
		}
	}
	ofs << minimum << endl;
}