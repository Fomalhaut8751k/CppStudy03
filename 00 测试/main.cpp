#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	cout << '4' - '0' << endl;
	int arr[4] = { 0 };
	int index = 0;

	vector<int> vec = { 1, 2, 4, 5 };
	while (!vec.empty())
	{
		auto it = vec.end();
		arr[index] = *(--it);
		index++;
		vec.pop_back();
	}

	for (int i = 0; i < 4; ++i)
	{
		cout << arr[i] << " ";
	}cout << endl;
	
	cout << (-123 % 10) / 1 << endl;
	cout << (-123 % 100) / 10 << endl;
	cout << (-123 % 1000) / 100 << endl;

	return 0;
}