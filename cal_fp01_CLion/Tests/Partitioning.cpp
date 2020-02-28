/*
 * Partioning.cpp
 */

#include "Partitioning.h"


int s_recursive(int n,int k)
{
    if (k == 1 || k == n) return 1;
    else if (k > 1 && n > k) return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
}

int s_dynamic(int n,int k)
{
    
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
	return 0;
}


