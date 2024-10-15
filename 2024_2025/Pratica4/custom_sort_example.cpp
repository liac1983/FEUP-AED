// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of the function sort with a custom comparator

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Type to store a person
typedef struct {
  int age;
  string name;
} Person;

// Function to compare two persons (to be used on sort)
// This function should return:
//  - true if person "p1" is "smaller" then person "p2"
//  - false otherwise
// Note: & passes a person as a reference, not making a copy
//       const indicates you cannot change the person, just read it
bool comparePerson(const Person & p1, const Person & p2) {
    if (p1.age < p2.age) return true;
    if (p1.age > p2.age) return false;

    return p1.name < p2.name;
};

 
int main() {
  int n;

  cin >> n;
  vector<Person> v(n);
  for (int i=0; i<n; i++)
    cin >> v[i].age >> v[i].name;

  // Call to standard sort algorithm in C++
  // sort(RandomIterator start, RandomIterator end, comparatorFunction)
  sort(v.begin(), v.end(), comparePerson);
  
  for (int i=0; i<n; i++)
    cout << v[i].age << " " << v[i].name << endl;
  
  return 0;
}