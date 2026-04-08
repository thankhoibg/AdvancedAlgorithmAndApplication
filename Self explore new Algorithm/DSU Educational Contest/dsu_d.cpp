#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

const int max_n = (int)2e5;
const int max_m = (int)4e5;

int n, m;
int par[max_n+5], sz[max_n+5];
pair<int, int> a[max_n+5];
pair<int, int> b[max_n+5];
pair<int, int> qu[max_m+5];
int res[max_n+5];
vector<int> group[max_n+5];

int root(int u) {
    if (par[u] == u) return u;
    return par[u] = root(par[u]);
}

void join(int u, int v, int i) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    int t_root = root(0);
    if (u == t_root) {
        if (i != m+1) {
            for(int x : group[v]) {
                res[x] = min(res[x], i);
            }
        }
    } else if (v == t_root) {
        if (i != m+1) {
            for(int x : group[u]) {
                res[x] = min(res[x], i);
            }
        }
    }
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    par[v] = u;
    for(int x : group[v]) {
        group[u].push_back(x);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n; ++ i) {
        cin >> a[i].first >> a[i].second;
        b[i] = a[i];
        par[i] = i;
        sz[i] = 1;
        group[i].push_back(i);
    }
    group[0].push_back(0);
    sz[0] = 1;
    par[0] = 0;
    join(0, 1, m+1);
    for(int i = 1; i <= m; ++ i) {
        cin >> qu[i].first >> qu[i].second;
        if (qu[i].second == 1) {
            b[qu[i].first].first = -1;
        } else {
            b[qu[i].first].second = -1;
        }
    }
    for(int i = 1; i <= n; ++ i) {
        if (b[i].first != -1) {
            join(b[i].first, i, m+1);
        }
        if (b[i].second != -1) {
            join(b[i].second, i, m+1);
        }
    }

    for(int i = 1; i <= n; ++ i) res[i] = m + 1;
    for(int i = m; i >= 1; -- i) {
        int u = qu[i].first, v = qu[i].second == 1 ? a[qu[i].first].first : a[qu[i].first].second;
        assert(v != -1);
        // cout << "join " << u << ' ' << v << '\n';
        // root(u) == 0 so group of u is alive and contrast
        join(u, v, i-1);
    }

    for(int i = 1; i <= n; ++ i) {
        if (res[i] == m+1) res[i] = -1;
        cout << res[i] << '\n';
    }

    return 0;
}
