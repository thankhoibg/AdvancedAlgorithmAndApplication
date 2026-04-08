#include <iostream>

using namespace std;

const int max_n = (int)1e6;

int n, m;
int par[max_n+5];

int root(int u) {
    if (par[u] == u) return u;
    return par[u] = root(par[u]);
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> m;
    for(int i = 1; i <= n+1; ++ i) {
        par[i] = i;
    }
    while (m-->0) {
        char type;
        int x;
        cin >> type >> x;
        if (type == '-') {
            par[x] = x + 1;
        } else {
            int res = root(x);
            if (res == n + 1) res = -1;
            cout << res << '\n';
        }
    }

    return 0;
}
