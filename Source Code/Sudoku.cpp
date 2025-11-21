#include <iostream>
#include <cstdlib>
#include <ctime>

inline void initialize(int array1[9][9], int array2[9][9]);
void generatesolution(int array[9][9]);
bool columnvalid(int array[9][9], int x, int y);
bool gridvalid(int array[9][9], int x, int y);
bool rowvalid(int array[9][9], int x, int y);

void main() {
	srand(time(0));
	int board[9][9], solution[9][9];

	initialize(board, solution);


}

inline void initialize(int array1[9][9], int array2[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			array1[i][j] = 0;
			array2[i][j] = 0;
		}
	}
}

void generatesolution(int array[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			do {
				array[i][j] = rand() % 10 + 1;
			} while (gridvalid(array,i,j) && columnvalid(array,i,j) && rowvalid(array,i,j));
		}
	}
}

bool columnvalid(int array[9][9], int x, int y) {

}

bool gridvalid(int array[9][9], int x, int y) {
	int row = x, column = y;

	//takes the row and column to the start of the 3x3 grid
	while (row % 3 != 0)
		row--;
	while (column % 3 != 0)
		column--;

	//runs until column goes out of 3x3 grid
	do {
		if (x == row && y == column) {//does not compare the grid position if it is same as the position to be validated
			row++;
			if (row % 3 == 0) {
				row - 3;
				column++;
				if (column % 3 == 0) {
					break;
				}
			}
			continue;
		}
		else {//checks if the current grid position duplicates the grid position to be validated
			if (array[row][column] == array[x][y]) {
				return 0;
			}
			else {
				row++;
				if (row % 3 == 0) {
					row - 3;
					column++;
					if (column % 3 == 0) {
						break;
					}
				}
			}
		}
	} while (column % 3 != 0);

	return 1;
}

bool rowvalid(int array[9][9], int x, int y) {

}