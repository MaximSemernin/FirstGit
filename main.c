#include <malloc.h>
#include <stdio.h>

typedef struct vector {
    int *data;
    size_t size;
    size_t capacity;
} vector;

vector createVector(size_t n) {
    vector v;
    v.data = (int*)malloc(sizeof(int) * n);
    if (v.data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v.capacity = n;
    v.size = 0;

    return v;
}

void reserve(vector *v, size_t newCapacity) {
    if (newCapacity == 0) {
        v->data = NULL;
        v->capacity = 0;
        v->size = 0;
    } else {
        v->data = (int*)realloc(v->data, sizeof(int) * newCapacity);
        if (v->data == NULL) {
            fprintf(stderr, "bad alloc");
            exit(1);
        }
        v->capacity = newCapacity;
        if (newCapacity < v->size) {
            v->size = newCapacity;
        }
    }
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->data = (int*)realloc(v->data, sizeof(int) * (v->capacity - v->size));
}

void deleteVector(vector *v) {
    free(v->data);
    v->size = 0;
    v->capacity = 0;
}
