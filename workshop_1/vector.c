#include "vector.h"

// Сложение векторов
void vector_sum(Vector3D *result, const Vector3D *v1, const Vector3D *v2) {
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

// Вычитание векторов
void vector_sub(Vector3D *result, const Vector3D *v1, const Vector3D *v2) {
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
}

// Скалярное произведение
double vector_dot(const Vector3D *v1, const Vector3D *v2) {
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

// Векторное произведение
void vector_cross(Vector3D *result, const Vector3D *v1, const Vector3D *v2) {
    result->x = v1->y * v2->z - v1->z * v2->y;
    result->y = v1->z * v2->x - v1->x * v2->z;
    result->z = v1->x * v2->y - v1->y * v2->x;
}
