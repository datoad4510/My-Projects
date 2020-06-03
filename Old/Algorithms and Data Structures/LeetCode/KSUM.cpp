#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> ksum(vector<int>& nums, int k, int target, int idx = 0)
{
	//if (is_sorted(nums.begin(), nums.end()) == 0)
	//	sort(nums.begin(), nums.end());
	vector<vector<int>> matrix;

	if (k == 1)
	{
		if (binary_search(nums.begin() + idx, nums.end(), target))
		{
			vector<int> v = { target };
			matrix.push_back(v);
			return matrix;
		}
	}
	if (k == 2)
	{
		int i = idx;
		int j = nums.size() - 1;
		int sum;
		//edge case when multiple target/2-s. is loop chatvale cherdeba roca nums[i] == nums[j]. amit winaswar vamowmebt iqneb mainc jamshi targetia
		if (target % 2 == 0 && count(nums.begin() + idx, nums.end(), target / 2) > 1)
		{
			vector<int> v = { target / 2, target / 2 };
			matrix.push_back(v);
		}
		while (i != j)
		{

			if (nums[i] == nums[i + 1])
			{
				++i;
				continue;
			}
			if (nums[j] == nums[j - 1])
			{
				--j;
				continue;
			}
			//aqamde duplicatebis moshorebaa. tu gvinda rom iyos duplikatebi, n^2 double loop sajiroa
			//tu sawyis vectorshi gvinda mati indexebi, axal wyvilebis veqtors gavaketebt sadac {nums[i],i} iqneba da davalagebt first-it
			//shemdeg ki prosto indexebs chavagdebt.
			sum = nums[i] + nums[j];
			if (sum == target)
			{
				vector<int> v = { min(nums[i],nums[j]), max(nums[i],nums[j]) };
				matrix.push_back(v);
				++i;//an es an --j gvinda rom rame sheicvalos
				continue;
			}
			if (sum < target)
			{
				++i;
				continue;
			}
			else //sum > target
			{
				--j;
				continue;
			}

		}
		return matrix;
	}
	else
	{
		for (int i = idx; i < nums.size(); ++i)
		{
			int count = 1;
			if (nums.size() - i < k)//make sure it returns the correct values for [1,2] and [1]
				break;
			
			vector<vector<int>> old_matrix = ksum(nums, k - count, target - nums[i], i + 1);
			for (int j = 0; j < old_matrix.size(); ++j)//complexity?
			{
				sort(old_matrix[j].begin(), old_matrix[j].end());
				vector<int> v;
				v.push_back(nums[i]);
				for (const auto& m : old_matrix[j])
					v.push_back(m);
				matrix.push_back(v);
			}

			while (i + 1 < nums.size() && nums[i] == nums[i + 1])//tu gameorebebiani mimdevroba aris, sakmarisia
			{													//pirvelze vqnat es metodi. shemdegshi is isev is iqneba umciresi
																//da gameordeba winadan nawili
				++i;
			}//amis gamo vshvebit winas shemdeg
			++count;
		}
		return matrix;
	}
}

void print_matrix(vector<vector<int>> v)
{
	if (v.size() == 0) {
		cout << "{ }" << endl;
		return;
	}
	cout << "{ ";
	for (int i = 0; i < v.size() - 1; ++i)
	{
		cout << "[ ";
		for (int j = 0; j < v[i].size() - 1; ++j)
		{
			cout << v[i][j] << " , ";
		}
		cout << v[i][v[i].size() - 1];
		cout << " ] , ";
	}
	cout << "[ ";
	for (int j = 0; j < v[v.size() - 1].size() - 1; ++j)
	{
		cout << v[v.size() - 1][j] << " , ";
	}
	cout << v[v.size() - 1][v[v.size() - 1].size() - 1];
	cout << " ] }" << endl;
}

int main()
{
	vector<int> v1 = { 21,2,34,5,11,-2,7,1,13,-1,1,1,6,6,6,6,3,3,3,3,4,4,4,0 };
	sort(v1.begin(), v1.end());
	vector<vector<int>> answer1 = ksum(v1, 6, 2);
	print_matrix(answer1);
	cout << "\n\n\n";
	system("pause");
}
