using namespace std;

struct Line {
  Point p, v;

  int intersect(Line& l) {
    return (intersectSegment(*this, l) && intersectSegment(l, *this)) ? 1 : 0;
  }

  bool intersectSegment(Line& l1, Line& l2) {
    if (l1.v.crossProduct(l2.v) == 0) return false;
    float t = (l2.p - l1.p).crossProduct(l2.v) / l1.v.crossProduct(l2.v);
    return (0 <= t && t <= 1);
  }

  Line(Point a, Point b) {
    this->p = a;
    this->v = b - a;
  }
};
