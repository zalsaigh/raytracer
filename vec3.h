#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
    public:
        vec3(): e{0,0,0} {}
        vec3(double e0, double e1, double e2): e{e0, e1, e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double scalar) {
            e[0] *= scalar;
            e[1] *= scalar;
            e[2] *= scalar;
            return *this;
        }

        vec3& operator/=(const double scalar) {
            return *this *= 1/scalar;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double e[3];
};

using point3 = vec3;
using colour = vec3;

// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3 &u)
{
    return out << u.e[0] << ' ' << u.e[1] << ' ' << u.e[2] << "\n";
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
    return vec3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

inline vec3 operator*(const vec3& u, double t)
{
    return vec3(u[0] * t, u[1] * t, u[2] * t);
}

inline vec3 operator*(double t, const vec3& u)
{
    return u * t;
}

inline vec3 operator/(const vec3& u, double t)
{
    return (1/t) * u;
}

inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}
#endif