#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    double x, y, z;
} Vector3D;

void vector_sum(Vector3D *result, const Vector3D *v1, const Vector3D *v2);
void vector_sub(Vector3D *result, const Vector3D *v1, const Vector3D *v2);
double vector_dot(const Vector3D *v1, const Vector3D *v2);
void vector_cross(Vector3D *result, const Vector3D *v1, const Vector3D *v2);

#endif
