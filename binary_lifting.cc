#include <bits/stdc++.h>
using namespace std;
using vi = vector< int >;
using vvi = vector< vi >;
using ll = long long int;

struct vertex {
  vi adj, logparents;
  int depth;
};


void dfs(vector< vertex >& g, vi& path, int root, int lv = 0) {
  for(int step = 0; lv - (1 << step) >= 0; ++step) {
    g[root].logparents.push_back(path[lv - (1 << step)]);
  }
  path[lv] = root;
  g[root].depth = lv;
  for(int adj : g[root].adj) {
    if(g[root].logparents.empty() || adj != g[root].logparents[0]) {
      dfs(g, path, adj, lv + 1);
    }
  }
}


int lca(vector< vertex >& g, int u, int v) {
  if(g[u].depth < g[v].depth) {
    swap(u, v);
  }
  // if answer is u or v, well find it here
  for(int i = int(g[u].logparents.size()) - 1; i >= 0; --i) {
    if(int(g[u].logparents.size()) > i && g[g[u].logparents[i]].depth >= g[v].depth) {
      u = g[u].logparents[i];
    }
  }
  if(u == v) return u;
  // lift whenever possible
  for(int i = int(g[u].logparents.size()) - 1; i >= 0 && u != v; --i) {
    if(int(g[u].logparents.size()) > i &&
       int(g[v].logparents.size()) > i &&
       g[u].logparents[i] != g[v].logparents[i]) {
      u = g[u].logparents[i];
      v = g[v].logparents[i];
    }
  }
  return g[v].logparents[0];
}

int naive_lca(vector< vertex >& g, int u, int v) {
  set < int > S;
  vi ms = {u, v};
  for(int x : ms) {
    int cur = x;
    do {
      if(S.count(cur)) return cur;
      S.insert(cur);
      if(g[cur].logparents.empty()) cur = -1;
      else cur = g[cur].logparents[0];
    } while(cur != -1);
  }
}

int main() {
  int n;
  cin >> n;
  vector< vertex > g(n, vertex());
  for(int i = 1; i < n; ++i) {
    int u = i, v = rand() % i;
    g[u].adj.push_back(v);
    g[v].adj.push_back(u);
  }
  vi path(n);
  dfs(g, path, 0, 0);
  for(int i = 0; i < n; ++i) {
    for(int j = i + 1; j < n; ++j) {
      cout << i << ", " << j << endl;
      int u = i, v = j;
      assert(lca(g, u, v) == naive_lca(g, u, v));
    }
  }
}
