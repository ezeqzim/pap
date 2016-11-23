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

  friend std::ostream& operator<<(std::ostream& os, const Point &p) {
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
