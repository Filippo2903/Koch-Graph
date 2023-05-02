#include <iostream>
#include <cmath>
#include "../lib/vector.h"
#include "../lib/coords2d.h"
using namespace std;

vector<Coords2D> find_points(Coords2D from, Coords2D to) {
    vector<Coords2D> points;

    points.push_back(from);

    double m = (to.y - from.y) / (to.x - from.x);

    Coords2D midpoint = Coords2D(from.x + ((to.x - from.x) / 2), from.y + ((to.y - from.y) / 2));

    Coords2D point_at_one_third = Coords2D(from.x + ((to.x - from.x) / 3), from.y + ((to.y - from.y) / 3));
    points.push_back(point_at_one_third);

    // calculate the top vertex of the triangle
    double side_length = sqrt(pow(point_at_one_third.x - from.x, 2) + pow(point_at_one_third.y - from.y, 2));
    double height = side_length * sqrt(3) / 2;

    points.push_back( from.x > to.x ?
                      Coords2D(midpoint.x - (height * sin(atan(m))), midpoint.y + (height * cos(atan(m)))) :
                      Coords2D(midpoint.x + (height * sin(atan(m))), midpoint.y - (height * cos(atan(m))))
    );

    points.emplace_back(from.x + (((to.x - from.x) / 3) * 2), from.y + (((to.y - from.y) / 3) * 2));

    points.push_back(to);

    return points;
}

vector<Coords2D> curve_points(Coords2D from, Coords2D to, short count) {
    vector<Coords2D> points = find_points(from, to);
    for (short i = 0; i < count; i++) {
        vector<Coords2D> work_points = points;
        points.clear();
        for (long int j = 1; j < work_points.size(); j++) {
            points += find_points(work_points[j - 1], work_points[j]);

            if (j < work_points.size() - 1)
                points.pop_back();
        }
    }

    return points;
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        cout << "Usage: Koch_curve.exe <from.x> <from.y> <to.x> <to.y> <count>";
        return 1;
    }

    Coords2D from = Coords2D(stoi(argv[1]), stoi(argv[2]));
    Coords2D to = Coords2D(stoi(argv[3]), stoi(argv[4]));
    short count = (short) stoi(argv[5]);

    if (count > 8) {
        cout << "count too high!";
        return 1;
    }

    vector<Coords2D> points = curve_points(from, to, count);

    cout << "[ ";
    for (Coords2D point : points)
        cout << point << ", ";
    cout << "]";

    return 0;
}
