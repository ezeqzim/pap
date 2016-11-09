#include "../stdc++.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

struct Point {
  int x, y;
  Point() {
	  this->x = this->y = 0;
  }

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
  forn(i, N - 2){
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

pair<Point, Point> getAdyacent(Point point) {
  auto iter = borders[point].begin();
  Point p1((*iter).x, (*iter).y);
  iter++;
  Point p2((*iter).x, (*iter).y);
  return make_pair(p1, p2);
}

void findSecond(){
  Point first = borders.begin()->first;
  pair<Point, Point> adyacents = getAdyacent(first);
  if (crossProduct(first, adyacents.first, adyacents.second) < 0)
    polygon[1] = adyacents.first;
  else
    polygon[1] = adyacents.second;
}

void clockwisePath(int N) {
  findSecond();
  Point before = polygon[0];
  Point actual = polygon[1];

  forr(i, 2, N) {
	pair<Point, Point> adyacents = getAdyacent(actual);
	Point next = adyacents.first == before ? adyacents.second : adyacents.first;
	polygon[i] = next;
	before = actual;
	actual = next;
  }
}

void print(int N){
  forn(i, N)
    cout << polygon[i] << " \n"[i == N-1];
}

int main(int argc, char const *argv[]) {
  int N;
  cin >> N;
  polygon = vector<Point>(N);
  extractBorders(N);
  polygon[0] = borders.begin()->first;
  clockwisePath(N);
  print(N);
  return 0;
}
