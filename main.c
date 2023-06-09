#include <malloc.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

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

bool isEmpty(vector *v) {
    return v->size == 0;
}

bool isFull(vector *v) {
    return v->size == v->capacity;
}

int getVectorValue(vector *v, size_t i) {
    return *(v->data + i);
}

void pushBack(vector *v, int x) {
    *(v->data + v->size) = x;
    if (v->size == v->capacity && v->capacity != 0) {
            reserve(v, v->capacity * 2);
    } else if (v->size == v->capacity && v->capacity == 0) {
        reserve(v, 1);
    }
    v->size++;
}

void popBack(vector *v) {
    if (v->size > 0) {
        v->size--;
    } else {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
}

int* atVector(vector *v, size_t index) {
    if (index < v->size) {
        return v->data + index;
    } else {
        fprintf(stderr, "IndexError: a[%llu] is not exists", index);
        exit(1);
    }
}

int* back(vector *v) {
    return v->data + (v->size - 1);
}

int* front(vector *v) {
    return v->data;
}

void test_pushBack_emptyVector() {
    vector v = createVector(10);
    assert(v.size == 0);
    pushBack(&v, 2);
    assert(v.size == 1);
    assert(*(v.data) == 2);
    assert(v.capacity == 10);
    pushBack(&v, 3);
    assert(v.size == 2);
    assert(*(v.data + 1) == 3);
    assert(v.capacity == 10);

    v = createVector(0);
    assert(v.size == 0);
    pushBack(&v, 2);
    assert(v.size == 1);
    assert(*(v.data) == 2);
    assert(v.capacity == 1);
}

void test_pushBack_fullVector() {
    vector v = createVector(1);
    v.size = 1;
    pushBack(&v, 2);
    assert(v.size == 2);
    assert(*(v.data + 1) == 2);
    assert(v.capacity == 2);
    pushBack(&v, 3);
    assert(v.size == 3);
    assert(*(v.data + 2) == 3);
    assert(v.capacity == 4);
}

void test_pushBack_notFullyFilledVector() {
    vector v = createVector(4);
    v.size = 3;
    pushBack(&v, 5);
    assert(v.size == 4);
    assert(*(v.data + 3) == 5);
    assert(v.capacity == 4);
}

void test_popBack_notEmptyVector() {
    vector v = createVector(0);
    pushBack(&v, 10);

    assert(v.size == 1);
    popBack(&v);
    assert(v.size == 0);
    assert(v.capacity == 1);
}

void test_atVector_notEmptyVector() {
    vector v = createVector(5);
    v.size = 5;
    int *ptr = atVector(&v, 1);
    assert(ptr == v.data + 1);
}

void test_atVector_requestToLastElement() {
    vector v = createVector(5);
    v.size = 5;
    int *ptr = atVector(&v, 4);
    assert(ptr == v.data + 4);
}

void test_back_oneElementInVector() {
    vector v = createVector(5);
    v.size = 1;
    int *ptr = back(&v);
    assert(ptr == v.data + (v.size - 1));
}

void test_front_oneElementInVector() {
    vector v = createVector(5);
    v.size = 1;
    int *ptr = front(&v);
    assert(ptr == v.data);
}

void test() {
    test_pushBack_emptyVector();
    test_pushBack_fullVector();
    test_pushBack_notFullyFilledVector();
    test_popBack_notEmptyVector();
    test_atVector_notEmptyVector();
    test_atVector_requestToLastElement();
    test_back_oneElementInVector();
    test_front_oneElementInVector();
}

int main() {
    test();

    return 0;
}
