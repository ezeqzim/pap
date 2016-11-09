#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

struct Point {
  int x, y;

  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }

  friend bool operator==(const Point& p1, const Point& p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
  }

  friend bool operator<(const Point& p1, const Point& p2) {
    return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
  }

  friend ostream& operator<<(ostream& os, const Point &p) {
    return os << p.x << " " << p.y;
  }
};

map<Point, set<Point> > borders;
vector<Point> polygon;

void updateBorder(Point& p1, Point& p2){
  if (borders[p1].erase(p2) == 0)
    borders[p1].insert(p2);
}

void extractBorders(int N) {
  forn(i, N-2){
    int x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    Point vertex1(x1, y1), vertex2(x2, y2), vertex3(x3, y3);
    updateBorder(vertex1, vertex2);
    updateBorder(vertex1, vertex3);
    updateBorder(vertex2, vertex1);
    updateBorder(vertex2, vertex3);
    updateBorder(vertex3, vertex1);
    updateBorder(vertex3, vertex2);
  }
}

int crossProduct(Point &base, Point &p1, Point &p2){
  int x1 = p1.x - base.x;
  int y1 = p1.y - base.y;
  int x2 = p2.x - base.x;
  int y2 = p2.y - base.y;
  return x1 * y2 - x2 * y1;
}

void findFirst(){
  Point actual = polygon[0];
  auto iter = borders[actual].begin();
  Point p1((*iter).x, (*iter).y);
  iter++;
  Point p2((*iter).x, (*iter).y);
  if (crossProduct(actual, p1, p2) < 0)
    polygon.push_back(p1);
  else
    polygon.push_back(p2);
}

void clockwisePath(int N) {
  findFirst();
  int before = 0;
  int actual = 1;

  while(polygon.size() < N) {
    auto iter = borders[polygon[actual]].begin();
    Point p1((*iter).x, (*iter).y);
    iter++;
    Point p2((*iter).x, (*iter).y);
    if (polygon[before] == p2)
      polygon.push_back(p1);
    else
      polygon.push_back(p2);
    before++;
    actual++;
  }
}

void finalize(int N){
  forn(i, N)
    cout << polygon[i] << " \n"[i == N-1];
}

int main(int argc, char const *argv[]) {
  int N;
  cin >> N;
  extractBorders(N);
  polygon.push_back(borders.begin()->first);
  clockwisePath(N);
  finalize(N);
  return 0;
}
