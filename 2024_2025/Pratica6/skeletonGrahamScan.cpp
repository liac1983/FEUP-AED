/**
   Algorithms and Data Structures (L.EIC011) 2024/2025
   DCC/FCUP & DEI/FEUP - University of Porto
   Ana Paula Tomas
*/

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
  int x, y;
};


/**
   checks left turn (assumes that there are no three collinear points)
*/
bool left_turn(Point &p0,Point &p1,Point &p2) {
  int x0 = p0.x, x1 = p1.x, x2 = p2.x;
  int y0 = p0.y, y1 = p1.y, y2 = p2.y;
  return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0) > 0; 
}


Point p1;  // global variable required for compPolar

/**
   checks whether p precedes q in the order defined by their polar angles w.r.t. p1
   (assumes that the polar angles are distinct, i.e., there are no three collinear points)
*/
bool compPolar(Point &p, Point &q) {
  return left_turn(p1,p,q);
}

/**
   returns the index of the bottom-most point 
   (in case of ties, returns the leftmost one)
*/
int bottomVertex(vector<Point> & pts) {
  int bottom = 0;

  for(int i=1; i < (int)pts.size(); i++) {
    // TODO
  }

  return bottom;
}

/**
   writes the convex hull in CCW order, starting at the bottom-most p1
*/
void output(stack<Point> & s){
  if (!s.empty()){
    Point p = s.top();
    s.pop();
    output(s);
    cout << p.x << " " << p.y << endl;
  }
}

/**
   finds the sequence of points in the convex hull (in CCW) of the set given by pts
*/
void GrahamScan(vector<Point> & pts) {
  int bottom = bottomVertex(pts);
  swap(pts[0],pts[bottom]);
  p1 = pts[0];

  // TODO: 
  // -- sort the remaining points angularly w.r.t. p1
  // -- create an empty stack s
  // -- push pts[0] and pts[1] into s

  // -- process the remaining points
  int k = 2;
  while (k < (int)pts.size()) {
    // TODO
    // Point p = s.top();
  }
  
  // TODO
  // output(s);
}

/**
   testing
*/
int main() {
  int n;

  cin >> n;

  vector<Point> pts(n);

  for(int i=0; i< n; i++){
    cin >> pts[i].x >> pts[i].y;
  }

  GrahamScan(pts);

  return 0;
}

/**
   Input:
10
5 2
0 5
3 3
4 10
3 0
10 10
7 0
1 8
4 6
9 8

   Output:
6
3 0
7 0
10 10
4 10
1 8
0 5
*/

