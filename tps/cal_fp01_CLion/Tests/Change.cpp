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
    int vi = 0;

    if (k == 0) return 0;

    if (minCoins(i, k - vi) < minCoins(i-1, k) && k  >= vi) return minCoins(i, k  - vi) + 1;

    else return minCoins(i-1, k);

}

int lastCoin(int i, int k){
    int vi = 0;

    if (k == 0) return 0;

    if (minCoins(i, k - vi) < minCoins(i-1, k) && k >= vi) return lastCoin(i-1, k);

    else return lastCoin(i-1, k);
}

string calcChange(int m, int numCoins, int *coinValues){
    string result = "";
    int INF = m+1;
    int minCoins[m+1];
    int lastCoin[m+1];

    minCoins[0] = 0;
    lastCoin[0] = 0;
    for (int k = 1; k <= m; k++)
        minCoins[k] = INF;

    for (int i = 1; i <= numCoins; i++ )
        for (int k = coinValues[i-1]; k <= m; k++)
            if (minCoins[k-coinValues[i-1]] < minCoins[k]) {
                minCoins[k] = 1 + minCoins[k - coinValues[i - 1]];
                lastCoin[k] = coinValues[i - 1];
            }

    if (minCoins[m] == INF)
        return "-";

    for (int k = m; k > 0; k -= lastCoin[k])
        result += to_string(lastCoin[k]) + ";";

    return result;
}


