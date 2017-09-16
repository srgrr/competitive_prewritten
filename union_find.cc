#include <bits/stdc++.h>
using namespace std;
using vi = vector< int >;
using vvi = vector< vi >;

/*
  HERE INDICES WORK FROM 0 to N-1
  IT HAS NO COUNTING MECHANISM
*/

struct union_find {
  vector< int > g;
  int n;
  union_find(int _n) {
    n = _n;
    g = vector< int >(n);
    for(int i=0; i<n; ++i) {
      g[i] = i;
    }
  }

  int rep(int u) {
    if(g[u] == u) return u;
    return g[u] = rep(g[u]);
  }

  void join(int u, int v) {
    if(u>v) swap(u, v);
    g[rep(u)] = rep(v);
  }

};

int main() {
  ios_base::sync_with_stdio(false);
  int n, m;
  while(cin >> n >> m) {
    union_find uf(n);
    int ans = n;
    for(int i=0; i<m; ++i) {
      if(i>0) cout << ' ';
      int u, v; cin >> u >> v;
      if(uf.rep(u) != uf.rep(v)) --ans, uf.join(u, v);
      cout << ans;
    }
    cout << endl;
  }
}
