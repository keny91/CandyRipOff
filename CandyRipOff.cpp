// CandyRipOff.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Grid.h"



/*

	THE WAY IT WORKS

	_ PLAYER DECIDES TO SWAP 2 CELLS  (done by writing coordinates)
		- if 3 are now linked -> destroy + score
		- call gravity / generate new cells in the columns that they were destroyed
		- check for any new combinations
		-...
		-no more comb -> reset multiplier + end turn


*/




int main()
{

	Grid TheGrid = Grid(10, 10);


	// Random grid generation, should be a method
	int max = 4;
	int min = 1;
	int randCounter = 1;

	/*
	Manual matrix creation

	int matrix[3][3] = { { 1111, 0, 3 },{ 4444, 0, 6 },{ 1000, 8, 9 } };

	for (int i = 0; i < TheGrid.dimension_y; ++i) {
		TheGrid.grid_table[i] = matrix[i];
	}
	*/
	//TheGrid.grid_table = matrix;
	




	/* Originate the original matrix*/
	for (int a = 0; a < TheGrid.dimension_x; a++) {
		for (int b = 0; b < TheGrid.dimension_y; b++) {
			//randCounter ++;
			TheGrid.grid_table[a][b] = min + ((rand()+randCounter)% (int)(max - min + 1));
			//cout << "\n" << matrix[a][b] << "\n";
			//cout << "\n" << a << b << "\n";
			//TheGrid.grid_table[a][b] = matrix[a][b];
		}
	}	

	
	TheGrid.print_grid();
	cout << "\n" ;


	cout << "\nGENERATE ZEROS\n";
	TheGrid.grid_table[5][0] = 0;
	TheGrid.grid_table[5][1] = 0;
	TheGrid.grid_table[1][0] = 0;
	TheGrid.grid_table[3][0] = 0;
	TheGrid.print_grid();

	cout << "\nZEROS GO TOP\n";

	TheGrid.SwapEmpty();
	TheGrid.print_grid();

	cout << "\nSUSTITUTE ZEROS\n";
	TheGrid.RegenerateEmptyCells();
	TheGrid.print_grid();


    return 0;
}

