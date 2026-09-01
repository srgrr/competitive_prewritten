#include <bits/stdc++.h>
using namespace std;

template< typename T >
struct coordinate_compression {
    vector< T > coords;

    coordinate_compression(vector< T > v) {
        coords = v;
        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());
    }

    int get_index(const T& obj) {
        return lower_bound(coords.begin(), coords.end(), obj) - coords.begin();
    }

    vector< int > get_indices(const vector< T >& objects) {
        vector< int > ret;
        for(const auto& a : objects) {
            ret.push_back(get_index(a));
        }
        return ret;
    }

    int size() {
        return (int)coords.size();
    }
};

int main() {
    vector< double > v = {3.0, 1.0, 2.0, 6.0};
    coordinate_compression< double > cc(v);
    for( auto x : cc.get_indices(v) ) {
        cout << x << endl;
    }
}
