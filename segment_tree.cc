#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/*
    Point update, range query segment tree.

    ARRAY POSITIONS START AT 0 HERE!
*/

template <typename T>
struct op_sum {
    T operator()(const T& a, const T& b) const { return a + b; }
    static T identity() { return T(0); }
};

template <typename T>
struct op_max {
    T operator()(const T& a, const T& b) const { return a < b ? b : a; }
    static T identity() { return numeric_limits<T>::lowest(); }
};

template <typename T>
struct op_min {
    T operator()(const T& a, const T& b) const { return b < a ? b : a; }
    static T identity() { return numeric_limits<T>::max(); }
};

template <typename T, typename Op = op_sum<T> >
struct segment_tree {
    int n;
    Op op;
    vector<T> _tree;

    segment_tree(int _n) {
        n = _n;
        _tree = vector<T>(4 * n, Op::identity());
    }

    segment_tree(const vector<T>& v) {
        n = v.size();
        _tree = vector<T>(4 * n, Op::identity());
        if(n > 0) build(v, 0, n - 1, 1);
    }

    void build(const vector<T>& v, int l, int r, int id) {
        if(l == r) {
            _tree[id] = v[l];
            return;
        }
        int h = (l + r) / 2;
        build(v, l, h, 2 * id);
        build(v, h + 1, r, 2 * id + 1);
        _tree[id] = op(_tree[2 * id], _tree[2 * id + 1]);
    }

    void update(int pos, T val, int l, int r, int id) {
        if(l == r) {
            _tree[id] = val;
            return;
        }
        int h = (l + r) / 2;
        if(pos <= h) update(pos, val, l, h, 2 * id);
        else update(pos, val, h + 1, r, 2 * id + 1);
        _tree[id] = op(_tree[2 * id], _tree[2 * id + 1]);
    }

    void update(int pos, T val) {
        update(pos, val, 0, n - 1, 1);
    }

    T get(int ql, int qr, int l, int r, int id) {
        if(qr < l || r < ql) return Op::identity();
        if(ql <= l && r <= qr) return _tree[id];
        int h = (l + r) / 2;
        return op(get(ql, qr, l, h, 2 * id), get(ql, qr, h + 1, r, 2 * id + 1));
    }

    T get(int ql, int qr) {
        return get(ql, qr, 0, n - 1, 1);
    }
};

template <typename T, typename Op>
T naive_get(const vector<T>& v, int ql, int qr) {
    Op op;
    T ret = Op::identity();
    for(int i = ql; i <= qr; ++i) ret = op(ret, v[i]);
    return ret;
}

int main() {
    const int n = 100;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) v[i] = rand() % 100 - 50;
    segment_tree<int> sum(v);
    segment_tree<int, op_max<int> > mx(v);
    segment_tree<int, op_min<int> > mn(v);
    for(int rep = 0; rep < 20; ++rep) {
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                assert(sum.get(i, j) == (naive_get<int, op_sum<int> >(v, i, j)));
                assert(mx.get(i, j) == (naive_get<int, op_max<int> >(v, i, j)));
                assert(mn.get(i, j) == (naive_get<int, op_min<int> >(v, i, j)));
            }
        }
        int pos = rand() % n, val = rand() % 100 - 50;
        v[pos] = val;
        sum.update(pos, val), mx.update(pos, val), mn.update(pos, val);
    }
    cout << "all intervals ok" << endl;
}
