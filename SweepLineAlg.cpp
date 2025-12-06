#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

struct Point
{
    double x, y;
    bool operator<(const Point &other) const
    {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
};

struct Segment
{
    Point p1, p2;
};

// Check orientation for direction
int orientation(Point a, Point b, Point c)
{
    double val = (b.y - a.y) * (c.x - b.x) -
                 (b.x - a.x) * (c.y - b.y);
    if (fabs(val) < EPS)
        return 0;             // colinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// Check if point q lies on segment pr
bool onSegment(Point p, Point q, Point r)
{
    return q.x <= max(p.x, r.x) + EPS && q.x + EPS >= min(p.x, r.x) &&
           q.y <= max(p.y, r.y) + EPS && q.y + EPS >= min(p.y, r.y);
}

// Intersection check for two segments
bool doIntersect(Point p1, Point q1, Point p2, Point q2, Point &intersection)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
    {
        // Compute intersection point using line equations
        double a1 = q1.y - p1.y;
        double b1 = p1.x - q1.x;
        double c1 = a1 * p1.x + b1 * p1.y;

        double a2 = q2.y - p2.y;
        double b2 = p2.x - q2.x;
        double c2 = a2 * p2.x + b2 * p2.y;

        double det = a1 * b2 - a2 * b1;

        if (fabs(det) < EPS)
            return false; // Lines are parallel

        intersection.x = (b2 * c1 - b1 * c2) / det;
        intersection.y = (a1 * c2 - a2 * c1) / det;
        return true;
    }

    // Special Cases
    if (o1 == 0 && onSegment(p1, p2, q1))
    {
        intersection = p2;
        return true;
    }
    if (o2 == 0 && onSegment(p1, q2, q1))
    {
        intersection = q2;
        return true;
    }
    if (o3 == 0 && onSegment(p2, p1, q2))
    {
        intersection = p1;
        return true;
    }
    if (o4 == 0 && onSegment(p2, q1, q2))
    {
        intersection = q1;
        return true;
    }

    return false;
}

int main()
{
    vector<vector<vector<int>>> lines = {
        { {1, 5}, {4, 5} },
        { {2, 5}, {10, 1} },
        { {3, 2}, {10, 3} },
        { {6, 4}, {9, 4} },
        { {7, 1}, {8, 1} }
    };

    // vector<vector<vector<int>>> lines = {
    //     {{0, 0}, {5, 5}},
    //     {{1, 5}, {5, 1}},
    //     {{2, 2}, {6, 2}},
    //     {{3, 0}, {3, 6}},
    //     {{4, 4}, {4, 0}}};

    // vector<vector<vector<int>>> lines = {
    //     {{0, 3}, {6, 3}},
    //     {{2, 0}, {2, 6}},
    //     {{1, 1}, {4, 4}},
    //     {{0, 5}, {5, 0}},
    //     {{3, 2}, {5, 2}}};
    vector<Segment> segments;
    for (auto &seg : lines)
    {
        segments.push_back({{(double)seg[0][0], (double)seg[0][1]}, {(double)seg[1][0], (double)seg[1][1]}});
    }

    set<Point> intersections;
    for (int i = 0; i < segments.size(); ++i)
    {
        for (int j = i + 1; j < segments.size(); ++j)
        {
            Point inter;
            if (doIntersect(segments[i].p1, segments[i].p2, segments[j].p1, segments[j].p2, inter))
            {
                intersections.insert(inter);
            }
        }
    }

    cout << "Total Intersections: " << intersections.size() << endl;
    for (auto &pt : intersections)
    {
        cout << "Intersection at: (" << pt.x << ", " << pt.y << ")" << endl;
    }

    return 0;
}
