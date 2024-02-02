#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
  float X, Y, Z;

  inline Vector3() {};
  inline Vector3(const float x, const float y, const float z) {
    X = x;
    Y = y;
    Z = z;
  }

  inline Vector3 operator + (const Vector3 &A) const {
    return Vector3(X + A.X, Y + A.Y, Z + A.Z);
  }

  inline Vector3 operator - (const Vector3 &A) const {
    return Vector3(X - A.X, Y - A.Y, Z - A.Z);
  }

  inline Vector3 operator - () {
    return Vector3(-X, -Y, -Z);
  }

  static inline Vector3 zero() {
    return Vector3(0.0f, 0.0f, 0.0f);
  }
};

#endif
