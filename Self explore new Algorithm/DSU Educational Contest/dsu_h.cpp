#include <iostream>

using namespace std;

const int max_n = (int)2e5;

int n, q;
int par1[max_n+5], par2[max_n+5];
int sz[max_n+5];

int root1(int u) {
    if (u == par1[u]) return u;
    return par1[u] = root1(par1[u]);
}

void join1(int u, int v) {
    u = root1(u);
    v = root1(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    sz[u] += sz[v];
    par1[v] = u;
}

int root2(int u) {
    if (u == par2[u]) return u;
    return par2[u] = root2(par2[u]);
}


int main() {
    ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
    if(fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> q;
    for(int i = 1; i <= n; ++ i) {
        par1[i] = par2[i] = i;
        sz[i] = 1;
    }
//    q = 0;
    while (q-->0) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            join1(u, v);
        } else if (type == 3) {
            int u, v;
            cin >> u >> v;
            if (root1(u) == root1(v)) cout << "YES\n";
            else cout << "NO\n";
        } else {
            int u, v;
            cin >> u >> v;
            int cur = root2(u);

            // Phải là dấu <, vì ta gộp cur với cur + 1
            while (cur < v) {
                // Nối 2 phần tử liền kề trong thực tế
                join1(cur, cur + 1);

                // Cập nhật DSU tiến bước: Gốc hiện tại (cur) trỏ thẳng sang gốc của phần tử bên phải
                par2[cur] = root2(cur + 1);

                // Nhảy cóc đến điểm chưa sáp nhập tiếp theo
                cur = root2(cur);
            }
        }
    }

    return 0;
}
