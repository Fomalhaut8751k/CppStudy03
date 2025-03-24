#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main() {
    string line;
    getline(cin, line); // 读取整行输入，如 "1 2 3 4 5"

    stringstream ss(line);
    vector<int> vec;
    int num;
    while (ss >> num) {
        vec.push_back(num);
    }

    // 输出验证
    for (int x : vec) {
        cout << x << " ";
    }
    return 0;
}