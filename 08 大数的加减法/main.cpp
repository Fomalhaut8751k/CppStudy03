#include<iostream>
#include<algorithm>
#include<string>
#include<functional>

using namespace std;

/*
	�����ֵ�λ�����࣬�ൽ�������ʹ洢����ʱ
	���ַ������洢

	��װһ������������str

	��ӣ�������λ��ʼ������������ӣ����������ڵ���10���ͽ�λ��
	���ȫ��������Ȼ��λ����������ַ���ǰ�Ӹ�'1'

	��������Ҫ�����жϼ����ͱ������Ĵ�С��Ҫ��֤�������ľ���ֵ���ڼ����ľ���ֵ
		���ж�����λ���ȣ����ľ���ֵ��
		���������ȣ��������ұ������Դ��ж�
		���ܽ������ǰ���㣬Ӧ��ɾȥ
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

// ��ӡ����
ostream& operator<<(ostream& cout, const BigInt& src)
{
	cout << src.strDigit;
	return cout;
}

// �ײ�ļӷ��㷨
string Myadd(string str1, string str2)
{
	// �����ַ����ĳ��ȣ�����ǰ��ķ���λ-
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
		result = '1' + result;  // ��λ
	return result;
}
// �ײ�ļ����㷨
string Myminus(string str1, string str2)
{
	// �����ַ����ĳ��ȣ�����ǰ��ķ���λ
	int len_str1 = (int)str1.length();
	int len_str2 = (int)str2.length();

	// �ж��Ƿ��Ǹ������ǵĻ�Ϊ1
	int p1 = 0;
	int p2 = 0;

	if (str1[0] == '-')
		p1 = 1;
	if (str2[0] == '-')
		p2 = 1;

	// �����Ľ��
	string result;

	int label_positive = 1;  // �жϱ������ͼ����ľ���ֵ��С������������֤�������ľ���ֵ
	                         // ���ڼ����ľ���ֵ

	int index = 0; 
	int backward = 0;  // ��λ����

	// �жϾ���ֵ��С
	// ���жϳ���(����������)�����ľ���ֵ��
	if (len_str1 - p1 > len_str2 - p2)
	{
		label_positive = 1;
	}
	else if (len_str1 - p1 < len_str2 - p2)
	{
		label_positive = 0;
	}
	else
	{	// ����������
		// ��������һ��һ���Ƚ�
		while (len_str1 - p1 >= index)
		{
			if (str1[p1 + index] > str2[p2 + index])  // ������ > ����
			{
				// ˵������������ֵ���ڼ���
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

	// ��������
	auto swapfunc = [](int& a, int& b)->void
	{
		int tmp = a;
		a = b;
		b = tmp;
	};

	// �Ƿ񽻻��ı�־
	bool swapLabel = false;

	if (label_positive == 0)  // ����������ľ���ֵ���ڼ����ľ���ֵ���ͽ��н���
	{
		string strtmp = str1;
		str1 = str2;
		str2 = strtmp;

		swapfunc(p1, p2);  // �����Ƿ��Ǹ���������ҲҪ���н���
		swapfunc(len_str1, len_str2);

		swapLabel = true;
	}

	//cout << str1 << " " << str2 << " " << p1 << " " << p2 << " " << len_str1 << " " << len_str2 << endl;

	// �������
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
	// ����ӿ�����Ҫ��󲹳��λ��ͬ�����������ǿ��ܳ��ֶ����1ǰ����

	// ǰ��������
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

	// �Ǹ��� - �Ǹ�����
	// label_positive == 0 ��Ե�һ��������������ľ���ֵС�ڼ����ģ������Ӧ��С��0
	// ���� - ������
	// p1+p2==2��ʾ���������Ǹ�������Եڶ��������������Ǹ�������ӽ���϶��Ǹ���
	// ���� + �Ǹ������Ǹ��� + ������
	// ͨ��operator+�����ã���֤�������str1�ǷǸ�����str2�Ǹ������൱�ڼ���
	// �������Ҫ������˵�����������ڼ���������
	if (label_positive == 0 or (p1 + p2 == 2))
	{
		resultStr = "-" + resultStr;
	}
	return resultStr;
}

// ��������
BigInt operator-(const BigInt& src1, const BigInt& src2)
{	
	// �Ǹ��� - �Ǹ���
	if(src1.strDigit[0] != '-' && src2.strDigit[0] != '-')
		return BigInt(Myminus(src1.strDigit, src2.strDigit));

	// ���� - �Ǹ���
	if (src1.strDigit[0] == '-' && src2.strDigit[0] != '-')
	{
		return BigInt('-' + Myadd(src2.strDigit, src1.strDigit));
	}
		
	// �Ǹ��� - ����
	if (src1.strDigit[0] != '-' && src2.strDigit[0] == '-')
	{
		return BigInt(Myadd(src1.strDigit, src2.strDigit));
	}

	// ���� - ����
	if (src1.strDigit[0] == '-' && src2.strDigit[0] == '-')
		return BigInt(Myminus(src1.strDigit, src2.strDigit));

	return BigInt(" ");
}

// �ӷ�����
BigInt operator+(const BigInt& src1, const BigInt& src2)
{
	// �Ǹ��� + �Ǹ���
	if (src1.strDigit[0] != '-' && src2.strDigit[0] != '-')
		return BigInt(Myadd(src1.strDigit, src2.strDigit));

	// ���� + �Ǹ���
	if (src1.strDigit[0] == '-' && src2.strDigit[0] != '-')
	{
		return BigInt(Myminus(src2.strDigit, src1.strDigit));
	}

	// �Ǹ��� + ����
	if (src1.strDigit[0] != '-' && src2.strDigit[0] == '-')
	{
		return BigInt(Myminus(src1.strDigit, src2.strDigit));
	}

	// ���� + ����
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