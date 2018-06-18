#include <bits/stdc++.h>
using namespace std;

struct sieve {
  vector< bool > is_prime;
  vector< int > primes;
  sieve(int N) {
    is_prime = vector< bool >(N, true);
    is_prime[0] = is_prime[1] = false;
    for(int i = 2; i < N; ++i) {
      if(is_prime[i]) {
        primes.push_back(i);
        for(int j = i + i; j < N; j += i) {
          is_prime[j] = false;
        }
      }
    }
  }
};


int main() {
  int N;
  cin >> N;
  sieve pf(N);
  for(int x : pf.primes) {
    cout << x << " ";
  }
  cout << endl;
}
