#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

const int max_n = (int)1e3;
const int max_m = (int)1e4;
const int oo = (int)1e9 + 1;

int n, m;
array<int, 3> edge[max_m+5];
int par[max_n+5], sz[max_n+5];

void init() {
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }
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

bool cmp(array<int, 3> a, array<int, 3> b) {
    return a[2] < b[2];
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; ++ i) cin >> edge[i][0] >> edge[i][1] >> edge[i][2];

    sort(edge + 1, edge + m + 1, cmp);

    int res = 2*oo;
    for(int i = 1; i <= m; ++ i) {
        init();
        int cnt = 0;
        int mx = -oo, mn = oo;
        for(int j = i; j <= m; ++ j) {
            if (join(edge[j][0], edge[j][1])) {
                cnt ++;
                mx = max(mx, edge[j][2]);
                mn = min(mn, edge[j][2]);
                if (cnt == n-1) break;
            }
        }
        if (cnt != n-1) break;
        res = min(res, mx - mn);
    }
    if (res == 2*oo) cout << "NOT FOUND";
    else cout << res;

    return 0;
}
