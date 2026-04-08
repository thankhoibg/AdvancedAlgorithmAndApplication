// https://oj.vnoi.info/problem/voscomps#comments
#include <bits/stdc++.h>

using namespace std;

const int max_n = (int)1e5;

int n, q;
array<int, 3> queries[max_n+5];

vector<bool> res;
vector<int> qu_time_stamps;
int cur_time_stamp = 0;
vector<pair<int, int>> t[max_n*4+5];
int par[max_n+5], sz[max_n+5];
struct Rollback {
    int y, r2;
    Rollback(int y, int r2) : y(y), r2(r2) {}
    Rollback() {}
};
stack<Rollback> st;
int total_rollback_times[max_n*4+5];

int root(int u) {
    if (par[u] == u) return u;
    return root(par[u]);
}

void merge(int node, int u, int v) {
    u = root(u);
    v = root(v);
    if (sz[u] < sz[v]) swap(u, v);
    // Save state
    st.push({v, sz[u]});
    
    par[v] = u;
    sz[u] += sz[v];
    total_rollback_times[node] ++;
}

void update(int node, int l, int r, int u, int v, pair<int, int> edge) {
    if (v < l || r < u) {
        return;
    }
    if (u <= l && r <= v) {
        t[node].push_back(edge);
        return;
    }
    int mnode = (l + r) >> 1;
    update(node << 1, l, mnode, u, v, edge);
    update(node << 1 | 1, mnode + 1, r, u, v, edge);
}

void dfs(int node, int l, int r) {
    // cerr << node << ' ' << l << ' ' << r << '\n';
    for (auto [u, v] : t[node]) {
        merge(node, u, v);
    }
    if (l == r) {
        // save answer
        while (cur_time_stamp < qu_time_stamps.size() && qu_time_stamps[cur_time_stamp] <= l) {
            // cerr << cur_time_stamp << '\n';
            int q_id = qu_time_stamps[cur_time_stamp];
            // cerr << q_id << '\n';
            int u = queries[q_id][1];
            int v = queries[q_id][2];
            // cerr << u << ' ' << v << '\n';
            // cerr << "u = " << u << " root: " << root(u) << '\n';
            // cerr << "v = " << v << " root: " << root(v) << '\n';
            if (root(u) == root(v)) {
                res.push_back(1);
            } else {
                res.push_back(0);
            }
            // cerr << "Res: " << (root(u) == root(v)) << '\n';
            cur_time_stamp ++;
        }
    } else {
        int mid = (l+r) >> 1;
        dfs(node << 1, l, mid);
        dfs(node << 1 | 1, mid + 1, r);

        
    }
    // Rollback
    while (!st.empty() && total_rollback_times[node] > 0) {
        auto [v, r1] = st.top();
        int u = par[v];
        // cout << node << ' ' << u << ' ' << v << '\n';
        sz[u] = r1;
        par[v] = v;
        st.pop();
        total_rollback_times[node] --;
    }
}

int main() {
    if (fopen(".inp", "r")) {
        freopen(".inp", "r", stdin);
        freopen(".out", "w", stdout);
    }
    cin >> n >> q;

    for (int i = 1; i <= q; ++ i) {
        cin >> queries[i][0] >> queries[i][1] >> queries[i][2];
        if (queries[i][1] > queries[i][2]) {
            swap(queries[i][1], queries[i][2]);
        }
        if (queries[i][0] == 3) {
            qu_time_stamps.push_back(i);
        }
    }

    // create life cycles of edges
    map<pair<int, int>, pair<int,int>> mp;
    vector<array<int, 4>> e_cycle;
    for(int i = 1; i <= q; ++ i) {
        int t = queries[i][0];
        int u = queries[i][1];
        int v = queries[i][2];
        if (t == 1) {
            if (mp[{u, v}].second == 0) {
                mp[{u, v}] = {i, 1};
            } else {
                mp[{u, v}].second ++;
            }
        } else if (t == 2) {
            mp[{u, v}].second --;
            if (mp[{u,v}].second == 0) {
                e_cycle.push_back({u, v, mp[{u,v}].first, i-1});
                mp[{u,v}].first = 0;
            }
            mp[{u,v}].second = max(mp[{u,v}].second, 0);
        }
    }
    for (auto &[k, v] : mp) {
        if (v.second > 0) {
            e_cycle.push_back({k.first, k.second, v.first, q});
        }
    }
    // for (auto &[u, v, l, r] : e_cycle) {
    //     cout << u << ' ' << v << ' ' << l << ' ' << r << '\n';
    // }
    mp.clear();

    // initial DSU
    for(int i = 1; i <= n; ++ i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (auto &[u, v, l, r] : e_cycle) {
        update(1, 1, q, l, r, {u, v});
    }

    // get answers for all 3rd type queries
    dfs(1, 1, q);

    // print answers
    for(int x : res) cout << x;

    return 0;
}

/*
2 4
1 1 2
3 2 1
2 2 1
3 1 2

10


*/