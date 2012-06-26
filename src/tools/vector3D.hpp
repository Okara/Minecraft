#ifndef OKARA_VECTOR_HPP_INCLUDED
#define OKARA_VECTOR_HPP_INCLUDED

class Vector3D
{
public:
    float X;
    float Y;
    float Z;

    Vector3D();
    Vector3D(float x,float y,float z);
    Vector3D(const Vector3D & v);
    Vector3D(const Vector3D & from,const Vector3D & to);

    Vector3D & operator= (const Vector3D & v);

    Vector3D & operator+= (const Vector3D & v);
    Vector3D operator+ (const Vector3D & v) const;

    Vector3D & operator-= (const Vector3D & v);
    Vector3D operator- (const Vector3D & v) const;

    Vector3D & operator*= (const float a);
    Vector3D operator* (const float a)const;
    friend Vector3D operator* (const float a,const Vector3D & v);

    Vector3D & operator/= (const float a);
    Vector3D operator/ (const float a)const;

    Vector3D crossProduct(const Vector3D & v)const;
    float length()const;
    Vector3D & normalize();
};


#endif // VECTOR_HPP_INCLUDED
