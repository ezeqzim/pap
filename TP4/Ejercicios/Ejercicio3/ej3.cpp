#include "ej3.h"

int main(int argc, char const *argv[]) {
  initialize();
  triangulate();
  cout << maxConvexPolygon() << endl;
  return 0;
}

void initialize(){
  int H, E;
  Point p, minimum;
  cin >> H >> E;
  goodPoints = vector<pair<Point, int> >(H);
  badPoints = vector<Point>(E);
  contents = vector<vector<vector<Content> > >(H, vector<vector<Content> >(H, vector<Content>(H)));
  forn(i, H) {
    cin >> p.x >> p.y;
    if (p < minimum)
      minimum = p;
    goodPoints[i] = make_pair(p, i);
  }
  forn(i, E) {
    cin >> p.x >> p.y;
    badPoints[i] = p;
  }

  outside.x = minimum.x - 1;
  outside.y = minimum.y - 1;
}

void triangulate() {
  for(pair<Point, int> a : goodPoints)
    for(pair<Point, int> b : goodPoints)
      for(pair<Point, int> c : goodPoints)
        if (a.first != b.first && a.first != c.first && b.first != c.first)
          contents[a.second][b.second][c.second] = getPointsInside(a.first, b.first, c.first);
}

Content getPointsInside(Point a, Point b, Point c) {
  int good = 0, bad = 0;
  for (pair<Point, int> p : goodPoints)
    if (p.first != a && p.first != b && p.first != c && isInside(p.first, a, b, c))
      good++;
  for (Point p : badPoints)
    if (isInside(p, a, b, c))
      bad++;
  return Content(good, bad);
}

bool isInside(Point p, Point a, Point b, Point c) {
  Line l1(p, outside), ab(a, b), bc(b, c), ac(a, c);
  return ab.intersect(l1) + bc.intersect(l1) + ac.intersect(l1) % 2 == 1;
}

int maxConvexPolygon() {
  int maximum = 0;
  while(goodPoints.size() > 0) {
    maximum = max(iteration(), maximum);
    goodPoints.erase(goodPoints.begin());
  }
  return maximum;
}

int iteration() {
  if (goodPoints.size() < 3)
    return goodPoints.size();

  vector<vector<int > > memo(goodPoints.size(), vector<int>(goodPoints.size(), 0));
  int maximum = 2;

  sortPoints();

  forr(i, 1, goodPoints.size())
    memo[0][i] = 2;

  forr(current, 2, goodPoints.size()) {
    forr(prevLast, 0, current - 1) {
      forr(last, prevLast + 1, current) {
        // Nos fijamos si es convexo
        if (goodPoints[last].first.counterClockWise(goodPoints[current].first, goodPoints[prevLast].first)) {
          Content content = contents[goodPoints[0].second][goodPoints[last].second][goodPoints[current].second];
          if (content.bad == 0) {
            memo[last][current] = max(memo[last][current], content.good + 1 + memo[prevLast][last]);
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
    if (goodPoints[i].first < goodPoints[leastY].first)
      leastY = i;

  swap(goodPoints[0], goodPoints[leastY]);

  pivot = goodPoints[0].first;
  sort(goodPoints.begin() + 1, goodPoints.end(), POLAR_ORDER);
}
