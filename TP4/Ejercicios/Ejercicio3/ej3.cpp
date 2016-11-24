#include "ej3.h"

int main(int argc, char const *argv[]) {
  initialize();
  triangulate();

  int maximum = 0;
  while(goodPoints.size() > 0) {
    maximum = max(grahamScan(goodPoints), maximum);
    goodPoints.erase(goodPoints.begin());
  }
  cout << maximum << endl;
  return 0;
}

void initialize(){
  int H, E;
  cin >> H >> E;
  goodPoints = vector<Point>(H);
  badPoints = vector<Point>(E);
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
  for(Point a : goodPoints)
    for(Point b : goodPoints)
      for(Point c : goodPoints)
        if (a != b && a != c && b != c)
          contents[Triangle(a, b, c)] = getPointsInside(a, b, c);
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

int grahamScan(vector<Point>& points) {
  if (points.size() < 3)
    return points.size();

  sortPoints();

  vector<vector<int > > memo(points.size(), vector<int>(points.size(), 0));

  forr(i, 1, points.size())
    memo[0][i] = 2;

  int maximum = 2;

  forr(current, 2, points.size()) {
    forr(prevLast, 0, current - 1) {
      forr(last, prevLast + 1, current) {
        // Point a = points[current] - points[last], b = points[prevLast] - points[last];
        // !(a.crossProduct(b) < 0)

        // Nos fijamos si es convexo
        if (points[last].counterClockWise(points[current], points[prevLast])) {
          Content content = contents[Triangle(points[0], points[last], points[current])];
          if (content.bad == 0) {
            // POSSIBLE POINT OF FAILURE
            memo[last][current] = content.good + 1 + memo[prevLast][last];
            // cout << "Current: " << current << " Last: " << last << " PrevLast: " << prevLast << " Val : " << memo[last][current] << endl;
            maximum = max(maximum, memo[last][current]);
          }
        }
      }
    }
  }

  return maximum;
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
