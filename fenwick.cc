#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 1e5 + 9;

/*
	INDICES START AT 1 HERE!
*/


struct fenwick {

  int n;
  vector< ll > tree;

  fenwick(int _n) {
    n = _n;
    tree = vector< ll >(n+1);
  }

  void insert(int pos, ll val) {
    while(pos <= n) {
       tree[pos] += val;
       pos += (pos & -pos);
    }
  }

  ll prefix(int pos) {
    ll ret = 0;
    while(pos > 0) {
      ret += tree[pos];
      pos -= (pos & -pos);
    }
    return ret;
  }

  ll intsum(int ql, int qr) {
    return prefix(qr) - prefix(ql - 1);
  }

};

int main() {
	fenwick f(100);
  for(int i=1; i<=100; ++i) f.insert(i, i);
  cout << f.prefix(10) << " " << f.prefix(100) << endl;
}
