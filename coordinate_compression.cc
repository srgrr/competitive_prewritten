#include <bits/stdc++.h>
using namespace std;

template< typename T >
int get_index(T obj, vector< T >& indices ) {
  return lower_bound(indices.begin(), indices.end(), obj) - indices.begin();
}

template< typename T >
vector< int > get_indices(vector< T >& objects, vector< T >& indices) {
  vector< int > ret;
  for(auto& a : objects) {
    ret.push_back(get_index(a, indices));
  }
  return ret;
}

template< typename T >
vector< T > compress_coordinates(vector< T > v) {
  vector< T > ret(v);
  sort( ret.begin(), ret.end() );
  unique( ret.begin(), ret.end() );
  return ret;
}

int main() {
  vector< double > v = {3.0, 1.0, 2.0, 6.0};
  auto cv = compress_coordinates(v);
  for( auto x : get_indices(v, cv) ) {
    cout << x << endl;
  }
}
