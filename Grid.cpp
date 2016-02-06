#include "stdafx.h"
#include "Grid.h"


//using namespace rando


Grid::Grid()
{
}

Grid :: Grid(int dimX = 10, int dimY = 10) {
	dimension_x = dimX ;
	dimension_y = dimY ;

	puntuation = 0;
	theStreak = 0;

	grid_table = new int*[dimY];
	for (int i = 0; i < dimY; ++i) {
		grid_table[i] = new int[dimX];
	}
	//grid_table = new int[dimension_x][dimension_y];
	//int matrix[dimX][dimY];
	//grid_table = matrix;


}

void Grid::ClearGrid() {

	for (int i = 0; i < dimension_y; ++i) {
		delete[] grid_table[i];
	}
	delete[] grid_table;
}



Grid::~Grid()
{
}



/*
	SwapEmpty: gets the position of a zero and swaps it with its upper in the same COL
		if its on the top of the col, it will cal generate random instead.

		The optimal way will be to detect the position of a zero in the column and swap the whole rest in a single loop instead
		of doing multiple calls
*/
void Grid:: SwapEmpty() {

	int * newCol= new int [dimension_y]();

	for (int j = 0; j < dimension_y; j++)
	{

		int x_ref = 0;
		int zerosFound = 0;


		// Detect and reorganize 
		for (int i = dimension_x - 1; i >= 0; i--) {

			// A zero is identified
			if (grid_table[i][j]==0 && i> 0){
				zerosFound++;
				//cout << "zero detected \n Nº ZEROS:" <<zerosFound<< "\n" ;
				newCol[zerosFound - 1] = 0;
			}
			else{
				newCol[i + zerosFound] = grid_table[i][j];
			}
		}


			

		// Update the column 
		if (zerosFound != 0) {
			for (int i = 0; i < dimension_x;i++){
			grid_table[i][j] = newCol[i];
			}

		}
		

	}

	/*
	if (col != dimension_y){
		// DO SWAP PROCESS

	

	}
	else {
		//GENERATE A NEW RANDOM CELL INSTEAD


	}
	*/

}


void Grid::RegenerateEmptyCells() {
	
	int max = 4;
	int min = 1;
	int randCounter = 1;

	for (int i = 0; i < dimension_x; i++) {
		for (int j = 0; j < dimension_y; j++) {

			if (grid_table[i][j] == 0)
				grid_table[i][j]=min + ((rand() + randCounter) % (int)(max - min + 1));
		}
	}


}

void Grid::print_grid () 
{

	/*ASCII :
	abcdefghij
	A -> 65 ; a -> 97    97-65 =32
	J -> 74 ; j ->  106    106 -74 = 32 */
	
	for (int i = 0; i < dimension_x; i++) {
		cout << "|";

		for (int j = 0; j < dimension_y; j++) {

			cout << grid_table[i][j] << "|";
		}

		cout << "\n";
	}

}



//Check if its a valid swap
	//Valid if selected points are consecutive in the X or Y axis BUT IT CAN ONLY BE A VERTICAL OR HORIZONTAL MOVE
	//DIAGONALS ARE FORBIDDEN
	//Returns TRUE if the selected where valid

bool Grid::ValidSwap(int posX1, int posX2, int posY1, int posY2) {


	if (posX1 >= dimension_x || posX2 >= dimension_x || posY1 >= dimension_y || posY2 >= dimension_y || posX2 <= 0 || posX1 <= 0 || posY1 <= 0 || posY1 <= 0 ){
	
		cout << "invalid input: out of bounds";
		return false;
	}

	if (posX1 == posX2 )
	{
		cout << "invalid input: X inputs are the same";
	}

	if (posY1 == posY2)
	{
		cout << "invalid input: Y inputs are the same";
	}

	if (((std::abs(posX1 - posX2) ==1 )&& (std::abs(posY1 - posY2) == 0))
		|| ((std::abs(posY1 - posY2) == 1) && (std::abs(posX1 - posX2) == 0))) {

		return true;
	}


	else {
		cout << "invalid input: not contiguous";
		return false;
	}
		
}




