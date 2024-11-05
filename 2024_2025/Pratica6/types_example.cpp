// AED 2024/2025 [Pedro Ribeiro - DCC/FCUP]
// An example usage of pairs, tuples and structs

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

// Example structure
typedef struct {
  string name;
  int age;
} Person;

// Example pair and tuple
typedef pair<double, double> Point2D;
typedef tuple<double, double, double> Point3D;

int main() {

  // --------------------------------------------------
  // Pairs group two variables
  // --------------------------------------------------
  cout << "PAIRS ----------" << endl;
  
  // A pair can group any type of variables
  pair<int, int> pi = {2, 4};
  pair<string, int> ps = {"John", 42};

  // You can access and moify elements 'first' and 'second'
  cout << pi.first << "," << pi.second << endl;
  cout << ps.first << "," << ps.second << endl;
  ps.first = "Mary";
  cout << ps.first << "," << ps.second << endl;

  // Pairs are comparable (compare first and in case of tie compare second)
  vector<pair<int, int>> vp = {{3,7}, {4,5}, {1,4}, {3,4}, {2,2}};
  sort(vp.begin(), vp.end());
  for (auto p : vp) cout << p.first << "," << p.second << endl;

  
  // -----------------------------------------------------------
  // Tuples are a generalization of a pair and allow N elements
  // -----------------------------------------------------------
  cout << "TUPLES ---------" << endl;
  
  tuple<string, int, bool> tup = {"James", 21, true};

  // You can access the elements using get<>
  cout << get<0>(tup) << "|" << get<1>(tup) << "|" << get<2>(tup) << endl;

  // Like pairs, tuples are comparable starting with the first element
  tuple<int, string, char> tup1 = {21, "David", 'A'};
  tuple<int, string, char> tup2 = {21, "Charles", 'B'};
  tuple<int, string, char> tup3 = {15, "Helen", 'C'};
  vector<tuple<int, string, char>> vt = {tup1, tup2, tup3}; 
  sort(vt.begin(), vt.end());
  for (auto t : vt) cout << get<0>(t) << "|" << get<1>(t) << "|" << get<2>(t) << endl;

  
  // -----------------------------------------------------------
  // Structs allow you to name the variables
  // -----------------------------------------------------------
  cout << "STRUCTS --------" << endl;

  // See Person definition on top of this file
  Person p1 = {"Hugh", 23}; // yes, this can be done, respecting the order of variables
  cout << p1.name << ";" << p1.age << endl;
  p1.name = "Eva";          // this is however more legible
  cout << p1.name << ";" << p1.age << endl;

  // Structs are however not directly comparable
  // (but you can implement a comparator - remember the sorting class?)
  Person p2 = {"Ted", 31};
  // Uncommenting the following line would give you an error
  // cout << (p1<p2) << endl;

  // -----------------------------------------------------------
  // Typedefs
  // -----------------------------------------------------------
  cout << "TYPEDEF --------" << endl;
  
  // Remember you can use typedef to name a type (see definitions on top of this file)
  Point2D point1 = {3.2, 9.6};
  Point3D point2 = {1.23, 4.56, 7.89};

  cout << "(" << point1.first << "," << point1.second << ")" << endl;
  cout << "(" << get<0>(point2) << "," << get<1>(point2) << "," << get<2>(point2) << ")" << endl;
      
  return 0;
}

