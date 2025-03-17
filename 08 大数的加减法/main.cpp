#include<iostream>
#include<algorithm>
#include<string>
#include<functional>

using namespace std;

/*
	当数字的位数过多，多到内置类型存储不下时
	用字符串来存储

	封装一函数，接收俩str

	相加：从数字位开始，从右往左相加，如果结果大于等于10，就进位，
	如果全部加完依然进位，就在输出字符串前加个'1'

	减法：需要额外判断减数和被减数的大小，要保证被减数的绝对值大于减数的绝对值
		先判断数字位长度，长的绝对值大
		如果长度相等，从左向右遍历，以此判断
		可能结果会有前置零，应该删去
*/

class BigInt
{
public:
	BigInt(string str) :strDigit(str) {};
	
private:
	string strDigit;
	friend ostream& operator<<(ostream& cout, const BigInt& src);
	friend BigInt operator+(const BigInt& src1, const BigInt& src2);
	friend BigInt operator-(const BigInt& src1, const BigInt& src2);
};

// 打印函数
ostream& operator<<(ostream& cout, const BigInt& src)
{
	cout << src.strDigit;
	return cout;
}

// 底层的加法算法
string Myadd(string str1, string str2)
{
	// 两个字符串的长度，包括前面的符号位-
	int len_str1 = (int)str1.length();
	int len_str2 = (int)str2.length();

	int p1 = 0;
	int p2 = 0;

	if (str1[0] == '-')
		p1 = 1;
	if (str2[0] == '-')
		p2 = 1;

	string result;

	int index = 1;
	int forward = 0;
	while (len_str1 - p1 >= index || len_str2 - p2 >= index)
	{
		int bit_1 = 0; int bit_2 = 0;
		if (len_str1 - p1 >= index)
			bit_1 = str1[len_str1 - index] - '0';
		if (len_str2 - p2 >= index)
			bit_2 = str2[len_str2 - index] - '0';

		int bit_s = bit_1 + bit_2 + forward;
		if (bit_s >= 10)
		{
			bit_s -= 10;
			forward = 1;
		}
		else
		{
			forward = 0;
		}

		result = (char)(bit_s + 48) + result;
		index++;
	}
	if (forward == 1)
		result = '1' + result;  // 进位
	return result;
}
// 底层的减法算法
string Myminus(string str1, string str2)
{
	// 两个字符串的长度，包括前面的符号位
	int len_str1 = (int)str1.length();
	int len_str2 = (int)str2.length();

	// 判断是否是负数，是的话为1
	int p1 = 0;
	int p2 = 0;

	if (str1[0] == '-')
		p1 = 1;
	if (str2[0] == '-')
		p2 = 1;

	// 初步的结果
	string result;

	int label_positive = 1;  // 判断被减数和减数的绝对值大小，后续调整保证被减数的绝对值
	                         // 大于减数的绝对值

	int index = 0; 
	int backward = 0;  // 进位符号

	// 判断绝对值大小
	// 先判断长度(不包括符号)，长的绝对值大
	if (len_str1 - p1 > len_str2 - p2)
	{
		label_positive = 1;
	}
	else if (len_str1 - p1 < len_str2 - p2)
	{
		label_positive = 0;
	}
	else
	{	// 如果长度相等
		// 从左往右一个一个比较
		while (len_str1 - p1 >= index)
		{
			if (str1[p1 + index] > str2[p2 + index])  // 被减数 > 减数
			{
				// 说明被减数绝对值大于减数
				label_positive = 1;
				break;
			}
			else if (str1[p1 + index] < str2[p2 + index])
			{
				label_positive = 0;
				break;
			}
			index++;
		}
	}

	//cout << label_positive << endl;

	// 交换函数
	auto swapfunc = [](int& a, int& b)->void
	{
		int tmp = a;
		a = b;
		b = tmp;
	};

	// 是否交换的标志
	bool swapLabel = false;

	if (label_positive == 0)  // 如果被减数的绝对值大于减数的绝对值，就进行交换
	{
		string strtmp = str1;
		str1 = str2;
		str2 = strtmp;

		swapfunc(p1, p2);  // 包括是否是负数，长度也要进行交换
		swapfunc(len_str1, len_str2);

		swapLabel = true;
	}

	//cout << str1 << " " << str2 << " " << p1 << " " << p2 << " " << len_str1 << " " << len_str2 << endl;

	// 相减代码
	index = 1;
	while (len_str1 - p1 >= index || len_str2 - p2 >= index)
	{
		//cout << len_str1 - index << " " << len_str2 - index  << endl;
		int bit_1 = 0; int bit_2 = 0;
		if(len_str1 - p1 >= index)
			bit_1 = str1[len_str1 - index] - '0';
		if (len_str2 - p2 >= index)
			bit_2 = str2[len_str2 - index] - '0';

		//cout << str1[len_str1 - index] << " " << str2[len_str2 - index] << endl;

		int bit_s = (bit_1 - bit_2) - backward;
		if (bit_s < 0)
		{
			bit_s += 10;
			backward = 1;
		}
		else
		{
			backward = 0;
		}

		result = (char)(bit_s + 48) + result;
		index++;
	}
	// 与相加可能需要最后补充进位不同，相减的情况是可能出现多余的1前置零

	// 前置零清理
	string resultStr;
	index = 0;
	int i = 0;
	for(; i < result.length(); i++)
	{
		if (result[i] != '0')
		{
			index++;
		}
		if (result[i] == '0' && index < 1)
		{
			continue;
		}
		resultStr += result[i];
	}

	// 非负数 - 非负数：
	// label_positive == 0 针对第一种情况，被减数的绝对值小于减数的，结果就应该小于0
	// 负数 - 负数：
	// p1+p2==2表示两个数都是负数，针对第二种情况，如果都是负数，相加结果肯定是负数
	// 负数 + 非负数，非负数 + 负数：
	// 通过operator+来调用，保证传入参数str1是非负数，str2是负数，相当于减法
	// 如果不需要交换，说明被减数大于减数，即正
	if (label_positive == 0 or (p1 + p2 == 2))
	{
		resultStr = "-" + resultStr;
	}
	return resultStr;
}

