#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#ifdef _WIN32
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif


typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float x, y, z, w;
} Vec4;

typedef struct {
    float m[16];
} Mat4;


static inline Vec3 vec3_sub(Vec3 a, Vec3 b) {
    Vec3 res = {a.x - b.x, a.y - b.y, a.z - b.z};
    return res;
}

static inline float vec3_dot(Vec3 a, Vec3 b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    Vec3 res = {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
    return res;

    /* примерный алгос <a> X <b>, <a> <b> - вектора
        |  i   j   k  |
        | a.x a.y a.z | = <a> X <b>
        | b.x b.y b.z |   
     
        <a> X <b> = i * det([a.y a.z]) - j * det([a.x a.z]) + k * det([a.x a.y])
                           ([b.y b.z])          ([b.x b.z])          ([b.x b.y])
    */

}

static inline Vec3 vec3_normalize(Vec3 v) {
    float len = v.x*v.x + v.y*v.y + v.z*v.z;
    if (len > 1e-8f) {
        float inv = 1.0f/sqrtf(len);
        Vec3 res = {v.x*inv, v.y*inv, v.z*inv};
        return res;
    }
    Vec3 res = {0.0f, 0.0f, 0.0f};
    return res;
}




EXPORT void mat4_identity(Mat4* out) {
    memset(out->m, 0, 16*sizeof(float));
    out->m[0] = 1.0f;
    out->m[5] = 1.0f;
    out->m[10] = 1.0f;
    out->m[15] = 1.0f;
}

EXPORT void mat4_multiply(const Mat4* a, const Mat4* b, const Mat4* out) {
    Mat4 tmp;
    for (int i = 0; i < 4; i++) {
        int row = i*4;
        for (int j = 0; j < 4; j++) {
            tmp.m[row+j] = 
            a->m[row+0]*b->m[0*4+j] + 
            a->m[row+1]*b->m[1*4+j] + 
            a->m[row+2]*b->m[2*4+j] + 
            a->m[row+3]*b->m[3+4+j];
        }
    }
    memcpy(out->m, tmp.m, 16*sizeof(float));
}

static inline Vec4 mat4_mul_vec4(const Mat4* m, Vec4 v) {
    Vec4 res;
    res.x = m->m[0]*v.x + m->m[1]*v.y + m->m[2]*v.z + m->m[3]*v.w;
    res.y = m->m[4]*v.x + m->m[5]*v.y + m->m[6]*v.z + m->m[7]*v.w;
    res.z = m->m[8]*v.x + m->m[9]*v.y + m->m[10]*v.z + m->m[11]*v.w;
    res.w = m->m[12]*v.x + m->m[13]*v.y + m->m[14]*v.z + m->m[15]*v.w;
    return res;

    /*
    
        (m00 m01 m02 m03)   (x)   (m00*x + m01*y + m02*z + m03*w)
        (m10 m11 m12 m13) * (y) = (m10*x + m11*y + m12*z + m13*w)
        (m20 m21 m22 m23) * (z) = (m20*x + m21*y + m22*z + m23*w)
        (m30 m31 m32 m33)   (w)   (m30*x + m31*y + m32*z + m33*w)

    */

}

