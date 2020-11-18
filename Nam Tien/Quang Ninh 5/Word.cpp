/*
dp Trie, Virtual tree.
*/

#include<bits/stdc++.h>

using namespace std;

#define vi vector<int> 
#define eb emplace_back

#define MX INT_MAX / 2
#define maxn 1000005
#define maxk 205
#define maxc 27

int n, k, ans[maxn];
string s[maxn];

struct trie
{
	vector<vi> dp, nxt, mdp; vi par, Nodes, d, L, sz; int cn; vector<bool> imp; int imp_cnt = 0;
	trie()
	{
		nxt.assign(maxn, vi(maxc, -1));
		mdp = dp = vector<vi> (maxn, vi());
		par = d = L = sz = vi(maxn, 0);
		cn = 0;
		imp = vector<bool> (maxn, 0);
	}
	void add_string(string s)
	{
		int now = 0;
		for(auto ch: s)
		{
			int c = ch - 'a';
			if(nxt[now][c] == -1)
			{
				nxt[now][c] = ++cn;
				par[cn] = now;
				d[cn] = d[now] + 1;
			}
			now = nxt[now][c];
		}
		L[now]++;
	}
	void assign_imp(int u)
	{
		imp[u] = 1;
		dp[u] = mdp[u] = vi(k + 5, MX);
	}
	void dfs(int now)
	{
		sz[now] = L[now];
		for(int i = 1; i <= L[now]; i++) Nodes.eb(now);
		int cnt = 0;
		for(int c = 0; c < 26; c++)
		{
			if(nxt[now][c] != -1) 
			{
				dfs(nxt[now][c]);
				sz[now] += sz[nxt[now][c]];
				if(sz[nxt[now][c]]) cnt++;
			}
		}
		if(cnt >= 2 or L[now]) assign_imp(now);
	}
	void solve()
	{
		for(auto u: Nodes)
		{
			int now = u;
			while(1)
			{
				if(imp[now])
				{
					for(int i = 1; i <= k; i++) 
						dp[u][i] = (i == 1)? d[u]: min(dp[u][i], mdp[now][i - 1] + d[u]);
				}
				if(now == 0) break;
				now = par[now];
			}
			now = u;
			while(1)
			{
				if(imp[now])
				{
					for(int i = 1; i <= k; i++) 
						mdp[now][i] = min(mdp[now][i], dp[u][i] + d[u] - 2 * d[now]);
				}
				if(now == 0) break;
				now = par[now];
			}
			for(int i = 1; i <= k; i++) ans[i] = min(ans[i], dp[u][i] + d[u]);
		}
	}
} T;
int main()
{
	freopen("WORD.inp", "r", stdin);
	freopen("WORD.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> k;
	fill(ans, ans + k + 1, MX);
	for(int i = 1; i <= n; i++) 
	{
		cin >> s[i];
		T.add_string(s[i]);
	}
	T.dfs(0);
	T.solve();
	for(int i = 1; i <= k; i++) cout << ans[i] << "\n";
}
