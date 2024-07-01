#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>  

struct Point {
    double x, y;
};

bool comparePoints(Point a, Point b) {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
}

double crossProduct(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

double distance(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool polarOrder(Point a, Point b, Point origin) {
    double cp = crossProduct(origin, a, b);
    if (cp == 0) {
        return distance(origin, a) < distance(origin, b);
    }
    return cp > 0;
}

std::vector<Point> convexHull(std::vector<Point>& points) {
    std::sort(points.begin(), points.end(), comparePoints);
    Point pivot = points[0];
    std::sort(points.begin() + 1, points.end(), [pivot](Point a, Point b) {
        return polarOrder(a, b, pivot);
    });

    std::vector<Point> hull;
    for (const auto& point : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], point) <= 0) {
            hull.pop_back();
        }
        hull.push_back(point);
    }
    return hull;
}

double polygonArea(const std::vector<Point>& points) {
    double area = 0.0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        area += points[i].x * points[(i + 1) % n].y - points[i].y * points[(i + 1) % n].x;
    }
    return std::fabs(area) / 2.0;
}

int main() {
    int N;
    std::cin >> N;
    std::vector<Point> points(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    if (N < 3) {
        printf("0.000\n");
        return 0;
    }

    std::vector<Point> hull = convexHull(points);
    double area = polygonArea(hull);

    printf("%.3f\n", area);

    return 0;
}
