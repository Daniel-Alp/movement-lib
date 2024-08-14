struct Vector {
    // inches
    double x, y;

    Vector();
    Vector(double x, double y); 

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double scalar);

    // rotated counter clockwise about the origin (angle in radians)
    Vector rotate_by(double angle);       
};

struct Pose {
    Vector coordinates;
    double theta; // heading in radians

    Pose();
    Pose(double x, double y, double theta);
    Pose(Vector coordinates, double theta);
};