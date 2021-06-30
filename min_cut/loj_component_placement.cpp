//https://lightoj.com/problem/component-placement
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

const int maxN = 2e5 + 5, mod = 1e9 + 7;
const int inf = 1e9;

int n, m; 
struct ed {
    int u, v, fl, ca; 
    ed(int u, int v, int ca) : u(u), v(v), fl(0), ca(ca) {}
};
struct dinic{
    vector<ed> E; 
    vector<int> d, ptr; 
    vector<vector<int> >g;
    int s, t, f; 
    dinic(int n, int s, int t): s(s), t(t), f(0){
        d = ptr = vi(n + 5 , 0) ; 
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
            int v  = E[id].v;
            if(E[id].ca > E[id].fl and d[v] > d[u]) {
                int tmp = dfs(v, min(now, E[id].ca - E[id].fl)); 
                if(tmp) { E[id].fl += tmp; E[id ^ 1].fl -= tmp; return tmp;}
            }
        }
        return 0; 
    }
    int maxflow() {
        while(1) {
            fill(all(d), inf); 
            queue<int> q; 
            d[s] = 0; 
            q.push(s); 
            while(!q.empty()) {
                int u  = q.front(); 
                q.pop(); 
                for(int id: g[u]) {
                    int v = E[id].v; 
                    if(d[v] > d[u] + 1 and E[id].ca > E[id].fl) {
                        d[v] = d[u] + 1;
                        q.push(v); 
                    }
                }
            }
            if(d[t] == inf) return f;
            fill(all(ptr), 0); 
            while(int tmp = dfs(s, inf)) f += tmp; 
        }
    }
}; 
int c[205][2]; 
signed main() {
    int tc; 
    cin >> tc; 
    loop(test, 1, tc) {
        cin >> n >> m; 
        loop(t, 0, 1) loop(i, 1, n) cin >> c[i][t]; 
        loop(i, 1, n) {
            int x; cin >> x; if(x == -1) c[i][0] = inf; 
            else if(x == 1) c[i][1] = inf; 
        }
        dinic din(n + 2, 0, n + 1); 
        loop(i, 1, n) {
            din.add(din.s, i, c[i][1]);
            din.add(i, din.t, c[i][0]); 
        }
        loop(i, 1, m) {
            int u, v, c; cin >> u >> v >> c; 
            din.add(u, v, c); 
            din.add(v, u, c);
        }
        cout << "Case " << test << ": " << din.maxflow() << endl;
//        for(auto e: din.E) if(e.fl > 0 and e.ca == e.fl) cout << e.u << sp << e.v << sp << e.fl << sp << e.ca << endl;
    }
}
