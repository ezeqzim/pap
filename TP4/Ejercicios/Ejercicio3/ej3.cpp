#include "ej3.h"

int main(int argc, char const *argv[]) {
  initialize();
  triangulate();

  while(goodPoints.size() > 0){
    cout << endl;
    stack<Point> hull = grahamScan(goodPoints);

    while (!hull.empty()) {
      Point p = hull.top();
      hull.pop();
      cout << p << endl;
    }

    goodPoints.erase(goodPoints.begin());
  }

  return 0;
}

void initialize(){
  int H, E;
  cin >> H >> E;
  goodPoints = vector<Point>(H);
  badPoints = vector<Point>(E);
  triangles = vector<vector<vector<Content> > > (H, vector<vector<Content> > (H, vector<Content>(H)));
  memo = vector<vector<int> > (H, vector<int>(H, 0));
  forn(i, H) {
    Point p;
    cin >> p.x >> p.y;
    goodPoints[i] = p;
  }
  forn(i, E) {
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

stack<Point> grahamScan(vector<Point>& points) {
  stack<Point> hull;
  if (points.size() < 3){
    for(int i = 0; i < points.size(); ++i)
      hull.push(points[i]);
    return hull;
  }

  sortPoints();

  hull.push(points[0]);
  hull.push(points[1]);

  int i = 2;
  while(i < points.size()){
    Point top = hull.top();
    hull.pop();
    Point a = points[i] - top, b = hull.top() - top;
    if(!(hull.size() > 0 && a.crossProduct(b) < 0)) {
      hull.push(top);
      hull.push(points[i]);
      i++;
    }
  }

  return hull;
}

void sortPoints() {
  int leastY = 0;
  for (int i = 1; i < goodPoints.size(); i++)
    if (goodPoints[i] < goodPoints[leastY])
      leastY = i;

  swap(goodPoints[0], goodPoints[leastY]);

  pivot = goodPoints[0];
  sort(goodPoints.begin() + 1, goodPoints.end(), POLAR_ORDER);
}
