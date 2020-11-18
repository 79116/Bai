/*
Manacher. Hashing, Greedy
*/

#include<bits/stdc++.h>

using namespace std;
#define int long long
const int mod = 1e9 + 7;

int n, m;

vector<vector<char> > flip(vector<vector<char> > tb, int Row, int Col)
{
	vector<vector<char> > ftb(Col + 5, vector<char> (Row + 5)); 
	for(int r = 1; r <= Row; r++) for(int c = 1; c <= Col; c++) ftb[c][r] = tb[r][c];
	return ftb;
}

int solve(vector<vector<char> > tb, int Row, int Col)
{
	vector<int> hs(Col + 5, 0), pal(Col + 5, 0), pf(Col + 5, 0), sf(Col + 5, 0); int L = 0, R = 0, re = 0; vector<vector<bool> > ok(2, vector<bool > (Col + 5, false));
	for(int c = 1; c <= Col; c++) 
	{
		for(int r = 1; r <= Row; r++)
		{
			hs[c] = hs[c] * 31 + tb[r][c] - 'a' + 1;
			hs[c] %= mod;
		}
	}
	for(int c = 1; c <= Col - 1; c++)
	{
		if(L <= c and c <= R) pal[c] = min(pal[L + R - c - 1], R - c);
		while(c + pal[c] + 1 <= Col and c - pal[c] >= 1 and hs[c - pal[c]] == hs[c + 1 + pal[c]]) pal[c]++;
		if(R < c + pal[c])
		{
			R = c + pal[c];
			L = c - pal[c] + 1;
		}
	}
	ok[0][1] = 1;
	pf[1] = 1;
	for(int c = 2; c <= Col; c++) 
	{
		int lb = c - pal[c - 1];
		if(pf[c - 1] != pf[lb - 1]) ok[0][c] = 1;
		pf[c] = pf[c - 1] + ok[0][c];
	}
	ok[1][Col] = 1;
	sf[Col] = 1;
	for(int c = Col - 1; c >= 1; c--)
	{
		int rb = c + pal[c];
		if(sf[rb + 1] != sf[c + 1]) ok[1][c] = 1;
		sf[c] = sf[c + 1] + ok[1][c];
	}
	for(int c = 1; c <= Col; c++) 
	{
		re += ok[0][c] * sf[c];
	}
	return re;
}

signed main()
{
	freopen("ORIGAMI.inp", "r", stdin);
  freopen("ORIGAMI.out", "w", stdout);
	cin >> n >> m;
	vector<vector<char> > tb(n + 5, vector<char> (m + 5));
	for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cin >> tb[i][j];
	int x = solve(tb, n, m);
	tb = flip(tb, n, m);
	int y = solve(tb, m, n);
	int ans = x * y;
	cout << ans;
}
