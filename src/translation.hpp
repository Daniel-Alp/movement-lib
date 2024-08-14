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

    // return translation rotated counter clockwise about the origin
    Vector rotate_by(double angle);       
};