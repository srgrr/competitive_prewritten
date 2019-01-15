#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using vi = vector< int >;
using vvi = vector< int >;

/*
  Two examples of the repeated squares algorithm on more complicated things
  (i.e: not numbers)
*/

struct permutation {
  vi p;
  permutation(vi& v) : p(v) { }
  permutation id() {
    int n = int(p.size());
    vi v(n);
    for(int i = 0; i < n; ++i) {
      v[i] = i;
    }
    return permutation(v);
  }
  permutation operator*(permutation& other) {
    int n = int(p.size());
    permutation ret(id());
    for(int i = 0; i < n; ++i) {
      ret.p[i] = p[other.p[i]];
    }
    return ret;
  }
};

template< typename T >
struct matrix {
  vector< vector< T > > m;
  matrix(vector< vector< T > >& mat) : m(mat) { }
  matrix operator*(matrix& other) {
    int n = int(m.size());
    vector< vector< T > > ret(n, vector< T >(n, 0));
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
        for(int k = 0; k < n; ++k) {
          ret[i][j] = ret[i][j] + m[i][k] * other.m[k][j];
        }
      }
    }
    return matrix(ret);
  }
  matrix id() {
    int n = int(m.size());
    vector< vector< T > > ret(n, vector< T >(n, 0.0));
    for(int i = 0; i < n; ++i) {
      ret[i][i] = 1.0;
    }
    return matrix(ret);
  }
};

template< typename T >
T fast_pow(T b, ll e) {
  if(e == 0ll) return b.id();
  if(e == 1ll) return b;
  T aux = fast_pow(b * b, e >> 1ll);
  if(e & 1ll) {
    aux = b * aux;
  }
  return aux;
}

int main() {
  int n;
  ll e;
  cin >> n >> e;
  vi v(n);
  for(int& x : v) cin >> x;
  permutation p(v);
  auto ans = fast_pow(p, e);
  // Build the permutation matrix of v
  vector< vector< int > > _perm_mat(n, vector< int >(n, 0));
  for(int i = 0; i < n; ++i) {
    _perm_mat[i][v[i]] = 1;
  }

  matrix perm_mat(_perm_mat);

  auto ret_mat = fast_pow(perm_mat, e);

  // Check that results coincide
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      if(ret_mat.m[i][j]) assert(ans.p[i] == j); 
    }
  }
}
