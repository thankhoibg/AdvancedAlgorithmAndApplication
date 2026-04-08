#include <iostream>
#include <algorithm>
#include <array>

using namespace std;

const int max_n = (int)2e5;
const int max_m = (int)4e5;

int n, m;
array<int, 3> edge[max_m+5];
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
    par[v] = u;
    sz[u] += sz[v];
    return true;
}

void init() {
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }
}

bool check(int cs) {
    int cnt = 0;
    init();
    for(int i = 1; i <= cs; ++ i) {
        cnt += join(edge[i][0], edge[i][1]);
        if (cnt == n-1) break;
    }
//    cout << cs << ' ' << cnt << '\n';
    return cnt == n-1;
}

int main() {
    cin >> n >> m;

    for(int i = 1; i <= m; ++ i) for(int j = 0; j <= 2; ++ j)
        cin >> edge[i][j];

    sort(edge+1, edge+m+1, cmp);

    int L = 1, R = m, res;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (check(mid)) {
//            cout << "y\n";
            R = mid-1;
            res = mid;
        } else {
            L = mid+1;
        }
    }
    cout << edge[res][2];

    return 0;
}
