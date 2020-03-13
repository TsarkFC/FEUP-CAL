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
    vector<int> indexes = checkPossibilities();

    if (indexes[0] == -1) return false;

    numbers[indexes[0]][indexes[1]] = indexes[2];

    solve();
}

vector<int> Sudoku::checkPossibilities() {
    //Greedy element -> check easiest option
    int array[9][9];

    for (int i = 0; i < 9; i++){ //array initialization
        for (int j = 0; j < 9; j++){
            array[i][j] = 0;
        }
    }

    vector<int> ret = {-1,-1, 0};
    int min = 11;
    int guess;

    for (int row = 0; row < 9; row++){ //find possibilities
        for (int col = 0; col < 9; col++){
            if (numbers[row][col] != 0) continue;
            for (int n = 0; n < 10; n++){
                if (lineHasNumber[row][n] | columnHasNumber[col][n] | block3x3HasNumber[row][col][n]) continue;
                array[row][col]++;
                guess = n;
            }

            if (array[row][col] < min && array[row][col] > 0) {
                ret[0] = row;
                ret[1] = col;
                ret[2] = guess;
                lineHasNumber[row][guess] = true;
                columnHasNumber[col][guess] = true;
                block3x3HasNumber[row][col][guess] = true;
            }

        }
    }

    return ret;
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
