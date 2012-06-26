#include "vector3D.hpp"
#include <cmath>

Vector3D::Vector3D()
{
    X = 0;
    Y = 0;
    Z = 0;
}

Vector3D::Vector3D(float x,float y,float z)
{
    X = x;
    Y = y;
    Z = z;
}

Vector3D::Vector3D(const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
}

Vector3D::Vector3D(const Vector3D & from,const Vector3D & to)
{
    X = to.X - from.X;
    Y = to.Y - from.Y;
    Z = to.Z - from.Z;
}

Vector3D & Vector3D::operator= (const Vector3D & v)
{
    X = v.X;
    Y = v.Y;
    Z = v.Z;
    return *this;
}

Vector3D & Vector3D::operator+= (const Vector3D & v)
{
    X += v.X;
    Y += v.Y;
    Z += v.Z;
    return *this;
}

Vector3D Vector3D::operator+ (const Vector3D & v) const
{
    Vector3D t = *this;
    t += v;
    return t;
}

Vector3D & Vector3D::operator-= (const Vector3D & v)
{
    X -= v.X;
    Y -= v.Y;
    Z -= v.Z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D & v) const
{
    Vector3D t = *this;
    t -= v;
    return t;
}

Vector3D & Vector3D::operator*= (const float a)
{
    X *= a;
    Y *= a;
    Z *= a;
    return *this;
}

Vector3D Vector3D::operator* (const float a)const
{
    Vector3D t = *this;
    t *= a;
    return t;
}

Vector3D operator* (const float a,const Vector3D & v)
{
    return Vector3D(v.X*a,v.Y*a,v.Z*a);
}

Vector3D & Vector3D::operator/= (const float a)
{
    X /= a;
    Y /= a;
    Z /= a;
    return *this;
}

Vector3D Vector3D::operator/ (const float a)const
{
    Vector3D t = *this;
    t /= a;
    return t;
}

Vector3D Vector3D::crossProduct(const Vector3D & v)const
{
    Vector3D t;
    t.X = Y*v.Z - Z*v.Y;
    t.Y = Z*v.X - X*v.Z;
    t.Z = X*v.Y - Y*v.X;
    return t;
}

float Vector3D::length()const
{
    return sqrt( X*X + Y*Y + Z*Z);
}

Vector3D & Vector3D::normalize()
{
    (*this) /= length();
    return (*this);
}
