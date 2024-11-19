// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of STL maps

#include <iostream>
#include <map>

using namespace std;

int main() {

  map<string, int> m;

  // Insert some elements
  m["John"] = 42;
  m["Sarah"] = 31;
  m["Tom"] = 56;

  // Print the elements of the map: each entry is a pair (key, value)
  for (auto p : m)
    cout << p.first << " -> " << p.second << endl;

  // Checking if a key is on the map
  // find return an iterator to position or end() if not present
  cout << "is Sarah on m? " << (m.find("Sarah")!=m.end()?"yes":"no") << endl;
  cout << "is Bob on m? " << (m.find("Bob")!=m.end()?"yes":"no") << endl;

  // Printing the value of a key
  cout << "Value of Sarah? " << m["Sarah"] << endl;
  // Careful: if the value does not exist, it will be created...
  cout << "Value of Kim? " << m["Kim"] << endl;

  // Showcasing erase and changing a value
  m.erase("Sarah");
  m["Tom"] = 20;
  cout << "After erasing Sarah and changing the value of Tom:" << endl;
  for (auto p : m)
    cout << p.first << " -> " << p.second << endl;
    
  return 0;
}


/*#include <iostream>
#include <map>
#include <string>
#include <multimap>

using namespace std;

int main() {
    map<string, int> m;

    // Insert elements
    m["John"] = 42;
    m["Sarah"] = 31;
    m["Tom"] = 56;

    // Print elements
    for (auto p : m)
        cout << p.first << " -> " << p.second << endl;

    // Map with different key/value types
    map<int, string> idToName = {{1, "Alice"}, {2, "Bob"}, {3, "Charlie"}};
    for (auto p : idToName)
        cout << p.first << " -> " << p.second << endl;

    // Multimap example
    multimap<string, int> mm = {{"John", 42}, {"John", 50}, {"Sarah", 31}};
    for (auto p : mm)
        cout << p.first << " -> " << p.second << endl;

    // Erase elements in a range
    map<int, string> m2 = {{1, "A"}, {2, "B"}, {3, "C"}, {4, "D"}};
    auto itStart = m2.lower_bound(2);
    auto itEnd = m2.upper_bound(3);
    m2.erase(itStart, itEnd);
    for (auto p : m2)
        cout << p.first << " -> " << p.second << endl;

    // Clear map
    m.clear();
    cout << "Size after clearing: " << m.size() << endl;

    // Lower and upper bounds
    map<int, string> m3 = {{1, "A"}, {3, "B"}, {5, "C"}};
    auto lb = m3.lower_bound(3);
    auto ub = m3.upper_bound(3);
    cout << "lower_bound(3): " << lb->first << " -> " << lb->second << endl;
    cout << "upper_bound(3): " << ub->first << " -> " << ub->second << endl;

    return 0;
}
*/


