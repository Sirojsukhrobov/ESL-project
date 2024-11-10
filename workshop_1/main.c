#include <stdio.h>
#include "vector.h"

int main() {
    Vector3D v1 = {1.0, 2.0, 3.0};
    Vector3D v2 = {4.0, 5.0, 6.0};
    Vector3D result;
    double dot_product;

    vector_sum(&result, &v1, &v2);
    printf("Sum: (%f, %f, %f)\n", result.x, result.y, result.z);

    vector_sub(&result, &v1, &v2);
    printf("Subtraction: (%f, %f, %f)\n", result.x, result.y, result.z);

    dot_product = vector_dot(&v1, &v2);
    printf("Dot product: %f\n", dot_product);

    vector_cross(&result, &v1, &v2);
    printf("Cross product: (%f, %f, %f)\n", result.x, result.y, result.z);

    return 0;
}
