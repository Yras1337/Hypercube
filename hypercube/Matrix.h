#pragma once
#include <vector>
#include "Vectorf.h"
std::vector < std::vector < float > > vecToMatrix(Vector4f v);
Vector3f matrixToVec(std::vector < std::vector < float > > m);
Vector4f matrixToVec4(std::vector < std::vector < float > > m);
std::vector < std::vector < float > > matmul(std::vector < std::vector < float > > a, std::vector < std::vector < float > > b);
Vector3f matmul(std::vector < std::vector < float > > a, Vector4f b);
Vector4f matmul(std::vector < std::vector < float > > a, Vector4f b, bool ch);