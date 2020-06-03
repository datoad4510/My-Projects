#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <cassert>
using namespace std;

vector<vector<int>> twosum_nodupl(vector<int>& nums, int target)//time: O(nlogn), space: O(1)
{
	sort(nums.begin(), nums.end());
	int i = 0;
	int j = nums.size() - 1;
	int sum;
	vector<vector<int>> answer;
	//edge case when multiple target/2-s. is loop chatvale cherdeba roca nums[i] == nums[j]. amit winaswar vamowmebt iqneb mainc jamshi targetia
	if (target % 2 == 0 && count(nums.begin(), nums.end(), target / 2) > 1)
	{
		vector<int> v = { target / 2, target / 2 };
		answer.push_back(v);
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
			vector<int> v = { nums[i],nums[j] };
			answer.push_back(v);
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
	return answer;
}

vector<vector<int>> twosum_new(vector<int>& nums, int target)//time: O(nlogn), space: O(1))
{
	vector<vector<int>> res;
	int left = 0;
	int right = nums.size() - 1;
	while (left < right) {
		int sum = nums[left] + nums[right];
		if (sum == target) {
			vector<int> v;
			v.push_back(min(nums[left], nums[right]));
			v.push_back(max(nums[left], nums[right]));
			res.push_back(v);
			// de - dup
			while (left < right && nums[left] == nums[left + 1]) { ++left; }
			while (left < right && nums[right] == nums[right - 1]) { --right; }
			++left;
			--right;
		}
		else if (sum < target) {
			++left;
		}
		else {
			--right;
		}
	}
	return res;
}

vector<vector<int>> twosum_nodupl_hashmap(vector<int>& nums, int target)//time: O(n), space: O(n)
{
	set<pair<int,int>> answer;
	unordered_map<int, int> um;
	for (int i = 0; i < nums.size(); ++i)
	{
		auto it = um.find(nums[i]);//pirvelit edzebs
		if (it != um.end())
		{
			++it->second;
			continue;
		}
		else
		{
			um.insert(make_pair(nums[i], 0));
		}
	}
	for (int i = 0; i < nums.size(); ++i)
	{
		auto it = um.find(target - nums[i]);
		if (it == um.end())
			continue;
		if (it->first == nums[i])
		{
			if (it->second != 0)
			{
				answer.insert({ nums[i],nums[i] });
				continue;
			}
			else
			{
				continue;
			}
		}
		else
		{
			answer.insert({ min(nums[i],target - nums[i]), max(nums[i],target - nums[i]) });
		}
	}
	vector<vector<int>> matrix;
	auto it = answer.begin();
	while (it != answer.end())
	{
		vector<int> v = { it->first,it->second };
		matrix.push_back(v);
		++it;
	}
	return matrix;
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
		for(int j = 0; j < v[i].size() - 1; ++j)
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


vector<vector<int>> threesum_nodupl_hashmap(vector<int>& nums, int target)//time: O(n^2) mgoni. space: O(n), yoveli iteraciisas O(n) iqmneba da ishleba
{
	vector<vector<int>> answer;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i)
	{

		vector<int> temp;//yvela sameuls aqvs umciresi wevri. danarcheni ori magis marjvnivaa. amitom, yvela nums[i]-tvis
		//movdzebnot romeli sameulebis umciresia.
		if (i == nums.size() - 2 || i == nums.size() - 1)
			break;
		for (int k = i + 1; k < nums.size(); ++k)
			temp.push_back(nums[k]);

		vector<vector<int>> matrix = twosum_nodupl_hashmap(temp, target - nums[i]);
		for (int j = 0; j < matrix.size(); ++j)//complexity?
		{
			vector<int> v = matrix[j];
			v.push_back(nums[i]);
			answer.push_back(v);
		}
		while (i + 1 < nums.size() && nums[i] == nums[i + 1])
		{
			++i;
		}
	}
	return answer;
}

vector<vector<int>> threesum_nodupl(vector<int>& nums, int target)//time: O(n^2logn) mgoni. space: O(1)
{
	vector<vector<int>> answer;
	sort(nums.begin(), nums.end());
	for (int i = 0; i < nums.size(); ++i)
	{

		vector<int> temp;//yvela sameuls aqvs umciresi wevri. danarcheni ori magis marjvnivaa. amitom, yvela nums[i]-tvis
		//movdzebnot romeli sameulebis umciresia.
		if (i == nums.size() - 2 || i == nums.size() - 1)//make sure it returns the correct values for [1,2] and [1]
			break;
		for (int k = i + 1; k < nums.size(); ++k)
			temp.push_back(nums[k]);

		vector<vector<int>> matrix = twosum_nodupl(temp, target - nums[i]);
		for (int j = 0; j < matrix.size(); ++j)//complexity?
		{
			vector<int> v = matrix[j];
			v.push_back(nums[i]);
			answer.push_back(v);
		}

		while ( 0 < i && i < nums.size() && nums[i - 1] == nums[i])//tu gameorebebiani mimdevroba aris, sakmarisia
		{													//pirvelze vqnat es metodi. shemdegshi is isev is iqneba umciresi
															//da gameordeba winadan nawili
			++i;
		}//amis gamo vshvebit winas shemdeg
	}
	return answer;
}



int main()
{
	vector<int> v1 = { 21,2,34,5,11,-2,7,1,13,-1,1,1,6,6,6,6,3,3,3,3,4,4,4,0 };
	vector<int> v2 = { 1,1,1,2,2,5,-1,9,6,3,0,-8 };
	vector<int> v3 = {-1, 0, 1, 2, -1, -4 };
	vector<vector<int>> answer1 = twosum_nodupl(v1, 2);
	vector<vector<int>> answer15 = twosum_nodupl_hashmap(v1, 11);
	vector<vector<int>> answer2 = threesum_nodupl(v1, 2);
	vector<vector<int>> answer25 = threesum_nodupl_hashmap(v2, 3);
	vector<vector<int>> answer3 = threesum_nodupl(v3, 0);
	print_matrix(answer1);
	cout << "\n\n\n";
	print_matrix(answer15);
	cout << "\n\n\n";
	print_matrix(answer2);
	cout << "\n\n\n";
	print_matrix(answer25);
	cout << "\n\n\n";
	print_matrix(answer3);
	cout << "\n\n\n";
	for (auto m : v1)
		cout << m << " ";
	cout << "\n\n";
	system("pause");
}