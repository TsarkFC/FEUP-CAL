/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku()
{
	this->initialize();
}

/**
 * Inicia um Sudoku com um conte�do inicial.
 * Lanca excepcao IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem numeros repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9])
{
	this->initialize();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (nums[i][j] != 0)
			{
				int n = nums[i][j];
				numbers[i][j] = n;
				lineHasNumber[i][n] = true;
				columnHasNumber[j][n] = true;
				block3x3HasNumber[i / 3][j / 3][n] = true;
				countFilled++;
			}
		}
	}
}

void Sudoku::initialize()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			for (int n = 0; n < 10; n++)
			{
				numbers[i][j] = 0;
				lineHasNumber[i][n] = false;
				columnHasNumber[j][n] = false;
				block3x3HasNumber[i / 3][j / 3][n] = false;
			}
		}
	}

	this->countFilled = 0;
}

/**
 * Obtem o conteudo actual (so para leitura!).
 */
int** Sudoku::getNumbers()
{
	int** ret = new int*[9];

	for (int i = 0; i < 9; i++)
	{
		ret[i] = new int[9];

		for (int a = 0; a < 9; a++)
			ret[i][a] = numbers[i][a];
	}

	return ret;
}

/**
 * Verifica se o Sudoku ja esta completamente resolvido
 */
bool Sudoku::isComplete()
{
	return countFilled == 9 * 9;
}



/**
 * Resolve o Sudoku.
 * Retorna indicacao de sucesso ou insucesso (sudoku impossivel).
 */
bool Sudoku::solve()
{
    if (isComplete()) return true;

    /***Greedy -> check easiest option***/

    int array[9][9];
    int nums[9][9][9];

    //array initialization
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            array[i][j] = 0;
        }
    }

    //nums initialization
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            for (int k = 0; k < 9; k++){
                nums[i][j][k] = 0;
            }
        }
    }

    int min[3];
    min[0] = 11;

    //find possibilities
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (numbers[row][col] != 0) continue;

            //space is empty
            for (int n = 1; n <= 9; n++) {
                if (lineHasNumber[row][n] | columnHasNumber[col][n] | block3x3HasNumber[row/3][col/3][n]) continue;
                array[row][col]++;
                nums[row][col][n-1] = n;
            }
            if (array[row][col] < min[0] && array[row][col] > 0){
                min[0] = array[row][col];
                min[1] = row;
                min[2] = col;
            }
        }

    }

    //fill sudoku
    int row = min[1], col = min[2], num;

    for (int n = 1; n <= 9; n++){
        if (nums[row][col][n-1] != 0){
            num = n;
            numbers[row][col] = n;
            lineHasNumber[row][n] = true;
            columnHasNumber[col][n] = true;
            block3x3HasNumber[row / 3][col / 3][n] = true;

            countFilled++;

            if (solve()) return true;

            numbers[row][col] = 0;
            lineHasNumber[row][num] = false;
            columnHasNumber[col][num] = false;
            block3x3HasNumber[row / 3][col / 3][num] = false;

            countFilled--;
        }
    }
    return false;
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print()
{
	for (int i = 0; i < 9; i++)
	{
		for (int a = 0; a < 9; a++)
			cout << this->numbers[i][a] << " ";

		cout << endl;
	}
}
