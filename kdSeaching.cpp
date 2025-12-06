#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Node {
    Point point;
    int axis; // 0 => split on x, 1 => split on y
    Node *left, *right;
    Node(Point p, int a) : point(p), axis(a), left(NULL), right(NULL) {}
};

bool cmpX(const Point &a, const Point &b) {
    return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}
bool cmpY(const Point &a, const Point &b) {
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

// Build KD-tree recursively
Node* buildKDTree(vector<Point> points, int depth = 0) {
    if (points.empty()) return NULL;

    int axis = depth % 2;
    if (axis == 0)
        sort(points.begin(), points.end(), cmpX);
    else
        sort(points.begin(), points.end(), cmpY);

    int median = points.size() / 2;
    Point nodePoint = points[median];

    cout << "Depth " << depth << ": split on "
         << (axis == 0 ? "x (vertical)" : "y (horizontal)")
         << ", node [" << nodePoint.x << "," << nodePoint.y << "]\n";

    vector<Point> leftPoints(points.begin(), points.begin() + median);
    vector<Point> rightPoints(points.begin() + median + 1, points.end());

    Node *node = new Node(nodePoint, axis);
    node->left = buildKDTree(leftPoints, depth + 1);
    node->right = buildKDTree(rightPoints, depth + 1);
    return node;
}

bool pointInRange(Point p, Point minR, Point maxR) {
    return (p.x >= minR.x && p.x <= maxR.x &&
            p.y >= minR.y && p.y <= maxR.y);
}

bool pointLEQv(Point p, Point v) {
    return (p.x <= v.x && p.y <= v.y);
}

// Search KD-tree for points in range R and <= v
void searchKDTree(Node *node, Point v, Point minR, Point maxR, vector<Point> &found) {
    if (!node) return;

    Point p = node->point;
    if (pointInRange(p, minR, maxR) && pointLEQv(p, v)) {
        found.push_back(p);
    }

    int axis = node->axis;
    if (axis == 0) { // split by x
        if (minR.x <= p.x) searchKDTree(node->left, v, minR, maxR, found);
        if (maxR.x >= p.x) searchKDTree(node->right, v, minR, maxR, found);
    } else { // split by y
        if (minR.y <= p.y) searchKDTree(node->left, v, minR, maxR, found);
        if (maxR.y >= p.y) searchKDTree(node->right, v, minR, maxR, found);
    }
}

int main() {
    vector<Point> points = {
        {1,9}, {2,3}, {4,1}, {3,7}, {5,4}, {6,8}, {7,2}, {8,8}, {7,9}, {9,6}
    };

    cout << "Building KD-tree:\n";
    Node *root = buildKDTree(points);

    vector<pair<Point, pair<Point, Point>>> tests = {
        {{2,3}, {{3,7}, {7,9}}},
        {{8,8}, {{4,1}, {9,9}}},
        {{7,9}, {{1,1}, {8,9}}}
    };

    for (int i = 0; i < (int)tests.size(); i++) {
        vector<Point> found;
        Point v = tests[i].first;
        Point minR = tests[i].second.first;
        Point maxR = tests[i].second.second;

        searchKDTree(root, v, minR, maxR, found);

        cout << "\nTest " << i+1 << ": v=[" << v.x << "," << v.y << "], R=[[" 
             << minR.x << "," << minR.y << "],[" << maxR.x << "," << maxR.y << "]]\n";
        cout << "Found " << found.size() << " points: ";
        for (auto &pt : found) {
            cout << "[" << pt.x << "," << pt.y << "] ";
        }
        cout << "\n";
    }

    return 0;
}
