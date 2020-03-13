/*
 * Partioning.cpp
 */

#include "Partitioning.h"
#include <vector>
#include <iostream>

using namespace std;

int s_recursive(int n,int k)
{
    if (k == 1 || k == n) return 1;
    else if (k > 1 && n > k) return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
}

int s_dynamic(int n,int k)
{
    int c[n][n];

    for (int i = 0; i < n; i++){
        c[0][i] = 1;
        c[i][i] = 1;

    }

    for (int i = 1; i < k; i++){
        for (int j = 0; j < (n-k); j++){
            cout << c[i][j+i] << " : " << c[i-1][j+i] << "   ->   " << (i+1)*c[i][j+i] + c[i-1][j+i] << endl;
            c[i][j+i+1] = (i+1)*c[i][j+i] + c[i-1][j+i];
        }
    }

    return c[k-1][n-1];
}


int b_recursive(int n)
{
    int sum = 0;

    for (int i = 1; i < n + 1; i++){
        sum += s_recursive(n, i);
    }

    return sum;
}

int b_dynamic(int n)
{
    int sum = 0;

    for (int i = 1; i < n + 1; i++){
        sum += s_dynamic(n, i);
    }

    return sum;
}


