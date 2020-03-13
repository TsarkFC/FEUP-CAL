/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>

/*NÃO É UM EXEPLO DE PROGRAMAÇÃO DINÂMINCA*/
string calcSum(int* sequence, int size)
{
    string ret;

    for (int m = 1; m < size + 1; m++){
        ret += minCalc(sequence, size, m);
    }


	return ret;
}

string minCalc(int* sequence, int size, int m){
    string ret = "";

    int min = 1000000;
    int sum = 0;
    int ind = 0;

    for (int i = 0; i < size - m + 1; i++){
        for (int s = 0; s < m; s++){
            sum += sequence[i+s];
        }

        if (sum < min){
            min = sum;
            ind = i;
        }
        sum = 0;
    }

    ret = to_string(min) + "," + to_string(ind) + ";";

    return ret;
}

