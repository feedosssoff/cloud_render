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
    Vec3 res = {b.x - a.x, b.y - a.y, b.z - a.z};
    return res;
}

static inline float vec3_dot(Vec3 a, Vec3 b) {
        return a.x*b.x + a.y*b.y + a.z*b.z;
}

static inline Vec3 vec3_cross(Vec3 a, Vec3 b) {
    res = {
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
    
}