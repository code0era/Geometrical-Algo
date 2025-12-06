#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

// Global reference point for sorting
Point p0;

int orientation(Point p, Point q, Point r) {
    // >0: clockwise, <0: counter-clockwise, =0: collinear
    return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
}

int distSq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool compare(Point p1, Point p2) {
    int o = orientation(p0, p1, p2);
    if (o == 0)
        return distSq(p0, p1) < distSq(p0, p2); // Keep closer point
    return o < 0; // Counter-clockwise first
}

void convexHull(Point points[], int n) {
    if (n < 3) {
        cout << "Convex hull not possible\n";
        return;
    }

    // Step 1: Find the bottom-most point
    int minIdx = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[minIdx].y ||
            (points[i].y == points[minIdx].y && points[i].x < points[minIdx].x))
            minIdx = i;
    }
    swap(points[0], points[minIdx]);
    p0 = points[0];

    // Step 2: Sort by polar angle w.r.t. p0
    sort(points + 1, points + n, compare);

    // Step 3: Remove collinear duplicates from end
    vector<Point> filtered;
    filtered.push_back(points[0]);
    for (int i = 1; i < n; i++) {
        // Skip point if same polar angle and farther than the last one
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        filtered.push_back(points[i]);
    }

    // Step 4: Use stack method
    if (filtered.size() < 3) {
        cout << "Convex hull not possible (after removing collinear points)\n";
        return;
    }

    vector<Point> hull;
    hull.push_back(filtered[0]);
    hull.push_back(filtered[1]);
    hull.push_back(filtered[2]);

    for (int i = 3; i < filtered.size(); i++) {
        while (hull.size() >= 2 &&
               orientation(hull[hull.size() - 2], hull[hull.size() - 1], filtered[i]) >= 0)
            hull.pop_back();
        hull.push_back(filtered[i]);
    }

    // Output result
    cout << "Convex Hull Points (in counter-clockwise order):\n";
    for (auto pt : hull)
        cout << "(" << pt.x << ", " << pt.y << ")\n";
    cout << endl;
}

int main() {
    Point points1[] = {{0, 0}, {1,1}, {2,2}, {3,1}, {3,0}, {1, -1}};
    Point points2[] = {{0, 0}, {0, 3}, {5, 1}, {3, 4}, {0, 6}, {3, 0}, {2, 2}, {1, 4}};
    Point points3[] = {{0, 0}, {-8, 0}, {-3, 3}, {-5, 0}, {3, 1}, {1, 2}, {3, 4}, {0, 6}, {-1, -2}};

    cout << "Graham Scan Test Case 01:\n";
    convexHull(points1, sizeof(points1) / sizeof(points1[0]));

    cout << "Graham Scan Test Case 02:\n";
    convexHull(points2, sizeof(points2) / sizeof(points2[0]));

    cout << "Graham Scan Test Case 03:\n";
    convexHull(points3, sizeof(points3) / sizeof(points3[0]));

    return 0;
}
