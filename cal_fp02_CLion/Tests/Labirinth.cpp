/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;



Labirinth::Labirinth(int values[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			labirinth[i][j] = values[i][j];
	this->initializeVisited();
}


void Labirinth::initializeVisited()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			visited[i][j] = false;
}




void  Labirinth::printLabirinth()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << visited[i][j] << " ";

		cout << endl;
	}
}


bool Labirinth::findGoal(int x, int y)
{
    visited[x][y] = true;
    bool skip = false;

    if (labirinth[x][y] == 2) return true;

    if ((labirinth[x+1][y] == 1 || labirinth[x+1][y] == 2) && !visited[x+1][y]){
        if (findGoal(x+1, y)) return true;
    }
    if ((labirinth[x][y+1] == 1 || labirinth[x][y+1] == 2) && !visited[x][y+1]){
        if (findGoal(x,y+1)) return true;
    }
    if ((labirinth[x-1][y] == 1 || labirinth[x-1][y] == 2) && !visited[x-1][y]){
        if (findGoal(x-1, y)) return true;
    }
    if ((labirinth[x][y-1] == 1 || labirinth[x][y-1] == 2) && !visited[x][y-1]){
        if (findGoal(x, y-1)) return true;
    }
    return false;
}

