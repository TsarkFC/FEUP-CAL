/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n) {
    if (n == 0 or n == 1) return 1;

    else return n * factorialRecurs(n - 1);
}

int factorialDinam(int n){
    /*SOLUÇÃO NÃO É PROGRAMAÇÃO DINÂMICA
    int ret = 1;

    while (n>1){
        ret *= n;
        n -= 1;
    }

    return ret;*/

    //------------------------------------------------------------------------------------------

    /*Esta solução já se trata de um caso de programação dinâmica uma vez que parte do caso base
     * para um caso mais complexo*/

    if (n == 0 || n == 1) return 1;

    int num = 1;
    int res = 1;

    while (num <= n){
        res *= num;
        num++;
    }

    return res;
}