#pragma once

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Grid
{
public:
	Grid();
	~Grid();
	int puntuation;
	int theStreak;
	void ClearGrid();
	int dimension_x;
	int dimension_y;
	Grid(int dimX, int dimY);
	void print_grid();
	//void gravity();
	void RegenerateEmptyCells();
	void SwapEmpty();
	bool Grid::ValidSwap(int posX1, int posX2, int posY1, int posY2);
	bool Swaping(int posX1, int posX2, int posY1, int posY2);
	int ** grid_table;
	bool checkTargetsHorizontal();
	bool checkTargetsVertical();
	void AddPoints(int counted_Symbols, int Streak);

private:
	// Nº of rows and cols
	
	


	

	


};

