#include <iostream>

using namespace std;

const int max_n = (int)3e5;

int n;
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
    cin >> n;
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
    }
    for(int _ = 1; _ <= n; ++ _) {
        int p;
        cin >> p;
        int x = root(p);
        par[x] = x + 1 == n + 1 ? 1 : x + 1;
        cout << x << ' ';
    }

    return 0;
}
