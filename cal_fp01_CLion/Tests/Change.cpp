/*
 * Change.cpp
 */

#include "Change.h"

/*FORMALIZAÇÃO DO PROBLEMA - alinea a)
 *
 * -Dados de entrada (input):
 *      * neste caso -> serão os argumentos (int m) e (int numCoins);
 *      * V = {v1, v2, ..., vn}; (tipo de moedas)
 *      * |V| = n;
 * -Variáveis de decisão:
 *      * X = {x1, x2, ..., xn}; (quantidade de cada moeda)
 *      * |X| = n;
 * -Função objetivo:
 *      * min(sum(X));
 * -Restriçções:
 *      * X.V = m;
 *
 * */

/*Alinea b) / c)
 *
 *|  i   |   v(i)   |         |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |
 *------------------|---------|-----------------------------------------------------------|
 *|  0   |    0     |mincoins |  0  | inf | inf |             ...                   | inf |
 *|______|__________|lastcoin |
 *|  1   |    1     |mincoins |
 *|______|__________|lastcoin |                     *completar*
 *|  2   |    2     |mincoins |
 *|______|__________|lastcoin |
 *|  3   |    5     |mincoins |
 *|______|__________|lastcoin |
 *
 *V = {0,1,2,5};
 */

int minCoins(int i, int k){
    int vi;

    if (k == 0) return 0;

    if (minCoins(i, k - vi) < minCoins(i-1, k) && k  >= vi) return minCoins(i, k  - vi) + 1;

    else return minCoins(i-1, k);

}

int lastCoin(int i, int k){
    int vi;

    if (k == 0) return 0;

    if (minCoins(i, k - vi) < minCoins(i-1, k) && k >= vi) return lastCoin(i-1, k);

    else return lastCoin(i-1, k);
}

string calcChange(int m, int numCoins, int *coinValues)
{
    return "";
}


