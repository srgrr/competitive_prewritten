#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 1e5 + 9;

/*
	INDICES START AT 1 HERE!
*/

template< typename T >
struct fenwick {

  int n;
  vector< T > tree;

  fenwick(int _n) {
    n = _n;
    tree = vector< T >(n + 1);
  }

  void insert(int pos, T val) {
    while(pos <= n) {
       tree[pos] += val;
       pos += (pos & -pos);
    }
  }

  T prefix(int pos) {
    T ret = 0;
    while(pos > 0) {
      ret += tree[pos];
      pos -= (pos & -pos);
    }
    return ret;
  }

  T intsum(int ql, int qr) {
    return prefix(qr) - prefix(ql - 1);
  }

};

int main() {
	fenwick< ll > f(100);
  for(int i=1; i<=100; ++i) f.insert(i, i);
  cout << f.prefix(10) << " " << f.prefix(100) << endl;
}
