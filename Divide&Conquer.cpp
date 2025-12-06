#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& p) const {
        return (x < p.x) || (x == p.x && y < p.y);
    }
};

// Cross product of vectors OA and OB
int cross(Point O, Point A, Point B) {
    return (A.x - O.x) * (B.y - O.y) -
           (A.y - O.y) * (B.x - O.x);
}

// Merge two convex hulls: left and right
vector<Point> mergeHulls(const vector<Point>& left, const vector<Point>& right) {
    int n1 = left.size(), n2 = right.size();

    // Find the rightmost point of left hull
    int i = 0;
    for (int j = 1; j < n1; j++) {
        if (left[j].x > left[i].x)
            i = j;
    }

    // Find the leftmost point of right hull
    int j = 0;
    for (int k = 1; k < n2; k++) {
        if (right[k].x < right[j].x)
            j = k;
    }

    // Find upper tangent
    int upi = i, upj = j;
    bool done = false;
    while (!done) {
        done = true;
        while (cross(right[upj], left[upi], left[(upi + 1) % n1]) > 0)
            upi = (upi + 1) % n1;
        while (cross(left[upi], right[upj], right[(n2 + upj - 1) % n2]) < 0) {
            upj = (n2 + upj - 1) % n2;
            done = false;
        }
    }

    // Find lower tangent
    int lowi = i, lowj = j;
    done = false;
    while (!done) {
        done = true;
        while (cross(right[lowj], left[lowi], left[(n1 + lowi - 1) % n1]) < 0)
            lowi = (n1 + lowi - 1) % n1;
        while (cross(left[lowi], right[lowj], right[(lowj + 1) % n2]) > 0) {
            lowj = (lowj + 1) % n2;
            done = false;
        }
    }

    // Combine points on convex hull
    vector<Point> result;
    int ind = upi;
    result.push_back(left[ind]);
    while (ind != lowi) {
        ind = (ind + 1) % n1;
        result.push_back(left[ind]);
    }

    ind = lowj;
    result.push_back(right[ind]);
    while (ind != upj) {
        ind = (ind + 1) % n2;
        result.push_back(right[ind]);
    }

    return result;
}

// Recursive function to compute convex hull
vector<Point> divideAndConquer(vector<Point>& points, int l, int r) {
    if (r - l + 1 <= 5) {
        // Use brute-force convex hull for small set
        vector<Point> sub(points.begin() + l, points.begin() + r + 1);
        sort(sub.begin(), sub.end());

        vector<Point> hull;

        // Lower hull
        for (auto p : sub) {
            while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], p) <= 0)
                hull.pop_back();
            hull.push_back(p);
        }

        // Upper hull
        int lowerSize = hull.size();
        for (int i = sub.size() - 2; i >= 0; i--) {
            while (hull.size() > lowerSize && cross(hull[hull.size()-2], hull[hull.size()-1], sub[i]) <= 0)
                hull.pop_back();
            hull.push_back(sub[i]);
        }

        hull.pop_back(); // Remove duplicate
        return hull;
    }

    int mid = (l + r) / 2;
    vector<Point> leftHull = divideAndConquer(points, l, mid);
    vector<Point> rightHull = divideAndConquer(points, mid + 1, r);
    return mergeHulls(leftHull, rightHull);
}

void convexHullDivideAndConquer(vector<Point>& points) {
    sort(points.begin(), points.end()); // Sort by x-coordinate
    vector<Point> hull = divideAndConquer(points, 0, points.size() - 1);

    cout << "Convex Hull (Divide and Conquer):\n";
    for (auto p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    vector<Point> points1 = {{0,0}, {0,4}, {-4,0}, {5,0}, {0,-6}, {1, 0}};
    vector<Point> points2 = {{0,0}, {0,3}, {5,1}, {3,4}, {0,6}, { 3,0},{2,2}, {1,4}};
    vector<Point> points3 = {{0,0},{-8,0}, {-3,3},{-5,0}, {3,1},{1,2},{3,4}, {0,6}, {-1,-2}};

    cout << "\nTest Case 1:\n";
    convexHullDivideAndConquer(points1);

    cout << "\nTest Case 2:\n";
    convexHullDivideAndConquer(points2);

    cout << "\nTest Case 3:\n";
    convexHullDivideAndConquer(points3);

    return 0;
}
