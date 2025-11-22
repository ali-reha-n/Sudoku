#include <iostream>
#include <cstdlib>
#include <ctime>

inline void initialize(int array1[9][9], int array2[9][9]);
void generatesolution(int array[9][9]);
bool columnvalid(int array[9][9], int x, int y);
bool gridvalid(int array[9][9], int x, int y);
bool rowvalid(int array[9][9], int x, int y);
void display(int array[9][9]);

void main() {
	srand(time(0));
	int board[9][9], solution[9][9];

	initialize(board, solution);

	generatesolution(solution);

	display(solution);


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
			array[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
		}
	}
}

bool columnvalid(int array[9][9], int x, int y) {
	int row = x;
	while (row != 0) {//goes to the end of the column
		row--;
	}
	while (row != 9) {
		if (row == x) {//skips row checking if the indices match
			row++;
			continue;
		}
		else {//checks if a duplicate exists
			if (array[row][y] == array[x][y]) {
				return 0;
			}
			else {
				row++;
			}
		}
	}
	return 1;
}

bool gridvalid(int array[9][9], int x, int y) {
	int row = x, column = y, counter=0;
	//takes the row and column to the start of the 3x3 grid
	while (row % 3 != 0)
		row--;
	while (column % 3 != 0)
		column--;

	//runs until column goes out of 3x3 grid
	for (int i = row; i < row + 3; i++) {
		for (int j = column; j < column + 3; j++) {
			if (i == x && j == y)
				continue;
			if (array[i][j] == array[x][y])
				return 0;




























































































































		}
	}
	return 1;
}

bool rowvalid(int array[9][9], int x, int y) {
	int column=y;
	while (column != 0) {//goes to the end of the row
		column--;
	}
	while (column != 9) {//traverses from start to end of row
		if (column == y) {//skips checking if the indices match
			column++;
			continue;
		}
		else {//checks if a duplicate exists on the index position
			if (array[x][column] == array[x][y]) {
				return 0;
			}
			else {
				column++;
			}
		}
	}
	return 1;
}

void display(int array[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}