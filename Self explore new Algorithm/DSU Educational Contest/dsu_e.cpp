#include <iostream>
#include <tuple>
#include <map>

using namespace std;

const int max_n = (int)5e4;
const int max_m = (int)1e5;
const int max_k = (int)1e5 + 5e4;

int n, m, k;
pair<int, int> edge[max_m+5];
int par[max_n+5], sz[max_n+5];
bool is_del[max_m+5];
tuple<bool, int, int> qu[max_k+5];
bool res[max_k+5];
map<pair<int,int>, int> mp;

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
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }

    cin >> n >> m >> k;
    for(int i = 1; i <= m; ++ i) {
        cin >> edge[i].first >> edge[i].second;
        if (edge[i].first > edge[i].second) swap(edge[i].first, edge[i].second);
        mp[edge[i]] = i;
        is_del[i] = false;
    }
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }
    for(int i = 1; i <= k; ++ i) {
        string s;
        int u, v;
        cin >> s >> u >> v;
        if (u > v) swap(u, v);
        if (s == "cut") {
            qu[i] = {0, u, v};
//            cout << u << ' ' << v << ' ' << mp[{u,v}] << '\n';
            is_del[mp[{u,v}]] = true;
        }
        else {
            qu[i] = {1, u, v};
        }
    }
    for(int i = 1; i <= m; ++ i) {
        if (!is_del[i]) {
            join(edge[i].first, edge[i].second);
        }
    }

    for(int i = k; i >= 1; -- i) {
        auto [type, u, v] = qu[i];
        if (!type) {
            join(u, v);
//            cout << i << ' ' << u << ' ' << v << '\n';
        } else {
            if (root(u) != root(v)) res[i] = false;
            else res[i] = true;
        }
    }

    for(int i = 1; i <= k; ++ i) {
//        cout << get<0>(qu[i]) << '\n';
        if (get<0>(qu[i])) {
            if (res[i]) cout << "YES\n";
            else cout << "NO\n";
        }
    }

    return 0;
}
