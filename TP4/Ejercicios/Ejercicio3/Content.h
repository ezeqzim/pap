using namespace std;

struct Content {
  int good, bad;

  Content() {
    this->good = this->bad = 0;
  }

  Content(int good, int bad) {
    this->good = good;
    this->bad = bad;
  }

  friend ostream& operator<<(ostream& os, const Content &p) {
    return os << "Good: " << p.good << " Bad: " << p.bad;
  }
};
