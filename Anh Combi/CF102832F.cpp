/* 
Gop set tren cay O nlog, HLD
*/
#include<bits/stdc++.h>
 
using namespace std;
 
#define ii pair<int, int>
#define iii pair<ii, int>
 
#define mp make_pair
#define eb emplace_back
 
#define vi vector<int>
#define vii vector<ii>
#define viii vector<iii>
 
#define fi first
#define se second
#define xx fi.fi
#define yy fi.se
#define zz se
 
const int maxn = 200005;
 
int n, arr[maxn], b[maxn], cnt[18][1100005][2], d[maxn], par[maxn], sz[maxn], hv[maxn];
long long ans, Ans;
vi el[22], G[maxn];
 
void prep(int u)
{
	sz[u] = 1;
	for(int v: G[u])
	{
		if(v != par[u])
		{
			par[v] = u;
			prep(v);
			sz[u] += sz[v];
			if(sz[v] > sz[hv[u]]) hv[u] = v;
		}
	}
}
void get_stack(int u)
{
	if(u == 1) d[u] = 1;
	if(u != hv[par[u]]) d[u] = d[par[u]] + 1;
	else d[u] = d[par[u]]; 
	for(int v: G[u]) if(v != par[u]) get_stack(v);
}
void add(int st_id, int node, int val)
{
	cnt[st_id][arr[node]][b[node]] += val;
}
void solve(int u)
{
	if(!hv[u]) 
	{
		el[d[u]].eb(u);
		add(d[u], u, 1);
		return;
	}
	solve(hv[u]);
	ans += cnt[d[u]][0][b[u] ^ 1];
	el[d[u]].eb(u);
	add(d[u], u, 1);
	for(int v: G[u])
	{
		if(v != par[u] and v != hv[u])
		{
			solve(v);
			for(auto i: el[d[v]]) ans += cnt[d[u]][arr[i] ^ arr[u]][b[i] ^ 1];
			while(!el[d[v]].empty())
			{
				int i = el[d[v]].back();
				add(d[v], i, -1);
				el[d[v]].pop_back();
				add(d[u], i, 1);
				el[d[u]].eb(i);
			}
		}
	}
}
signed main()
{
// 	freopen(".inp", "r", stdin);
// 	freopen(".out", "w", stdout);
 	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> arr[i];
    for(int i = 1; i <= n - 1; i++)
    {
    	int u, v;
    	cin >> u >> v;
    	G[u].eb(v);
    	G[v].eb(u);
	}
	par[1] = 1;
	prep(1);
	get_stack(1);
	for(int bit = 0; bit <= 17; bit++)
	{
		for(int i = 1; i <= n; i++)
		{
			b[i] = i >> bit & 1;
		}
		ans = 0;
		solve(1);
		for(int st = 1; st < 18; st++)
		{
			while(!el[st].empty())
			{
				int i = el[st].back();
				add(st, i, -1);
				el[st].pop_back();
			}
		}
		Ans += ans << bit;
	}
	cout << Ans;
}
