#include <iostream>
#include <cmath>
#include "../lib/vector.h"
#include "../lib/coords2d.h"
using namespace std;

Coords2D up(double x0, double x1, Coords2D midpoint, double height, double m) {
    return x0 > x1 ?
    Coords2D(midpoint.x - (height * sin(atan(m))), midpoint.y + (height * cos(atan(m)))) :
    Coords2D(midpoint.x + (height * sin(atan(m))), midpoint.y - (height * cos(atan(m))));
}

Coords2D down(double x0, double x1, Coords2D midpoint, double height, double m) {
    return x0 < x1 ?
           Coords2D(midpoint.x - (height * sin(atan(m))), midpoint.y + (height * cos(atan(m)))) :
           Coords2D(midpoint.x + (height * sin(atan(m))), midpoint.y - (height * cos(atan(m))));
}

Coords2D find_top_vertex(Coords2D A, Coords2D B, Coords2D (*direction)(double, double, Coords2D, double, double)) {
    double m = (B.y - A.y) / (B.x - A.x);
    double side_length = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
    double height = side_length * sqrt(3) / 2;

    Coords2D midpoint = Coords2D(A.x + ((B.x - A.x) / 2), A.y + ((B.y - A.y) / 2));
    return (*direction)(A.x, B.x, midpoint, height, m);
}

vector<Coords2D> find_points(Coords2D from, Coords2D to) {
    vector<Coords2D> points;

    Coords2D point_at_one_third = Coords2D(from.x + ((to.x - from.x) / 3), from.y + ((to.y - from.y) / 3));
    Coords2D point_at_two_third = Coords2D(from.x + (((to.x - from.x) / 3) * 2), from.y + (((to.y - from.y) / 3) * 2));

    points.push_back(from);

    points.push_back(point_at_one_third);

    points.push_back(find_top_vertex(point_at_one_third, point_at_two_third, down));

    points.emplace_back(point_at_two_third);

    points.push_back(to);

    return points;
}

vector<Coords2D> snowflake_points(Coords2D A, Coords2D B, Coords2D C, short count) {
    vector<Coords2D> points = {A, B, C, A};
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

    Coords2D A = Coords2D(stoi(argv[1]), stoi(argv[2]));
    Coords2D B = Coords2D(stoi(argv[3]), stoi(argv[4]));
    Coords2D C = find_top_vertex(A, B, up);

    short count = (short) stoi(argv[5]) - 1;

    if (count > 8) {
        cout << "count too high!";
        return 1;
    }

    vector<Coords2D> points = snowflake_points(A, B, C, count);

    cout << "[ ";
    for (Coords2D point : points)
        cout << point << ", ";
    cout << "]";

    return 0;
}