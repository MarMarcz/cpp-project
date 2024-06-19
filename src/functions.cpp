// functions.cpp

#include "functions.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

float divide(int a, int b) {
    if (b != 0) {
        return static_cast<float>(a) / b;
    } else {
        return 0; // return 0 for division by zero
    }
}
