#include <cstdio>
#include <cmath>

const double EPS = 1e-12;

class Point {
 public:
  double x, y, z;

  Point() : x(0), y(0), z(1) {}
  Point(double x, double y) : x(x), y(y), z(1) {}
  Point(double x, double y, double z) : x(x), y(y), z(z) {}

  bool operator==(Point other) {
    return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS && fabs(z - other.z) < EPS);
  }

  Point operator+(Point other) {
    return Point(x + other.x, y + other.y, z + other.z);
  }

  Point normalize() {
    x = x / z;
    y = y / z;
    z = 1;
  }

  double dot(Point other) {
    return x * other.x + y * other.y + z * other.z;
  }

  Point cross(Point other) {
    return Point(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
  }

  void print(bool newline=true) {
    printf("%lf %lf %lf", x, y, z);
    if (newline)
      printf("\n");
  }
};

bool are_orthogonal(Point p, Point l) {
  return (p.dot(l) == 0);
}

Point line_through_two_points(Point p, Point q) {
  return p.cross(q);
}

Point intersection(Point l, Point m) {
  return l.cross(m);
}

Point parellel_to_through_point(Point l, Point p) {
  auto q = l.cross(Point(0, 0, 1));
  return p.cross(q);
}

Point perpendicular_to_through_point(Point l, Point p) {
  auto q = l.cross(Point(0, 0, 1));
  Point q_orth(q.y, -q.x, 0);
  return p.cross(q_orth);
}

Point projection_on_line(Point p, Point l) {
  auto m = perpendicular_to_through_point(l, p);
  return m.cross(l);
}

int main() {
  Point a(2, 2, 1);
  Point b(3, -2, 1);
  Point c(-4, -1, 1);
  Point d(-2, 3, 1);
  auto l = line_through_two_points(a, c);
  auto m = line_through_two_points(b, d);
  auto e = intersection(l, m);
  e.normalize();
  // expected: 0 1 1
  e.print();
  return 0;
}
