#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

struct Point {
  int x, y;

  bool operator<(Point p) {
    if (y != p.y)
      return y < p.y;
    return x < p.x;
  }

  Point(){
    this->x = 0;
    this->y = 0;
  }

  Point(int x, int y){
    this->x = x;
    this->y = y;
  }
};

vector<Point> goodPoints;
vector<Point> badPoints;

Point pivot;

// returns true if p1 -> p2 -> p3 forms a counter-clockwise turn
bool counterClockWise(Point base, Point p1, Point p2) {
  int x1 = p1.x - base.x;
  int y1 = p1.y - base.y;
  int x2 = p2.x - base.x;
  int y2 = p2.y - base.y;
  return (x1 * y2 - x2 * y1) > 0;
}

// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b)  {
  return counterClockWise(pivot, a, b);
}

stack<Point> grahamScan(vector<Point>& points) {
  stack<Point> hull;
  if (points.size() < 3) {
    forn(i, points.size()){
      cerr << "hola" << endl;
      hull.push(points[i]);
    }
    return hull;
  }

  // find the point having the least y coordinate (pivot),
  // ties are broken in favor of lower x coordinate
  int leastY = 0;
  for (int i = 1; i < points.size(); i++)
    if (points[i] < points[leastY])
      leastY = i;

  // swap the pivot with the first point
  swap(points[0], points[leastY]);

  // sort the remaining point according to polar order about the pivot
  pivot = points[0];
  sort(points.begin() + 1, points.end(), POLAR_ORDER);

  hull.push(points[0]);
  hull.push(points[1]);
  hull.push(points[2]);

  for (int i = 3; i < points.size(); ++i) {
    Point top = hull.top();
    hull.pop();
    while(!counterClockWise(hull.top(), top, points[i])) {
      top = hull.top();
      hull.pop();
    }
    hull.push(top);
    hull.push(points[i]);
  }
  return hull;
}

void initialize(){
  int H, E;
  cin >> H >> E;
  goodPoints = vector<Point>(H);
  badPoints = vector<Point>(E);
  forn(i, H){
    Point p;
    cin >> p.x >> p.y;
    goodPoints[i] = p;
  }
  forn(i, E){
    Point p;
    cin >> p.x >> p.y;
    badPoints[i] = p;
  }
}

int main(int argc, char const *argv[]) {
  initialize();

  forn(i, goodPoints.size()){
    stack<Point> hull = grahamScan(goodPoints);

    cerr << hull.size() << endl;

    while (!hull.empty()) {
      Point p = hull.top();
      hull.pop();
      cerr << "(" << p.x << ", " << p.y << ")" << endl;
    }

    goodPoints.erase(goodPoints.begin());
  }

  return 0;
}
