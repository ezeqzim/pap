using namespace std;

struct Triangle {
  Point a, b, c;

  Triangle(Point a, Point b, Point c) {
    this->a = a;
    this->b = b;
    this->c = c;
  }

  bool operator<(const Triangle& other) const {
    if (a == other.a) {
      if (b == other.b) {
        return c < other.c;
      } else {
        return b < other.b;
      }
    } else {
      return a < other.a;
    }
  }
};
