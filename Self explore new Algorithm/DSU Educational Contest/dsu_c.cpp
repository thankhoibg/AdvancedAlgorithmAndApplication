#include <iostream>

using namespace std;

const int max_n = (int)1e5 + 5;

int n, m;
int par[max_n+5], sz[max_n+5], val[max_n+5];

int root (int u) {
    if (par[u] == u) return u;
    return root(par[u]);
}

int calc(int u) {
    int r = root(u);
    int res = 0;
    while (u != r) {
        res += val[u];
        u = par[u];
    }
    res += val[u];
    return res;
}

void Union(int u, int v) {
    u = root(u);
    int V = v;
    v = root(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    val[v] -= calc(u);
    sz[u] += sz[v];
    par[v] = u;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen(".inp", "r", stdin);
//    freopen(".out", "w", stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
        val[i] = 0;
    }

    while (m --> 0) {
        string type;
        int u, v;
        cin >> type;
        if (type == "join") {
            cin >> u >> v;
            Union(u, v);
        } else if (type == "add") {
            cin >> u >> v;
            u = root(u);
            val[u] += v;
//            cout << u << ' ' << val[u] << '\n';
        } else {
            cin >> u;
            cout << calc(u) << '\n';
        }
    }

    return 0;
}
