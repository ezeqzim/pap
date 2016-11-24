#include "../stdc++.h"
#include "Point.h"
#include "Content.h"
#include "Line.h"

typedef long long ll;
#define forr(i, a, b) for(int i = (a); i < (b); ++i)
#define forn(i, n) forr(i, 0, n)

using namespace std;

vector<Point> goodPoints;
vector<Point> badPoints;
vector<vector<vector<Content> > > triangles;
vector<vector<int > > memo;
Point pivot;
Point OUTSIDE(1 << 16, 1 << 16); //(2 ** 16, 2 ** 16)

void initialize();
void triangulate();
Content getPointsInside(Point a, Point b, Point c);
bool isInside(Point p, Point a, Point b, Point c);
void sortPoints();
bool POLAR_ORDER(Point a, Point b) { return pivot.counterClockWise(a, b); }
stack<Point> grahamScan(vector<Point>& points);

// ASUMIMOS QUE NO PUEDE HABER 2 CIUDADES EN EL MISMO PUNTO
