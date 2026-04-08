#include <iostream>
#include <vector>

using namespace std;

const int max_n = (int)3e5;

int n, m;
int par[max_n+5], sz[max_n+5], dist[max_n+5];

void init() {
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
        dist[i] = 0;
    }
}

int root(int u) {
    if (u == par[u]) return u;
    int p = par[u];
    par[u] = root(par[u]);
    dist[u] += dist[p];
    return par[u];
}

void join(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    par[u] = v;
    sz[v] += sz[u];
    dist[u] = 1;
}

int calc(int u) {
    root(u);
    return dist[u];
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> m;
    init();
    while (m --> 0) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            join(u, v);
        } else {
            int u;
            cin >> u;
            cout << calc(u) << '\n';
        }
    }
    return 0;
}
