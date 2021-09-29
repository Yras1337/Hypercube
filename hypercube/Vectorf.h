#pragma once
class Vector3f {
public:
    float x, y, z;
    Vector3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};
class Vector4f {
public:
    float x, y, z, w;
    Vector4f(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
};