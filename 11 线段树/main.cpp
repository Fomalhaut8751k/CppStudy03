#include<iostream>
#include<vector>

using namespace std;

// 线段树：实现y=ax+b的映射
class SegMentTree
{
public:
	SegMentTree(int n, vector<int>& num):
		tree(vector<int>((n << 2) + 1, 0)),
		tag(vector<pair<int, int>>((n << 2) + 1, { 1, 0 }))  // 懒标记初始化
	{
		a.push_back(0);
		a.insert(a.end(), num.begin(), num.end());
	}

	// push_up
	void push_up(int p)
	{
		tree[p] = tree[p << 1] + tree[p << 1 | 1];
	}

	// push_down
	void push_down(int p, int pl, int pr)
	{
		if (tag[p] != pair<int,int>(1, 0))
		{
			int a = tag[p].first, b = tag[p].second; 

			int ai = tag[p << 1].first, bi = tag[p << 1].second;
			tag[p << 1] = pair<int, int>(a * ai, a * bi + b);

			ai = tag[p << 1|1].first, bi = tag[p << 1|1].second;
			tag[p << 1|1] = pair<int, int>(a * ai, a * bi + b);

			tree[p << 1] = a * tree[p << 1] + b * pl;
			tree[p << 1 | 1] = a * tree[p << 1 | 1] + b * pr;

			tag[p] = pair<int, int>(1, 0);
		}
	}

	// build
	void build(int p, int pl, int pr)
	{
		if (pl == pr)
		{
			tree[p] = a[pl];
			return;
		}
		int mid = (pl + pr) >> 1;
		build(p << 1, pl, mid);
		build(p << 1 | 1, mid + 1, pr);
		push_up(p);
	}

	// update
	void update(int p, int pl, int pr, int L, int R, int a, int b)
	{
		if (L <= pl && pr <= R)
		{
			tree[p] = a * tree[p] + b * (pr - pl + 1);
			int ai = tag[p].first, bi = tag[p].second;
			tag[p] = pair<int, int>(a * ai, a * bi + b);
			return;
		}
		int mid = (pl + pr) >> 1;
		push_down(p, mid - pl + 1, pr - mid);
		if (L <= mid)
		{
			update(p << 1, pl, mid, L, R, a, b);
		}
		if (R > mid)
		{
			update(p << 1 | 1, mid + 1, pr, L, R, a, b);
		}
		push_up(p);
	}

	// query
	int query(int p, int pl, int pr, int L, int R)
	{
		if (L <= pl && pr <= R)
		{
			return tree[p];
		}
		int ans = 0;
		int mid = (pl + pr) >> 1;
		push_down(p, mid - pl + 1, pr - mid);
		if (L <= mid)
		{
			ans += query(p << 1, pl, mid, L, R);
		}
		if (R > mid)
		{
			ans += query(p << 1 | 1, mid + 1, pr, L, R);
		}
		return ans;
	}

private:
	vector<int> a;
	vector<int> tree;
	vector<pair<int, int>> tag;
};

int main()
{
	int n = 8;
	vector<int> nums = { 1, 4, 2, 8 ,5 , 7, 9, 3 };
	SegMentTree st(n, nums);
	st.build(1, 1, n);
	cout << st.query(1, 1, n, 2, 5) << endl;

	st.update(1, 1, n, 4, 6, 3, 4);
	cout << st.query(1, 1, n, 3, 5) << endl;

	st.update(1, 1, n, 2, 4, 2, 1);
	cout << st.query(1, 1, n, 2, 7) << endl;
	return 0;
}