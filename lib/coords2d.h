#include <ostream>

struct Coords2D {
    double x;
    double y;

    Coords2D(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

std::ostream& operator<<(std::ostream& os, const Coords2D& coord) {
    os << "Coords2D(" << coord.x << ", " << coord.y << ")";
    return os;
}

bool operator==(const Coords2D& p0, const Coords2D& p1) {
    return p0.x == p1.x && p0.y == p1.y;
}

bool operator!=(const Coords2D& p0, const Coords2D& p1) {
    return !(p0 == p1);
}

Coords2D operator+(const Coords2D& p0, const Coords2D& p1) {
    return Coords2D(p0.x + p1.x, p0.y + p1.y);
}

Coords2D operator+=(const Coords2D& p0, const Coords2D& p1) {
    return Coords2D(p0.x + p1.x, p0.y + p1.y);
}
