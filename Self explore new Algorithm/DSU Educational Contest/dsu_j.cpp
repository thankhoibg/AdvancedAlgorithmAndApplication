#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

const int max_n = (int)2e5;

int n, m;
array<int, 3> edge[max_n+5];
int par[max_n+5], sz[max_n+5];

bool cmp(array<int, 3> a, array<int, 3> b) {
    return a[2] < b[2];
}

int root(int u) {
    if (par[u] == u) return u;
    return par[u] = root(par[u]);
}

bool join(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    par[v] = u;
    return true;
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++ i) cin >> edge[i][0] >> edge[i][1] >> edge[i][2];

    sort(edge+1, edge+m+1, cmp);

    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }
    long long res = 0;
    for(int i = 1; i <= m; ++ i) {
        if (join(edge[i][0], edge[i][1])) {
            res += edge[i][2];
        }
    }
    cout << res;

    return 0;
}
