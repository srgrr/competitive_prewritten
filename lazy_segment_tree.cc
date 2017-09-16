#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
const int maxn = 1e5 + 9;
const int maxt = 1<<21;

struct query {
  char type;
  double l, r, yl, yr, x;
};

query queries[maxn];

struct lazy_segment_tree {
  int n;
  vector< double > tree, pending;

  void push_flag(int l, int r, int id) {
    tree[id] += double(r - l + 1)*pending[id];
    if(l<r) {
      pending[2*id] += pending[id];
      pending[2*id + 1] += pending[id];
    }
    pending[id] = 0.0;
  }

  void add(int ql, int qr, int l, int r, double val, int id) {
    push_flag(l, r, id);
    if(ql <= l && qr >= r) {
      pending[id] += val;
      push_flag(l, r, id);
      return;
    }
    if(qr < l || r < ql) return;
    int h = (l+r)/2;
    add(ql, qr, l, h, val, 2*id),
    add(ql, qr, h+1, r, val, 2*id + 1);
    tree[id] = tree[2*id] + tree[2*id + 1];
  }

  void add(int ql, int qr, double val) {
    add(ql, qr, 0, n-1, val, 1);
  }

  double get(int ql, int qr, int l, int r, int id) {
    push_flag(l, r, id);
    if(ql <= l && qr >= r) return tree[id];
    if(qr <  l || r  < ql) return 0.0;
    int h = (l+r)/2;
    return get(ql, qr, l, h, 2*id) + get(ql, qr, h+1, r, 2*id + 1);
  }

  double get(int ql, int qr) {
    return get(ql, qr, 0, n-1, 1);
  }

  lazy_segment_tree(int N, int T) {
    n = N;
    tree = vector< double >(T, 0.0);
    pending = vector< double >(T, 0.0);
  }
};

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);
  cout.setf(ios::fixed);
  cout.precision(3);
  int n;
  while(cin >> n) {
    set< double > number_track;
    for(int i=0; i<n; ++i) {
      query& q = queries[i];
      cin >> q.type;
      if(q.type == 'A') {
        cin >> q.l >> q.r >> q.yl >> q.yr;
        number_track.insert(q.l);
        number_track.insert(q.r);
        number_track.insert(q.yl);
        number_track.insert(q.yr);
      }
      else {
        cin >> q.x;
        number_track.insert(q.x);
      }
    }
    int cur_index = 0;
    unordered_map< double, int > compressed;
    for(double x : number_track) {
      compressed[x] = cur_index++;
    }
    lazy_segment_tree A(cur_index, maxt), B(cur_index, maxt);
    for(int i=0; i<n; ++i) {
      query& q = queries[i];
        if(q.type == 'A') {
        int cl = compressed[q.l], cr = compressed[q.r];
        //B.add(cl, cl, q.yl), B.add(cr, cr, q.yr);
        double a = (q.yl - q.yr)/(q.l - q.r);
        double b = q.yr - a*q.r;
        //cout << cl << " " << cr << endl;
        //cout << "pendiente = " << a << " indep = " << b << endl;
        A.add(cl, cr, a);
        B.add(cl, cr, b);
      }
      else {
        int cx = compressed[q.x];
        //cout << cx << endl;
        //cout << A.get(cx, cx) << " " << B.get(cx, cx) << endl;
        cout << A.get(cx, cx)*q.x + B.get(cx, cx) << endl;
      }
    }
  }
}
