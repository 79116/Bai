// https://acm.timus.ru/problem.aspx?space=1&num=1533
#include<bits/stdc++.h>

using namespace std;

#define loop(i, l, r) for(int i = (int) l; i <= (int) r; i++)
#define rloop(i, r, l) for(int i = (int) r; i >= (int) l; i--)

#define vi vector<int>
#define ii pair<int, int>
#define eb emplace_back
#define all(x) begin(x), end(x)
#define fi first
#define se second

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define rand rng
#define endl '\n'
#define sp ' '


#define int long long

const int maxn = 2e5 + 5, mod = 1e9 + 7, inf = mod;

struct ed{
	int u, v, fl, ca; 
	ed(int u = 0, int v = 0, int ca = 0) : u(u), v(v), ca(ca), fl(0) {}
}; 
struct dinic {
	vector<ed> E; 
	vi ptr, d; 
	vector<vi> g; 
	int s, t, fl; 
	dinic(int n, int s, int t) : s(s), t(t), fl(0) { 
		ptr = d = vi(n + 5, 0); 
		g.resize(n + 5); 
	}
	void add(int u, int v, int ca) {
		g[u].eb(E.size()); 
		E.eb(u, v, ca);
		g[v].eb(E.size()); 
		E.eb(v, u, 0); 
	}
	int dfs(int u, int now) {
		if(u == t) return now; 
		for(int &p = ptr[u]; p < g[u].size(); p++) {
			int id = g[u][p]; 
			if(E[id].ca > E[id].fl and d[E[id].v] > d[u]) {
				int tm = dfs(E[id].v, min(now, E[id].ca - E[id].fl)); 
				if(tm) { E[id].fl += tm; E[id ^ 1].fl -= tm; return tm;}
			}
		}
		return 0; 
	}
	int maxflow() {
		while(1) {
			fill(all(d), inf); 
			d[s] = 0; 
			queue<int> q; 
			q.push(s); 
			while(!q.empty()) {
				int u = q.front(); 
				q.pop(); 
				for(int id: g[u]) {
					int v = E[id].v; 
					if(E[id].ca > E[id].fl and d[v] > d[u] + 1) {
						d[v] = d[u] + 1; 
						q.push(v); 
					}
				}
			}
			if(d[t] == inf) return fl; 
			fill(all(ptr), 0); 
			while(int t = dfs(s, inf)) fl += t; 
		}
	}
	// n in these function is not the same as n above, this one is only use to detect which side of the bipartite graph the vertex in on
	vector<bool> vs; 
	void get(int i, int n) {
		vs[i] = 1; 
		for(int id: g[i]) {
			if(i <= n and E[id].v > n and E[id].fl == 0 and !vs[E[id].v]) get(E[id].v, n); 
			if(i > n and E[id].v <= n and E[id].fl < 0 and !vs[E[id].v]) get(E[id].v, n); 
		}
	}
	set<int> minnimum_vertex_cover(int n) {
		vs = vector<bool>(2 * n + 2, 0); 
		set<int> l, r; 
		loop(i, 1, n) l.insert(i); 
		loop(i, 1, n) {
			bool unsat = 0; 
			for(int id: g[i]) {
				unsat |= (E[id].v == s and E[id].fl == 0);
			}
			if(unsat) {
//				cout << i << endl;
				get(i, n); 
			}
		}
		loop(i, 1, n) if(vs[i]) l.erase(i); 
		loop(i, n + 1, 2 * n) if(vs[i]) r.insert(i - n); 
//		assert(l.size() + r.size() == fl);
		set<int> re; for(int i: l) re.insert(i); for(int i: r) re.insert(i); 
		return re; 
	}
}; 
int n; 
vi g[maxn]; 
bool vs[maxn]; 

void dfs(int u, int r) {
	vs[u] = 1; 
	for(int v: g[u]) if(!vs[v]) dfs(v, r); 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n; 
	dinic din(2 * n + 2, 0, 2 * n + 1); 
	loop(i, 1, n) {
		loop(j, 1, n) {
			int x; cin >> x; 
			if(x) g[i].eb(j); 
		}
	}
	loop(i, 1, n) { fill(all(vs), 0); dfs(i, i); loop(j, 1, n) if(vs[j] and i != j) din.add(i, j + n, 1); }
	loop(i, 1, n) {din.add(din.s, i, 1); din.add(i + n, din.t, 1); }
	cout << n - din.maxflow() << endl; 
	set<int>  mcbm= din.minnimum_vertex_cover(n); 
//	assert(mcbm.size() == din.fl);
	loop(i, 1, n) if(!mcbm.count(i)) cout << i << sp;
}

