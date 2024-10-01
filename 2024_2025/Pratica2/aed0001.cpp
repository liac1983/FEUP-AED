// An example solution that is not efficient enough
// It has temporal complexity O(Q*N), where N is the maximum possible number

#include <iostream>

using namespace std;

bool isPrime(int n) {
  if (n<2) return false;
  
  for (int i=2; i<n; i++)
    if (n % i == 0)
      return false;
  
  return true;
}

int main() {
  int q;

  cin >> q;
  for (int i=0; i<q; i++) {
    int n;
    cin >> n;
    if (isPrime(n)) cout << n << " is prime" << endl;
    else cout << n << " is composite" << endl;
  }
    
  return 0;
}