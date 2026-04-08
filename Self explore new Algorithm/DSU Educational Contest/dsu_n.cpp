#include <iostream>

using namespace std;

const int max_n = (int)1e5;

int n, m;
int par[max_n+5], dist[max_n+5];

int root(int u) {
    if (par[u] == u) return u;
    int p = par[u];
    par[u] = root(par[u]);
    dist[u] += dist[p];
    return par[u];
}

void join(int u, int v) {
    int U = u;
    u = root(u);
    v = root(v);
    if (u == v) return;
    par[v] = u;
    dist[v] = 1;
//    par[u] = v;
//    dist[u] = 1;
}

int main() {
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> m;

    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        dist[i] = 0;
    }

    while (m --> 0) {
        int type, u, v;
        cin >> type >> u >> v;
        if (type == 1) {
            join(u, v);

//            for(int i = 1; i <= n; ++ i) {
//                root(i);
//                cout << dist[i] << ' ';
//            }
//            cout << '\n';
        } else {
//            for(int i = 1; i <= n; ++ i) {
//                root(i);
//                cout << dist[i] << ' ';
//            }
//            cout << '\n';
            if (root(u) != root(v)) cout << "Merry Christmas!\n";
            else if (dist[u] % 2 == dist[v] % 2) cout << "Yes\n";
            else cout << "No\n";
        }
    }

    return 0;
}
