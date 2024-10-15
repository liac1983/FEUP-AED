// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of the function sort with a custom comparator
// (using a lambda expression)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Type to store a person
typedef struct {
  int age;
  string name;
} Person;
 
int main() {
  int n;

  cin >> n;
  vector<Person> v(n);
  for (int i=0; i<n; i++)
    cin >> v[i].age >> v[i].name;

  // Using anonymous lambda expression
  sort(v.begin(), v.end(),
       [](const Person & p1, const Person & p2) {
         if (p1.age < p2.age) return true;
         if (p1.age > p2.age) return false;
         return p1.name < p2.name;
       });
  
  for (int i=0; i<n; i++)
    cout << v[i].age << " " << v[i].name << endl;
  
  return 0;
}