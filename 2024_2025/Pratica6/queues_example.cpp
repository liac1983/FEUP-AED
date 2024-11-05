// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of STL queues

#include <iostream>
#include <queue>

using namespace std;

int main() {
  
  // Example list of integers
  queue<int> q;

  cout << "Queue size: " << q.size() << endl;

  q.push(2);
  q.push(4);
  q.push(6);
  q.push(8);

  cout << "Queue size: " << q.size() << endl;

  while (!q.empty()) {
    cout << "At the front: " << q.front() << " | At the back: " << q.back() << endl;
    q.pop();
  }

  cout << "Queue size: " << q.size() << endl;

  // A queue can be of any type
  queue<string> q2;
  queue<char> q3;
  queue<bool> q4;
      
  return 0;
}
