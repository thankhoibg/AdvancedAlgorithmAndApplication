#include <iostream>

using namespace std;

const int max_n = (int)3e5 + 5;

int n, m;
int par[max_n+5], sz[max_n+5], mn[max_n+5], mx[max_n+5];

int root (int u) {
    if (par[u] == u) return u;
    return par[u] = root(par[u]);
}

void Union(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    par[v] = u;
    sz[u] += sz[v];
    mn[u] = min(mn[u], mn[v]);
    mx[u] = max(mx[u], mx[v]);
}

void solve(int u) {
    u = root(u);
    cout << mn[u] << ' ' << mx[u] << ' ' << sz[u] << '\n';
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; ++ i) {
        par[i] = mn[i] = mx[i] = i;
        sz[i] = 1;
    }

    while (m --> 0) {
        string type;
        int u, v;
        cin >> type >> u;
        if (type == "union") {
            cin >> v;
            Union(u, v);
        } else {
            solve(u);
        }
    }

    return 0;
}
