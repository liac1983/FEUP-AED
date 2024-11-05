// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of STL stacks

#include <iostream>
#include <stack>

using namespace std;

int main() {
  
  // Example list of integers
  stack<int> st;

  cout << "Stack size: " << st.size() << endl;

  st.push(2);
  st.push(4);
  st.push(6);
  st.push(8);

  cout << "Stack size: " << st.size() << endl;

  while (!st.empty()) {
    cout << "At the top: " << st.top() << endl;
    st.pop();
  }

  cout << "Stack size: " << st.size() << endl;

  // A stack can be of any type
  stack<string> st2;
  stack<char> st3;
  stack<bool> st4;
      
  return 0;
}

