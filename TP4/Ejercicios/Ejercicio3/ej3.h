#include "../stdc++.h"
#include "Point.h"
#include "Content.h"
#include "Line.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

vector<pair<Point, int> > goodPoints; //index on contents
vector<Point> badPoints;
vector<vector<vector<Content> > > contents;
Point pivot, outside;

void initialize();
void triangulate();
Content getPointsInside(Point a, Point b, Point c);
bool isInside(Point p, Point a, Point b, Point c);
void sortPoints();
bool POLAR_ORDER(pair<Point, int> a, pair<Point, int> b) { return pivot.counterClockWise(a.first, b.first); }
int maxConvexPolygon();
int iteration();