/*
Swaping: we interchange two contiguous cells, if CHECKTARGET() returns a positive response, the new Grid will suplant the actual grid.
*/
bool Grid::Swaping(int posX1, int posX2, int posY1, int posY2) {

	// STEP 1: GENERATE A NEW GRID WHERE THE 
	Grid newGrid = Grid(dimension_x, dimension_y);
	int Po1x, Po2x, Po1y, Po2y;

	// 1 is the pos associated to the first move
	int posA = grid_table[posX1][posY1];
	int posB = grid_table[posX2][posY2];

	//for

	// SWAP THE POSITIONS OF BOTH POSITIONS

	if (ValidSwap(posX1,posX2,posY1,posY2)) {

	// Create a duplicate
	for (int i = 0; i < dimension_x; i++) {
		for (int j = 0; j < dimension_y; j ++) {
			newGrid.grid_table[i][j] = grid_table[i][j];
		}
	}

	newGrid.grid_table[posX1][posY1] = posB;
	newGrid.grid_table[posX2][posY2] = posA;

	//Debug
	newGrid.print_grid();


	// IF we destroy blocks int the process-> We sustitute our previous grid with this one
	if (newGrid.checkTargetsHorizontal()) {
		grid_table = newGrid.grid_table;
	}

	// ELSE we remain with the original
	else {
		cout << "That moves has NO EFFECT";
	}

	}
		return false;
}


/*
	CheckTargets we check for horizontal and vertical lines
*/
bool Grid::checkTargetsHorizontal() {

	int count;
	int symbol; // the symbol we are checking at the moment

	// HORIZONTAL SEARCH
	
	for (int i = 0; i < dimension_x;i++){
		//count start as 0 in each row (the first count will set it to 1)
		count = 0;		
		symbol = grid_table[0][0];

		for (int j = 0; j < dimension_y; j++) {
			

			// CASE 2: WE CONTINUE FINDING THE SAME SYMBOL
			if (grid_table[i][j] == symbol) {
				count++;
				grid_table[i][j] = 0;
				//cout << "\n\n";
				//print_grid();
				
				if (i+1 == dimension_x) {
					grid_table[i][j] = symbol;
				}

			}

			


			// CASE 2: WE END THE STREAK
			else{
				// Success
				if (count >= 3) {
					theStreak++;  //increase the streak
					AddPoints(count, theStreak);	
					count = 1;// 
				}

				// RESET PREVIOUS VALUES THAT HAS BEEN SET TO -1
				else
				{
					
					for (int streak = 1; streak <= count; streak++) {
						grid_table[i][j - streak] = symbol;
					}
					// 
					symbol = grid_table[i][j];   // We take the new value as the new symbol
					grid_table[i][j] = 0;
					count = 1;
				}
				
			}
		}
	}




	return false;
}



/*
CheckTargets we check for horizontal and vertical lines
*/
bool Grid::checkTargetsVertical() {

	int count;
	int symbol; // the symbol we are checking at the moment

				// HORIZONTAL SEARCH
	symbol = grid_table[0][0];
	for (int i = 0; i < dimension_y; i++) {
		//count start as 0 in each row (the first count will set it to 1)
		count = 0;
		for (int j = 0; j < dimension_x; j++) {


			// CASE 2: WE CONTINUE FINDING THE SAME SYMBOL
			if (grid_table[i][j] == symbol) {
				count++;
				grid_table[i][j] = -1;
				

			}

			// CASE 2: WE END THE STREAK
			else {

				if (count >= 3) {
					theStreak++;  //increase the streak
					AddPoints(count, theStreak);		// 
					count = 1;
				}

				else{
				// RESET PREVIOUS VALUES THAT HAS BEEN SET TO -1
				for (int streak = 1; streak <= count; streak++) {
					grid_table[i][j - streak] = symbol;
				}
				// 
				symbol = grid_table[i][j];   // We take the new value as the new symbol
				grid_table[i][j] = 0;
				count = 1;
				}
			}
		}
	}




	return false;
}


/*
	Count Points:
		Points depend directly in the consecutive streak and the number of   
*/

void Grid::AddPoints(int counted_Symbols, int Streak) {
	cout << counted_Symbols * 10 * Streak;
	puntuation = puntuation + counted_Symbols * 10 * Streak;

}