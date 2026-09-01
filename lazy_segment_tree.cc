#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

/*
    Range update, range query lazy segment tree.

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

// Range add. Scales the tag by segment length; use with op_sum.
template <typename T>
struct lazy_add {
    static T identity() { return T(0); }
    T compose(const T& existing, const T& incoming) const { return existing + incoming; }
    T apply(const T& val, const T& tag, int len) const { return val + tag * T(len); }
};

// Range add applied to each element; use with op_min / op_max.
template <typename T>
struct lazy_add_each {
    static T identity() { return T(0); }
    T compose(const T& existing, const T& incoming) const { return existing + incoming; }
    T apply(const T& val, const T& tag, int len) const { (void)len; return val + tag; }
};

template <typename T, typename Op = op_sum<T>, typename Lazy = lazy_add<T> >
struct lazy_segment_tree {
    int n;
    Op op;
    Lazy lz;
    vector<T> tree, pending;

    lazy_segment_tree(int _n) {
        n = _n;
        tree = vector<T>(4 * n, Op::identity());
        pending = vector<T>(4 * n, Lazy::identity());
    }

    lazy_segment_tree(const vector<T>& v) {
        n = (int)v.size();
        tree = vector<T>(4 * n, Op::identity());
        pending = vector<T>(4 * n, Lazy::identity());
        if(n > 0) build(v, 0, n - 1, 1);
    }

    void build(const vector<T>& v, int l, int r, int id) {
        if(l == r) {
            tree[id] = v[l];
            return;
        }
        int h = (l + r) / 2;
        build(v, l, h, 2 * id);
        build(v, h + 1, r, 2 * id + 1);
        tree[id] = op(tree[2 * id], tree[2 * id + 1]);
    }

    void push(int l, int r, int id) {
        tree[id] = lz.apply(tree[id], pending[id], r - l + 1);
        if(l < r) {
            pending[2 * id] = lz.compose(pending[2 * id], pending[id]);
            pending[2 * id + 1] = lz.compose(pending[2 * id + 1], pending[id]);
        }
        pending[id] = Lazy::identity();
    }

    void update(int ql, int qr, T val, int l, int r, int id) {
        push(l, r, id);
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr) {
            pending[id] = lz.compose(pending[id], val);
            push(l, r, id);
            return;
        }
        int h = (l + r) / 2;
        update(ql, qr, val, l, h, 2 * id);
        update(ql, qr, val, h + 1, r, 2 * id + 1);
        tree[id] = op(tree[2 * id], tree[2 * id + 1]);
    }

    void update(int ql, int qr, T val) {
        update(ql, qr, val, 0, n - 1, 1);
    }

    T get(int ql, int qr, int l, int r, int id) {
        push(l, r, id);
        if(qr < l || r < ql) return Op::identity();
        if(ql <= l && r <= qr) return tree[id];
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
    const int n = 50;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) v[i] = rand() % 100 - 50;
    lazy_segment_tree<int> sum(v);
    lazy_segment_tree<int, op_max<int>, lazy_add_each<int> > mx(v);
    lazy_segment_tree<int, op_min<int>, lazy_add_each<int> > mn(v);
    for(int rep = 0; rep < 20; ++rep) {
        for(int i = 0; i < n; ++i) {
            for(int j = i; j < n; ++j) {
                assert(sum.get(i, j) == (naive_get<int, op_sum<int> >(v, i, j)));
                assert(mx.get(i, j) == (naive_get<int, op_max<int> >(v, i, j)));
                assert(mn.get(i, j) == (naive_get<int, op_min<int> >(v, i, j)));
            }
        }
        int l = rand() % n, r = rand() % n, val = rand() % 20 - 10;
        if(l > r) swap(l, r);
        for(int i = l; i <= r; ++i) v[i] += val;
        sum.update(l, r, val), mx.update(l, r, val), mn.update(l, r, val);
    }
    cout << "all intervals ok" << endl;
}