// 减法函数
BigInt operator-(const BigInt& src1, const BigInt& src2)
{	
	// 非负数 - 非负数
	if(src1.strDigit[0] != '-' && src2.strDigit[0] != '-')
		return BigInt(Myminus(src1.strDigit, src2.strDigit));

	// 负数 - 非负数
	if (src1.strDigit[0] == '-' && src2.strDigit[0] != '-')
	{
		return BigInt('-' + Myadd(src2.strDigit, src1.strDigit));
	}
		
	// 非负数 - 负数
	if (src1.strDigit[0] != '-' && src2.strDigit[0] == '-')
	{
		return BigInt(Myadd(src1.strDigit, src2.strDigit));
	}

	// 负数 - 负数
	if (src1.strDigit[0] == '-' && src2.strDigit[0] == '-')
		return BigInt(Myminus(src1.strDigit, src2.strDigit));

	return BigInt(" ");
}

// 加法函数
BigInt operator+(const BigInt& src1, const BigInt& src2)
{
	// 非负数 + 非负数
	if (src1.strDigit[0] != '-' && src2.strDigit[0] != '-')
		return BigInt(Myadd(src1.strDigit, src2.strDigit));

	// 负数 + 非负数
	if (src1.strDigit[0] == '-' && src2.strDigit[0] != '-')
	{
		return BigInt(Myminus(src2.strDigit, src1.strDigit));
	}

	// 非负数 + 负数
	if (src1.strDigit[0] != '-' && src2.strDigit[0] == '-')
	{
		return BigInt(Myminus(src1.strDigit, src2.strDigit));
	}

	// 负数 + 负数
	if (src1.strDigit[0] == '-' && src2.strDigit[0] == '-')
		return BigInt("-" + Myadd(src1.strDigit, src2.strDigit));

	return BigInt(" ");
}

int main()
{
	BigInt a("8");
	BigInt b("-27");
	BigInt c("18");
	BigInt d("-7");

	cout << a << " + " << b << " = " << a + b << endl;
	cout << a << " + " << c << " = " << a + c << endl;
	cout << a << " + " << d << " = " << a + d << endl;
	cout << b << " + " << c << " = " << b + c << endl;
	cout << b << " + " << d << " = " << b + d << endl;
	cout << c << " + " << d << " = " << c + d << endl;

	cout << a << " -  " << b << " = " << a - b << endl;
	cout << a << " - " << c << " = " << a - c << endl;
	cout << a << " - " << d << " = " << a - d << endl;
	cout << b << " - " << c << " = " << b - c << endl;
	cout << b << " - " << d << " = " << b - d << endl;
	cout << c << " - " << d << " = " << c - d << endl;
 
	return 0;
}