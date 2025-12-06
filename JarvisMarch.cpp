#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    // For sorting/printing
    bool operator<(const Point& p) const {
        return (x < p.x) || (x == p.x && y < p.y);
    }
};

// To find orientation of ordered triplet (p, q, r).
// Returns:
// 0 --> collinear
// 1 --> clockwise
// 2 --> counterclockwise
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;           // collinear
    return (val > 0) ? 1 : 2;         // 1: clockwise, 2: counterclockwise
}

void jarvisConvexHull(Point points[], int n) {
    if (n < 3) {
        cout << "Convex hull not possible\n";
        return;
    }

    vector<Point> hull;

    // Step 1: Find the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++) {
        if (points[i] < points[leftmost])
            leftmost = i;
    }

    // Step 2: Wrap the hull
    int p = leftmost, q;
    do {
        hull.push_back(points[p]);
        q = (p + 1) % n;

        for (int i = 0; i < n; i++) {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }

        p = q;
    } while (p != leftmost);

    // Output
    cout << "Convex Hull Points (Jarvis March):\n";
    for (auto pt : hull)
        cout << "(" << pt.x << ", " << pt.y << ")\n";
    cout << endl;
}
int main() {
    Point points1[] = {{0, 0}, {1,1}, {2,2}, {3,1}, {3,0}, {1, -1}};
    Point points2[] = {{0, 0}, {0, 3}, {5, 1}, {3, 4}, {0, 6}, {3, 0}, {2, 2}, {1, 4}};
    Point points3[] = {{0, 0}, {-8, 0}, {-3, 3}, {-5, 0}, {3, 1}, {1, 2}, {3, 4}, {0, 6}, {-1, -2}};

    int n1 = sizeof(points1) / sizeof(points1[0]);
    int n2 = sizeof(points2) / sizeof(points2[0]);
    int n3 = sizeof(points3) / sizeof(points3[0]);

    cout << "Jarvis March Test Case 01:\n";
    jarvisConvexHull(points1, n1);

    cout << "Jarvis March Test Case 02:\n";
    jarvisConvexHull(points2, n2);

    cout << "Jarvis March Test Case 03:\n";
    jarvisConvexHull(points3, n3);

    return 0;
}

