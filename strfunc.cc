#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
    kmp_failure[i] = longest proper prefix of s[0..i] that is also a suffix.
    z_function[i]  = longest prefix of s that is also a prefix of s[i..].
    z_function[0]  = 0
*/

template< typename S >
vector< int > kmp_failure(const S& s) {
    int n = int(s.size());
    vector< int > pi(n);
    for(int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while(j > 0 && s[i] != s[j]) j = pi[j - 1];
        if(s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

template< typename S >
vector< int > z_function(const S& s) {
    int n = int(s.size());
    vector< int > z(n);
    for(int i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) z[i] = min(r - i + 1, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

template< typename S >
vector< int > naive_kmp_failure(const S& s) {
    int n = int(s.size());
    vector< int > pi(n);
    for(int i = 1; i < n; ++i) {
        for(int len = i; len >= 0; --len) {
            bool ok = true;
            for(int k = 0; k < len; ++k) {
                if(s[k] != s[i - len + 1 + k]) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                pi[i] = len;
                break;
            }
        }
    }
    return pi;
}

template< typename S >
vector< int > naive_z_function(const S& s) {
    int n = int(s.size());
    vector< int > z(n);
    for(int i = 1; i < n; ++i) {
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    }
    return z;
}

int main() {
    for(int n = 0; n <= 20; ++n) {
        for(int rep = 0; rep < 50; ++rep) {
            string s(n, 'a');
            for(int i = 0; i < n; ++i) s[i] = 'a' + rand() % 3;
            assert(kmp_failure(s) == naive_kmp_failure(s));
            assert(z_function(s) == naive_z_function(s));
        }
        vector< int > v(n);
        for(int i = 0; i < n; ++i) v[i] = rand() % 4;
        assert(kmp_failure(v) == naive_kmp_failure(v));
        assert(z_function(v) == naive_z_function(v));
    }
    cout << "all ok" << endl;
}
