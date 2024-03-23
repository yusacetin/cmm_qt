#ifndef POINT_H
#define POINT_H

class Point {
public:
    double x;
    double y;
    Point() {
        x = 0.0;
        y = 0.0;
    }
    Point(double setx, double sety) {
        x = setx;
        y = sety;
    }
};

#endif // POINT_H
