/**
 * BLG 336E - Analysis of Algorithms II
 * Assignment 2
 * Mustafa Can Caliskan
 * 150200097
*/

#include <iostream>   // For input/output
#include <cmath>      // For distance calculations
#include <vector>     // For vector operations
#include <algorithm>  // For sorting operations
#include <limits>     // For min(), max() functions
#include <fstream>    // To read/write files
#include <chrono>     // For time measurement


using namespace std;

// Structure to represent a point in 2D space
struct Point {
    double x, y;
};

// Helper function to calculate distance between two points
double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)); // The Euclidean distance is utilized.
}

// Helper function to compare points based on x-coordinate, can use this for sorting.
bool compareX(Point p1, Point p2) {
    return p1.x < p2.x; // To sort in ascending order, the comparison condition should be from smallest to largest.
}

// Helper function to compare points based on y-coordinate, can use this for sorting.
bool compareY(Point p1, Point p2) {
    return p1.y < p2.y; // To sort in ascending order, the comparison condition should be from smallest to largest.
}

// Function to find the closest pair of points using brute force.
pair<Point, Point> bruteForceClosestPair(vector<Point>& points, int start, int end) {
    pair<Point, Point> closest_result;
    double min_dist = numeric_limits<double>::max();

    // Traverses all pairs within the range and identifies the pair with the smallest distance.
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            double dist = distance(points[i], points[j]); 
            if (dist < min_dist) {
                min_dist = dist;
                closest_result = {points[i], points[j]};
            }
        }
    }

    return closest_result;
}

pair<Point, Point> closestPair(vector<Point>& points, int start, int end) {

    if (end - start <= 3) // If the interval length is 3 or smaller, it is directly solved using a brute force approach.
        return bruteForceClosestPair(points, start, end);

    // For the divide and conquer approach, we partition the problem by dividing it into halves and recursively calling each sub-part.
    int middle = (start + end) / 2;
    pair<Point, Point> left_pair = closestPair(points, start, middle);
    pair<Point, Point> right_pair = closestPair(points, middle, end);

    pair<Point, Point> closest;
    double min_dist;
    if (distance(left_pair.first, left_pair.second) < distance(right_pair.first, right_pair.second)) {
        closest = left_pair;
        min_dist = distance(left_pair.first, left_pair.second);
    } else {
        closest = right_pair;
        min_dist = distance(right_pair.first, right_pair.second);
    }

    // Points close to the barrier are additionally examined.
    vector<Point> strip;
    for (int i = start; i < end; ++i) {
        if (abs(points[i].x - points[middle].x) < min_dist)
            strip.push_back(points[i]);
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_dist; ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < min_dist) {
                min_dist = dist;
                closest = {strip[i], strip[j]};
            }
        }
    }

    return closest;
}

// Function to remove a pair of points from the point vector. Returns the newly formed vector.
vector<Point> removePairFromVector(vector<Point>& point_vector, pair<Point, Point> point_pair) {
    vector<Point> result_vector;

    for (Point point: point_vector) {
        if (!((point.x == point_pair.first.x && point.y == point_pair.first.y) || 
              (point.x == point_pair.second.x && point.y == point_pair.second.y))) {
            result_vector.push_back(point);
        }
    }

    return result_vector;
}

void findClosestPairOrder(vector<Point> points) {
    vector<pair<Point,Point>> pairs; //add your pairs to this vector
    Point unconnected = {-1,-1}; //set this as the unconnected point if it exists, leave as is otherwise.

    sort(points.begin(), points.end(), compareX);
    while (!points.empty() && points.size() != 1) {
        pair<Point, Point> closest = closestPair(points, 0, points.size());
        // pair<Point, Point> closest = bruteForceClosestPair(points, 0, points.size()); // Added for the purpose of comparing the brute force and divide and conquer methods.
        if ((closest.first.y > closest.second.y) || (closest.first.y == closest.second.y && closest.first.x > closest.second.x)) {
            swap(closest.first, closest.second);
        }
        pairs.push_back(closest);
        points = removePairFromVector(points, closest);
    }

    if (!points.empty()) {
        unconnected = points[0];
    }
   
    for(size_t i = 0; i < pairs.size(); i++){
        cout << "Pair " << i+1 << ": " << pairs[i].first.x << ", " << pairs[i].first.y << " - " << pairs[i].second.x << ", " << pairs[i].second.y << endl;
    }
    if (unconnected.x != -1){
        cout << "Unconnected " << unconnected.x << ", " << unconnected.y;
    }
}

//Read the coordinates from the file and convert them to a vector. Return the vector as a "vector<Point>"
vector<Point> readCoordinatesFromFile(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "File cannot be opened." << endl;
        exit(1);
    }

    double x, y;
    while (file >> x >> y) {
        points.push_back({x, y});
    }

    file.close();
    return points;
}

int main(int argc, char* argv[]) {

    vector<Point> points = readCoordinatesFromFile(argv[1]);

    // The addition of various lines for time measurement.

    // auto start = chrono::high_resolution_clock::now();      // Start measuring time
    findClosestPairOrder(points);
    // auto stop = chrono::high_resolution_clock::now();                       // Stop measuring time
    // auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);       // Calculate the duration
    // cout << "\nTime taken: " << duration.count() << " nanoseconds" << endl;
    return 0;
}
