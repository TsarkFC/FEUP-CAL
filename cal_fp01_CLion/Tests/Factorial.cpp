/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {
    if (n == 0 or n == 1) return 1;

    else return n * factorialRecurs(n - 1);
}

int factorialDinam(int n){
    if (n == 0 || n == 1) return 1;

    int num = 1;
    int res = 1;

    while (num <= n){
        res *= num;
        num++;
    }

    return res;
}