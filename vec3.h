#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class Vec3
{
    public:
        Vec3(): e{0,0,0} {}
        Vec3(double e0, double e1, double e2): e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        Vec3& operator+=(const Vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        Vec3& operator*=(const double scalar) {
            e[0] *= scalar;
            e[1] *= scalar;
            e[2] *= scalar;
            return *this;
        }

        Vec3& operator/=(const double scalar) {
            return *this *= 1/scalar;
        }

        double Length() const {
            return sqrt(LengthSquared());
        }

        double LengthSquared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double e[3];
};

using Point3 = Vec3;
using Colour = Vec3;

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const Vec3 &u)
{
    return out << u.e[0] << ' ' << u.e[1] << ' ' << u.e[2] << "\n";
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline Vec3 operator*(const Vec3& u, double t)
{
    return Vec3(u[0] * t, u[1] * t, u[2] * t);
}

inline Vec3 operator*(double t, const Vec3& u)
{
    return u * t;
}

inline Vec3 operator/(const Vec3& u, double t)
{
    return (1/t) * u;
}

inline double Dot(const Vec3 &u, const Vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 UnitVector(Vec3 v)
{
    return v / v.Length();
}
#endif