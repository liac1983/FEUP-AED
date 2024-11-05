// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of STL lists

#include <iostream>
#include <list>

using namespace std;

// An example template function to print a list of any type
template <typename T>
void print(list<T> & lst) {
  for (auto i : lst) cout << i << " ";
  cout << endl;
}

int main() {
  
  // Example list of integers
  list<int> lst = {3, 5, 7, 1};
  print(lst);

  lst.push_front(42); // insert element on the front
  lst.pop_back();     // remove element from the back
  lst.push_back(20);  // insert element on the back  
  print(lst);
  
  auto it = lst.begin();
  cout << *it << endl;   // iterator to the first position
  it++;                  
  cout << *it << endl;   // iterator now points to 2nd position
  it = lst.erase(it);    // erase second position
  cout << *it << endl;   // iterator now points to element after old 2nd position
  print(lst);            // new list

  // A list can be of any type
  list<string> lst2 = {"forty", "two"};
  list<char> lst3 = {'a', 'e', 'i', 'o', 'u'};
  list<bool> lst4 = {true, false, true};
  print(lst2);
  print(lst3);
  print(lst4);
      
  return 0;
}

