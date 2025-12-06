#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>
using namespace std;

struct Point
{
    int x, y;
};

// Utility: Compare by x and y
bool compareX(Point a, Point b) { return a.x < b.x; }
bool compareY(Point a, Point b) { return a.y < b.y; }

// Euclidean distance
float distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Brute force for small subsets
pair<Point, Point> bruteForce(vector<Point> &points, int left, int right, float &minDist)
{
    pair<Point, Point> bestPair;
    minDist = FLT_MAX;

    for (int i = left; i <= right; ++i)
    {
        for (int j = i + 1; j <= right; ++j)
        {
            float d = distance(points[i], points[j]);
            if (d < minDist)
            {
                minDist = d;
                bestPair = {points[i], points[j]};
            }
        }
    }

    return bestPair;
}

// Check strip area
pair<Point, Point> stripClosest(vector<Point> &strip, float d, float &minDist)
{
    pair<Point, Point> bestPair;
    sort(strip.begin(), strip.end(), compareY);
    minDist = d;

    for (int i = 0; i < strip.size(); ++i)
    {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j)
        {
            float distTemp = distance(strip[i], strip[j]);
            if (distTemp < minDist)
            {
                minDist = distTemp;
                bestPair = {strip[i], strip[j]};
            }
        }
    }

    return bestPair;
}

// Recursive divide-and-conquer
pair<Point, Point> closestUtil(vector<Point> &pointsSortedX, int left, int right, float &minDist)
{
    if ((right - left) <= 3)
        return bruteForce(pointsSortedX, left, right, minDist);

    int mid = (left + right) / 2;
    Point midPoint = pointsSortedX[mid];

    float dl, dr;
    pair<Point, Point> leftPair = closestUtil(pointsSortedX, left, mid, dl);
    pair<Point, Point> rightPair = closestUtil(pointsSortedX, mid + 1, right, dr);

    pair<Point, Point> bestPair;
    if (dl < dr)
    {
        minDist = dl;
        bestPair = leftPair;
    }
    else
    {
        minDist = dr;
        bestPair = rightPair;
    }

    // Build strip
    vector<Point> strip;
    for (int i = left; i <= right; ++i)
    {
        if (abs(pointsSortedX[i].x - midPoint.x) < minDist)
            strip.push_back(pointsSortedX[i]);
    }

    float stripDist;
    pair<Point, Point> stripPair = stripClosest(strip, minDist, stripDist);

    if (stripDist < minDist)
    {
        minDist = stripDist;
        bestPair = stripPair;
    }

    return bestPair;
}

// Main function
pair<Point, Point> closestPair(vector<Point> &points, float &minDist)
{
    vector<Point> pointsSortedX = points;
    sort(pointsSortedX.begin(), pointsSortedX.end(), compareX);
    return closestUtil(pointsSortedX, 0, pointsSortedX.size() - 1, minDist);
}

int main(){
// {
    // vector<Point> points = {
    //     {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};

    // vector<Point> points = {
    //     {10, 10}, {11, 10}, {100, 100}, {110, 110}, {10, 11}, {200, 200}};

    vector<Point> points = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {5, 5}, {100, 100}};

    float minDist;
    pair<Point, Point> result = closestPair(points, minDist);

    cout << "Closest Pair: (" << result.first.x << ", " << result.first.y
         << ") and (" << result.second.x << ", " << result.second.y << ")\n";
    cout << "Distance: " << minDist << endl;

    return 0;
}
