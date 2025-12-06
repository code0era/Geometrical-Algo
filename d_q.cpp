#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& p) const {
        return (x < p.x) || (x == p.x && y < p.y);
    }

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
};

// Cross product (O → A) × (O → B)
int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Brute-force Convex Hull using Graham's scan (for 5 or fewer points)
vector<Point> bruteHull(vector<Point>& pts) {
    sort(pts.begin(), pts.end());

    vector<Point> hull;
    // Lower hull
    for (const Point& p : pts) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    // Upper hull
    int lowerSize = hull.size();
    for (int i = (int)pts.size() - 2; i >= 0; i--) {
        while ((int)hull.size() > lowerSize && cross(hull[hull.size()-2], hull[hull.size()-1], pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    // Remove duplicate last point
    if (!hull.empty())
        hull.pop_back();

    return hull;
}

// Recursive Divide and Conquer
vector<Point> divideAndConquer(vector<Point>& pts, int l, int r) {
    if (r - l + 1 <= 5) {
        vector<Point> sub(pts.begin() + l, pts.begin() + r + 1);
        return bruteHull(sub);
    }

    int mid = (l + r) / 2;
    vector<Point> leftHull = divideAndConquer(pts, l, mid);
    vector<Point> rightHull = divideAndConquer(pts, mid + 1, r);

    // Merge hulls and return result using Graham scan on combined
    vector<Point> merged = leftHull;
    merged.insert(merged.end(), rightHull.begin(), rightHull.end());
    return bruteHull(merged);
}

// Main Hull Driver
void convexHullDivideAndConquer(vector<Point>& points) {
    sort(points.begin(), points.end()); // Sort by x (and y)
    vector<Point> hull = divideAndConquer(points, 0, points.size() - 1);

    cout << "Convex Hull (Divide and Conquer):\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

// Sample Input Cases
int main() {
    vector<Point> points1 = {{0, 0}, {1,1}, {2,2}, {3,1}, {3,0}, {1, -1}};
    vector<Point> points2 = {{0,0}, {0,3}, {5,1}, {3,4}, {0,6}, {3,0}, {2,2}, {1,4}};
    vector<Point> points3 = {{0,0}, {-8,0}, {-3,3}, {-5,0}, {3,1}, {1,2}, {3,4}, {0,6}, {-1,-2}};

    cout << "\nTest Case 1:\n";
    convexHullDivideAndConquer(points1);

    cout << "\nTest Case 2:\n";
    convexHullDivideAndConquer(points2);

    cout << "\nTest Case 3:\n";
    convexHullDivideAndConquer(points3);

    return 0;
}
