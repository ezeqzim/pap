#include "ej3.h"

int main(int argc, char const *argv[]) {
  initialize();
  triangulate();
  sortPoints();





  // forn(i, goodPoints.size())
  //   forn(j, goodPoints.size())
  //     forn(k, goodPoints.size())
  //       if (i != j && i != k && j != k)
  //         cout << "A: " << goodPoints[i] << " B: " << goodPoints[j]
  //           << " C: " << goodPoints[k] << " " << triangles[i][j][k] << endl;

  // forn(i, goodPoints.size()){
  //   stack<Point> hull = grahamScan(goodPoints);
  //
  //   cerr << hull.size() << endl;
  //
  //   while (!hull.empty()) {
  //     Point p = hull.top();
  //     hull.pop();
  //     cerr << "(" << p.x << ", " << p.y << ")" << endl;
  //   }
  //
  //   goodPoints.erase(goodPoints.begin());
  // }

  return 0;
}

void initialize(){
  int H, E;
  cin >> H >> E;
  goodPoints = vector<Point>(H);
  badPoints = vector<Point>(E);
  triangles = vector<vector<vector<Content> > > (H, vector<vector<Content> > (H, vector<Content>(H)));
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

void triangulate() {
  forn(i, goodPoints.size())
    forn(j, goodPoints.size())
      forn(k, goodPoints.size())
        if (i != j && i != k && j != k)
          triangles[i][j][k] = getPointsInside(goodPoints[i], goodPoints[j], goodPoints[k]);
}

Content getPointsInside(Point a, Point b, Point c) {
  int good = 0, bad = 0;
  for (Point p : goodPoints)
    if (p != a && p != b && p != c && isInside(p, a, b, c))
      good++;
  for (Point p : badPoints)
    if (isInside(p, a, b, c))
      bad++;
  return Content(good, bad);
}

bool isInside(Point p, Point a, Point b, Point c) {
  Line l1(p, OUTSIDE), ab(a, b), bc(b, c), ac(a, c);
  return ab.intersect(l1) + bc.intersect(l1) + ac.intersect(l1) % 2 == 1;
}

void sortPoints() {
  // find the point having the least y coordinate (pivot),
  // ties are broken in favor of lower x coordinate
  int leastY = 0;
  for (int i = 1; i < goodPoints.size(); i++)
    if (goodPoints[i] < goodPoints[leastY])
      leastY = i;

  // swap the pivot with the first point
  swap(goodPoints[0], goodPoints[leastY]);

  // sort the remaining point according to polar order about the pivot
  pivot = goodPoints[0];
  sort(goodPoints.begin() + 1, goodPoints.end(), POLAR_ORDER);
}

// used for sorting points according to polar order w.r.t the pivot
bool POLAR_ORDER(Point a, Point b)  {
  return counterClockWise(pivot, a, b);
}

// returns true if p1 -> p2 -> p3 forms a counter-clockwise turn
bool counterClockWise(Point base, Point p1, Point p2) {
  Point a = p1 - base;
  Point b = p2 - base;
  return a.crossProduct(b) > 0;
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
