// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of STL sets and multisets

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {

  vector<int> v= {2,4,8,3,8,2,5,4};

  set<int> s;
  multiset<int> ms;

  // Traverse all the values of the vector and insert them on set s and multiset ms
  for (auto i : v) {
    s.insert(i);
    ms.insert(i);
  }

  // Print number of elements
  cout << "s.size() = " << s.size() << endl;
  cout << "ms.size() = " << ms.size() << endl;

  // Print the elements themselves (notice how they come in sorted order)
  cout << "s:";
  for (auto i : s) cout << " " << i;
  cout << endl;
  cout << "ms:";
  for (auto i : ms) cout << " " << i;
  cout << endl;

  // Normal forward iterator
  auto it = s.begin();
  cout << "it = s.begin(); it = " << *it << endl;
  it++;
  cout << "it++; it = " << *it << endl;
  it--;
  cout << "it--; it = " << *it << endl;
  it = s.end();
  it--;
  cout << "it = s.end(); it--; it = " << *it << endl;

  // Reverse iterator
  auto rit = s.rbegin();
  cout << "rit = s.rbegin(); rit = " << *rit << endl;
  rit++;
  cout << "rit++; rit = " << *rit << endl;

  // Checking if an element is on the set
  // find return an iterator to position or end() if not present
  cout << "is 5 on s? " << (s.find(5)!=s.end()?"yes":"no") << endl;
  cout << "is 6 on s? " << (s.find(6)!=s.end()?"yes":"no") << endl;

  // Erasing element by value
  s.erase(5);
  cout << "after removing 5, s.size() = " << s.size() << endl;
  cout << "after removing 5 again, s.size() = " << s.size() << endl;
  
  return 0;
}

// 1. Create a set of a different type
/*set<string> stringSet = {"apple", "orange", "banana"};
cout << "String set:"; 
for (auto &str : stringSet) cout << " " << str;
cout << endl;*/

// 2. Traverse all values in reverse order
/*cout << "s in reverse order:";
for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
    cout << " " << *rit;
cout << endl;
*/

// 3. Erase with an iterator
/*auto itErase = s.find(3);
if (itErase != s.end()) {
    s.erase(itErase);
    cout << "After erasing 3, s:";
    for (auto &x : s) cout << " " << x;
    cout << endl;
}
*/

// 4. Erase with a range of iterators
/*auto rangeStart = s.find(2);
auto rangeEnd = s.find(5);
s.erase(rangeStart, rangeEnd);
cout << "After erasing range [2, 5), s:";
for (auto &x : s) cout << " " << x;
cout << endl;
*/


// 5. Test lower_bound and upper_bound
/*auto lb = s.lower_bound(4);
auto ub = s.upper_bound(4);
cout << "lower_bound(4): " << (lb != s.end() ? to_string(*lb) : "not found") << endl;
cout << "upper_bound(4): " << (ub != s.end() ? to_string(*ub) : "not found") << endl;
*/

// Correct code 
/*#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main() {
    vector<int> v = {2, 4, 8, 3, 8, 2, 5, 4};

    set<int> s;
    multiset<int> ms;

    for (auto i : v) {
        s.insert(i);
        ms.insert(i);
    }

    // Print sizes and contents
    cout << "s.size() = " << s.size() << endl;
    cout << "ms.size() = " << ms.size() << endl;
    cout << "s:"; for (auto i : s) cout << " " << i; cout << endl;
    cout << "ms:"; for (auto i : ms) cout << " " << i; cout << endl;

    // Reverse traversal
    cout << "s in reverse order:";
    for (auto rit = s.rbegin(); rit != s.rend(); ++rit)
        cout << " " << *rit;
    cout << endl;

    // Erase with iterator
    auto itErase = s.find(3);
    if (itErase != s.end()) {
        s.erase(itErase);
        cout << "After erasing 3, s:";
        for (auto &x : s) cout << " " << x;
        cout << endl;
    }

    // Erase range
    auto rangeStart = s.find(2);
    auto rangeEnd = s.find(8);
    s.erase(rangeStart, rangeEnd);
    cout << "After erasing range [2, 8), s:";
    for (auto &x : s) cout << " " << x;
    cout << endl;

    // Lower and upper bounds
    auto lb = s.lower_bound(4);
    auto ub = s.upper_bound(4);
    cout << "lower_bound(4): " << (lb != s.end() ? to_string(*lb) : "not found") << endl;
    cout << "upper_bound(4): " << (ub != s.end() ? to_string(*ub) : "not found") << endl;

    // Set of different type
    set<string> stringSet = {"apple", "orange", "banana"};
    cout << "String set:"; 
    for (auto &str : stringSet) cout << " " << str;
    cout << endl;

    return 0;
}
*/




