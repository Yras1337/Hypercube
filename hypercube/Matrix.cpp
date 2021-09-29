#include "Vectorf.h"
#include <vector>
std::vector < std::vector < float > > vecToMatrix(Vector4f v) {
    std::vector < std::vector < float > > m(4, std::vector < float >(1));
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = v.w;
    return m;
}
Vector3f matrixToVec(std::vector < std::vector < float > > m) {
    return Vector3f(m[0][0], m[1][0], m[2][0]);
}
Vector4f matrixToVec4(std::vector < std::vector < float > > m) {
    return Vector4f(m[0][0], m[1][0], m[2][0], m[3][0]);
}
std::vector < std::vector < float > > matmul(std::vector < std::vector < float > > a, std::vector < std::vector < float > > b) {
    int colsA = a[0].size();
    int rowsA = a.size();
    int colsB = b[0].size();
    int rowsB = b.size();
    std::vector < std::vector < float > > result(rowsA, std::vector < float >(colsB));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            float sum = 0;
            for (int k = 0; k < colsA; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}
Vector3f matmul(std::vector < std::vector < float > > a, Vector4f b) {
    return matrixToVec(matmul(a, vecToMatrix(b)));
}
Vector4f matmul(std::vector < std::vector < float > > a, Vector4f b, bool ch) {
    return matrixToVec4(matmul(a, vecToMatrix(b)));
}