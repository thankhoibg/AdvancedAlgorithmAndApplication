#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

using namespace std;

const int max_n = (int)2e5;

int n, m;
long long s;
array<int, 4> edge[max_n+5];
int par[max_n+5], sz[max_n+5];

bool cmp(array<int, 4> a, array<int, 4> b) {
    return a[2] > b[2];
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
    cin >> n >> m >> s;
    for(int i = 1; i <= m; ++ i) {
        cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
        edge[i][3] = i;
    }

    sort(edge+1, edge+m+1, cmp);

    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }
    long long res = 0, sum_not_use = 0;
    vector<int> vec;
    for(int i = 1; i <= m; ++ i) {
        if (join(edge[i][0], edge[i][1])) {
            res += edge[i][2];
//            used[i] = true;
        } else {
//            used[i] = false;
            sum_not_use += edge[i][2];
            vec.push_back(i);
        }
    }

    reverse(vec.begin(), vec.end());
    while (sum_not_use > s && !vec.empty()) {
        sum_not_use -= edge[vec.back()][2];
        vec.pop_back();
    }

    cout << vec.size() << '\n';
    vector<int> vecc;
    for(int x : vec) {
        vecc.push_back(edge[x][3]);
    }
    sort(vecc.begin(), vecc.end());
    for(int x : vecc) cout << x << ' ';

    return 0;
}
