#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

// Global pivot point for sorting
Point p1;

// Function to determine if three points make a left turn
bool left_turn(Point &p0, Point &p1, Point &p2) {
    int x0 = p0.x, x1 = p1.x, x2 = p2.x;
    int y0 = p0.y, y1 = p1.y, y2 = p2.y;
    return (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) > 0;
}

// Comparator to sort by polar angle with respect to p1
bool compPolar(Point &p, Point &q) {
    return left_turn(p1, p, q);
}

// Function to find the bottom-most point
int bottomVertex(vector<Point> &pts) {
    int bottom = 0;
    for (int i = 1; i < (int)pts.size(); i++) {
        if (pts[i].y < pts[bottom].y || (pts[i].y == pts[bottom].y && pts[i].x < pts[bottom].x)) {
            bottom = i;
        }
    }
    return bottom;
}

// Output the points in the convex hull in counterclockwise order
void output(stack<Point> &s) {
    vector<Point> result;
    while (!s.empty()) {
        result.push_back(s.top());
        s.pop();
    }
    reverse(result.begin(), result.end());
    cout << result.size() << endl;
    for (const auto &p : result) {
        cout << p.x << " " << p.y << endl;
    }
}

// Graham Scan algorithm for convex hull
void GrahamScan(vector<Point> &pts) {
    int bottom = bottomVertex(pts);
    swap(pts[0], pts[bottom]);
    p1 = pts[0];

    // Sort the points by polar angle with respect to p1
    sort(pts.begin() + 1, pts.end(), compPolar);

    stack<Point> s;
    s.push(pts[0]);
    s.push(pts[1]);

    // Process remaining points
    for (int i = 2; i < (int)pts.size(); i++) {
        Point top = s.top();
        s.pop();
        while (!s.empty() && !left_turn(s.top(), top, pts[i])) {
            top = s.top();
            s.pop();
        }
        s.push(top);
        s.push(pts[i]);
    }

    output(s);
}

// Main function to read input and execute Graham Scan
int main() {
    int n;
    cin >> n;
    vector<Point> pts(n);

    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }

    GrahamScan(pts);

    return 0;
}
