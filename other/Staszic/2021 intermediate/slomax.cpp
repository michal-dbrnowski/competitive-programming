#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<pair<int,int>>> graph;
vector<vector<int>> ancestor;
vector<vector<int>> dist;
vector<int> depth;

void dfs(int v, int prev, int weight) {
    ancestor[v][0] = prev;
    dist[v][0] = weight;
    depth[v] = depth[prev] + 1;
    for (auto [u, w] : graph[v])
        if (u != prev) dfs(u, v, w);
}

int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    for (int k = 19; k >= 0; k--) {
        if (depth[ancestor[b][k]] >= depth[a])
            b = ancestor[b][k];
    }
    if (a == b) return a;
    for (int k = 19; k >= 0; k--) {
        if (ancestor[a][k] != ancestor[b][k])
            a = ancestor[a][k],
            b = ancestor[b][k];
    }
    return ancestor[a][0];
}

int get_dist(int a, int c) {
    int len = depth[a] - depth[c];
    int res = INT_MIN;
    for (int k = 19; k >= 0; k--) {
        if ((1 << k) <= len) {
            len -= (1 << k);
            res = max(res, dist[a][k]);
            a = ancestor[a][k];
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    graph.resize(n+1), ancestor.resize(n+1, vector<int>(20)),
    dist.resize(n+1, vector<int>(20)), depth.resize(n+1, -1);
    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    dfs(1, 1, 0);
    for (int k = 1; k < 20; k++)
        for (int i = 1; i <= n; i++)
            ancestor[i][k] = ancestor[ancestor[i][k-1]][k-1];

    for (int k = 1; k < 20; k++)
        for (int i = 1; i <= n; i++)
            dist[i][k] = max(dist[i][k-1], dist[ancestor[i][k-1]][k-1]);

    int a, b;
    while (cin >> a >> b) {
        int c = lca(a, b);
        if (a == b)
            cout << 0 << '\n';
        else
            cout << max(get_dist(a, c), get_dist(b, c)) << '\n';
    }
    return 0;
}