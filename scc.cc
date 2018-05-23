#include <bits/stdc++.h>
using namespace std;

struct scc {
  struct vertex {
    int ind, low;
    vector< int > adj;
    bool in_stack, vis;
    vertex() {
      in_stack = vis = false;
    }
  };

  stack < int > S;

  vector< vertex > g;
  
  vector< vector< int > > sccs;
  vector< int > scc_ind;


  scc(int N) {
    g = vector< vertex >(N);
    sccs = vector< vector< int > >();
    scc_ind = vector< int >(N);
  }

  void dfs(int root) {
    static int ind = 0;
    if(g[root].vis) return;
    g[root].vis = true;
    g[root].ind = g[root].low = ind;
    ++ind;
    S.push(root);
    g[root].in_stack = true;
    for(int adj : g[root].adj) {
      dfs(adj);
      if(g[adj].in_stack) {
        g[root].low = min(g[root].low, g[adj].low);
      }
    }
    if(g[root].ind == g[root].low) {
      int cur_ind = int(sccs.size());
      vector< int > cur_scc;
      int lastv;
      do {
        lastv = S.top();
        g[lastv].in_stack = false;
        S.pop();
        scc_ind[lastv] = cur_ind;
        cur_scc.push_back(lastv);
      } while(lastv != root);
      sccs.push_back(cur_scc);
    }
  }

  void compute_sccs() {
    for(int i = 0; i < int(g.size()); ++i) {
      dfs(i);
    }
  }

};

int main() {
  int T;
  cin >> T;
  for(int i = 1; i <= T; ++i) {
    int n, m;
    cin >> n >> m;
    scc g(n);
    for(int i = 0; i < m; ++i) {
     int u, v;
     cin >> u >> v;
     g.g[u].adj.push_back(v);
    }
    g.compute_sccs();
    cout << "Graph #" << i << " has " << g.sccs.size() << " strongly connected component(s)." << endl;
  }
}
