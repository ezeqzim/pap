using namespace std;

struct Point {
  int x, y;

  bool operator<(Point& p) {
    if (y != p.y)
      return y < p.y;
    return x < p.x;
  }

  bool operator==(Point& p) {
    return p.x == x && p.y == y;
  }

  bool operator!=(Point& p) {
    return !(p == *this);
  }

  Point operator-(Point& p) {
    return Point(x - p.x, y - p.y);
  }

  float crossProduct(Point& p) {
    return x * p.y - y * p.x;
  }

  bool counterClockWise(Point p1, Point p2) {
    Point a = p1 - *this;
    Point b = p2 - *this;
    return a.crossProduct(b) > 0;
  }

  friend ostream& operator<<(ostream& os, const Point &p) {
    return os << p.x << " " << p.y;
  }

  Point() {
    this->x = 0;
    this->y = 0;
  }

  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
};
