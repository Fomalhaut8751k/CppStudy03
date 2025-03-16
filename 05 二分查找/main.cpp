#include<iostream>
#include "utils.hpp"

using namespace std;

int main() {

	int arr_int[10] = { 12,17,22,29,36,44,59,72,79,91 };

	cout << BinarySearch(arr_int, 10, 57) << endl;
	cout << BinarySearch(arr_int, 0, 9, 59) << endl;

	system("pause");
	return 0;
}