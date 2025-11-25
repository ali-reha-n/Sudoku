#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

inline void initialize(int array1[9][9], int array2[9][9]);
void generatesolution(int array[9][9]);
bool columnvalid(int array[9][9], int x, int y);
bool gridvalid(int array[9][9], int x, int y);
bool rowvalid(int array[9][9], int x, int y);
void display(int array[9][9]);
void generateboard(int board[9][9], int  solution[9][9]);
bool solved(int board[9][9],int solution[9][9]);
bool inputvalid(int board[9][9], int solution[9][9], int x, int y);

void main() {
	srand(time(0));
	int row, column , digit;
	int board[9][9], solution[9][9];
	initialize(board, solution);

	generatesolution(solution);
	generateboard(board, solution);
	display(board);

	do {
		std::cout << "\033[38;5;179mRow: ";
		std::cin >> row;
		if (row < 1 || row>9) {
			std::cout << "Invalid Values Entered.Press any key to try again!" << std::endl;
			_getch();
			system("cls");
			display(board);
			continue;
		}
		std::cout << "Column: ";
		std::cin >> column;
		if ( column < 1 || column>9 ) {
			std::cout << "Invalid Values Entered.Press any key to try again!" << std::endl;
			_getch();
			system("cls");
			display(board);
			continue;
		}
		std::cout << "Digit:";
		std::cin >> digit;
		if ( digit < 1 || digit>9) {
			std::cout << "Invalid Values Entered.Press any key to try again!" << std::endl;
			_getch();
			system("cls");
			display(board);
			continue;
		}
		board[row - 1][column - 1] = digit;
		if (!inputvalid(board, solution , row-1 , column-1)) {
			std::cout << "Invalid. Press any key to try again." << std::endl;
			board[row - 1][column - 1] = 0;
			_getch();
		}
		system("cls");
		display(board);
	} while (!solved(board, solution));

	std::cout << "Congratulations! Sudoku Solved.";


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
	int counter=0 , backtrackedindex , valid[9] , push=0;
	int i = 0,j = 0;
	bool out = false;
	while(i<9){
		while(j<9) {
			counter = 0;
			do {
				array[i][j] = rand() % 9 + 1;
				counter++;
				if (counter > 300) {
					array[i][j] = 0;
					while (i != 0 || j != 0) {
						push = 0;
						for (int k = 0; k < 9; k++) {
							valid[k] = 0;
						}
						if (j == 0) {
							j = 8;
							i--;
						}
						else {
							j--;
						}
						for (int k = 1; k <= 9; k++) {
							array[i][j] = k;
							if (columnvalid(array, i, j) && rowvalid(array, i, j) && gridvalid(array, i, j)) {
								valid[push++] = k;
							}
						}
						int k = 0;
						while (valid[k] != 0) {
							array[i][j] = valid[k];
							if (j == 8) {
								j = 0;
								i++;
							}
							else {
								j++;
							}
							if (columnvalid(array, i, j) && rowvalid(array, i, j) && gridvalid(array, i, j)) {
								if (j == 8) {
									j = 0;
									i++;
								}
								else {
									j++;
								}
								out = 1;
								break;
							}
							if (j == 0) {
								j = 8;
								i--;
							}
							else {
								j--;
							}
							k++;
						}
						if (out) {
							out = 0;
							break;
						}
						array[i][j] = 0;
						if (j == 0) {
							j = 8;
							i--;
						}
						else {
							j--;
						}
					}
					continue;
				}
			} while (!columnvalid(array, i, j) || !rowvalid(array, i, j) || !gridvalid(array,i,j));
			j++;
		}
		j = 0;
		i++;
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
	std::cout << "\033[38;5;179m" << "    1   2   3   4   5   6   7   8   9  " << std::endl;
	std::cout << "\033[96m" << "  +---+---+---+---+---+---+---+---+---+" << std::endl;
	for (int i = 0; i < 9; i++) {
		std::cout << "\033[38;5;179m" << i + 1<< "\033[96m" << " |";
		for (int j = 0; j < 9; j++) {
			if (array[i][j] == 0) {
				std::cout << " \033[48;5;240m \033[0m\033[96m |";
			}
			else {
				std::cout << " " << "\033[38;5;213m" << array[i][j] << "\033[96m" << " " << "|";
			}
		}
		std::cout << "\n  +---+---+---+---+---+---+---+---+---+" << std::endl;
	}
	std::cout << "\033[0m" << "\n\n\n" << std::endl;
}
void generateboard( int board[9][9], int solution[9][9]) {
	int pos;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			pos = rand() % 9;
			board[i][pos] = solution[i][pos];
		}
	}
}

bool solved(int board[9][9], int solution[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != solution[i][j])return 0;
		}
	}
	return 1;
}

bool inputvalid(int board[9][9], int solution[9][9], int x, int y) {
	if (board[x][y] == solution[x][y])return true;
	else return false;
}