#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Neka 2D point structure
struct Point {
    double x;
    double y;
};

// Func za scaling
Point scalePoint(const Point& p, double sx, double sy) {
    Point result;
    result.x = sx * p.x;
    result.y = sy * p.y;
    return result;
}

// Func za rotacija (agol vo stepeni)
Point rotatePoint(const Point& p, double angleDegrees) {
    double angleRadians = angleDegrees * M_PI / 180.0;
    Point result;
    result.x = p.x * cos(angleRadians) - p.y * sin(angleRadians); //cmath ako raboti
    result.y = p.x * sin(angleRadians) + p.y * cos(angleRadians); //znae nekogash da ne raboti
    return result;
}

int main() {
    // tocka za proba
    Point p = {3.0, 4.0};

    //za Scale
    double sx = 2.0; // scale x za 2
    double sy = 0.5; // scale y za 0.5

    // za Rotacija
    double angle = 45.0; // stepeni

    // Neka scaling
    Point scaledPoint = scalePoint(p, sx, sy);
    cout << "Scaled Point: (" << scaledPoint.x << ", " << scaledPoint.y << ")\n";

    // Neka rotacija
    Point rotatedPoint = rotatePoint(p, angle);
    cout << "Rotiran Point: (" << rotatedPoint.x << ", " << rotatedPoint.y << ")\n";

    // neka scaling pa rotacija
    Point scaledThenRotated = rotatePoint(scaledPoint, angle);
    cout << "Scaled pa Rotiran Point: (" << scaledThenRotated.x << ", " << scaledThenRotated.y << ")\n";

    // neka rotacija pa scaling
    Point rotatedThenScaled = scalePoint(rotatedPoint, sx, sy);
    cout << "Rotiran pa Scaled Point: (" << rotatedThenScaled.x << ", " << rotatedThenScaled.y << ")\n";

    return 0;
}
