#pragma once
#include <assimp/types.h>
#include <cml.h>

inline mat4 assimpToCmlMatrix(const aiMatrix4x4& mat) 
{
    mat4 res;
    res.matrix[0][0] = mat.a1; res.matrix[0][1] = mat.a2; res.matrix[0][2] = mat.a3; res.matrix[0][3] = mat.a4;
    res.matrix[1][0] = mat.b1; res.matrix[1][1] = mat.b2; res.matrix[1][2] = mat.b3; res.matrix[1][3] = mat.b4;
    res.matrix[2][0] = mat.c1; res.matrix[2][1] = mat.c2; res.matrix[2][2] = mat.c3; res.matrix[2][3] = mat.c4;
    res.matrix[3][0] = mat.d1; res.matrix[3][1] = mat.d2; res.matrix[3][2] = mat.d3; res.matrix[3][3] = mat.d4;

    // res.matrix[0][0] = mat.a1; res.matrix[1][0] = mat.a2; res.matrix[2][0] = mat.a3; res.matrix[3][0] = mat.a4;
    // res.matrix[0][1] = mat.b1; res.matrix[1][1] = mat.b2; res.matrix[2][1] = mat.b3; res.matrix[3][1] = mat.b4;
    // res.matrix[0][2] = mat.c1; res.matrix[1][2] = mat.c2; res.matrix[2][2] = mat.c3; res.matrix[3][2] = mat.c4;
    // res.matrix[0][3] = mat.d1; res.matrix[1][3] = mat.d2; res.matrix[2][3] = mat.d3; res.matrix[3][3] = mat.d4;

    return res;

}

inline vec3 assimpToCmlVect(aiVector3D& vec) 
{
    vec3 v;
    v.x = vec.x;
    v.y = vec.y;
    v.z = vec.z;
    return v;
}

inline quat assimpToCmlQuat(aiQuaternion& qu)
{
    quat q;
    q.x = qu.x;
    q.y = qu.y;
    q.z = qu.z;
    q.w = qu.w;
    return q;
}
