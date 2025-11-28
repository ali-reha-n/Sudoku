#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <Windows.h>

inline void initialize(int array1[9][9], int array2[9][9]);
void generatesolution(int array[9][9]);
bool columnvalid(int array[9][9], int x, int y);
bool gridvalid(int array[9][9], int x, int y);
bool rowvalid(int array[9][9], int x, int y);
void display(int array[9][9]);
void generateboard(int board[9][9], int  solution[9][9] , int forbiddenrows[] , int forbiddencolumns[]);
bool solved(int board[9][9],int solution[9][9]);
void displayboardvalidity(int board[9][9], int solution[9][9]);

void main() {
	srand(time(0));
	int row, column , digit,choice,score=0;
	int board[9][9], solution[9][9], forbiddenrows[81] = { 0 }, forbiddencolumns[81] = {0};
	bool unmodifiable = false;
	initialize(board, solution);

	generatesolution(solution);
	generateboard(board, solution , forbiddenrows,forbiddencolumns);

	while (!solved(board, solution)) {
		display(board);
		std::cout << "\033[38;5;179mScore: " << score << std::endl;
		std::cout << "Enter your choice: " << std::endl;
		std::cout << "1. Add a number." << std::endl;
		std::cout << "2. Hint." << std::endl;
		std::cout << "3. View wrong entries with respect to the solution." << std::endl;
		std::cout << "4. Solve the board. " << std::endl;
		std::cout << "\nChoice: ";
		std::cin >> choice;
		if (choice == 1) {
			unmodifiable = 0;
			std::cout << "Row: ";
			std::cin >> row;
			if (row < 1 || row>9) {
				std::cout << "Invalid Values Entered.Try Again!" << std::endl;
				Sleep(2000);
				system("cls");
				continue;
			}
			std::cout << "Column: ";
			std::cin >> column;
			if (column < 1 || column>9) {
				std::cout << "Invalid Values Entered.Try again!" << std::endl;
				Sleep(2000);
				system("cls");
				continue;
			}
			for (int i = 0; i < 81; i++) {
				if (forbiddenrows[i] == row && forbiddencolumns[i] == column) {
					std::cout << "You cannot modify any value of the pre-generated board. Only empty or your own filled values." << std::endl;
					Sleep(3000);
					system("cls");
					unmodifiable = 1;
					break;
				}
				if (forbiddencolumns[i] == 0)break;
			}
			if (unmodifiable)continue;
			std::cout << "Digit:";
			std::cin >> digit;
			if (digit < 1 || digit>9) {
				std::cout << "Invalid Values Entered.Try again!" << std::endl;
				Sleep(2000);
				system("cls");
				continue;
			}
			if (board[row - 1][column - 1] != 0) {
				board[row - 1][column - 1] = digit;
				score -= 5;
			}
			else {
				board[row - 1][column - 1] = digit;
				score += 10;
			}
			
			if (!rowvalid(board, row - 1, column - 1) || !columnvalid(board, row - 1, column - 1) || !gridvalid(board, row - 1, column - 1)) {
				std::cout << "Invalid. Try again!" << std::endl;
				Sleep(2000);
				score -= 15;
				board[row - 1][column - 1] = 0;
			}
			system("cls");
		}
		else if (choice == 2) {
			do {
				row = rand() % 9;
				column = rand() % 9;
			} while (board[row][column] != 0);
			board[row][column] = solution[row][column];
			std::cout << "\nA digit  will be placed in 3 seconds at:\nRow: " << row+1 << "\nColumn: " << column+1 << std::endl;
			Sleep(3000);
			system("cls");
			score -= 5;
		}
		else if (choice == 3) {
			displayboardvalidity(board, solution);
			system("cls");
			score -= 15;
		}
		else if (choice == 4) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					board[i][j] = solution[i][j];
				}
			}
			score -= 50;
		}
		else {
			std::cout << "Invalid Choice. Try Again!" << std::endl;
			Sleep(2000);
			system("cls");
		}
	}
	system("cls");
	display(board);

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
	std::cout << "\033[96m" << "  +---+---+---\033[38;5;179m+\033[96m---+---+---\033[38;5;179m+\033[96m---+---+---+" << std::endl;
	for (int i = 0; i < 9; i++) {
		std::cout << "\033[38;5;179m" << i + 1<< "\033[96m" << " |";
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 2 && j != 8) {
				if (array[i][j] == 0) {
					std::cout << " \033[48;5;240m \033[0m\033[96m \033[38;5;179m|\033[96m";
				}
				else {
					std::cout << " " << "\033[38;5;213m" << array[i][j] << "\033[96m" << " " << "\033[38;5;179m|\033[96m";
				}
			}
			else {
				if (array[i][j] == 0) {
					std::cout << " \033[48;5;240m \033[0m\033[96m |";
				}
				else {
					std::cout << " " << "\033[38;5;213m" << array[i][j] << "\033[96m" << " " << "|";
				}
			}
		}
		if (i % 3 == 2 && i != 8) {
			std::cout << "\n  \033[38;5;179m+---+---+---+---+---+---+---+---+---+" << std::endl;
		}
		else {
			std::cout << "\n  +---+---+---\033[38;5;179m+\033[96m---+---+---\033[38;5;179m+\033[96m---+---+---+" << std::endl;
		}
	}
	std::cout << "\033[0m" << "\n" << std::endl;
}
void generateboard( int board[9][9], int solution[9][9], int forbiddenrows[] , int forbiddencolumns[]) {
	int pos , pusher=0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			pos = rand() % 9;
			board[i][pos] = solution[i][pos];
			forbiddenrows[pusher] = i+1;
			forbiddencolumns[pusher++] = pos+1;
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

void displayboardvalidity(int board[9][9], int solution[9][9]) {
	system("cls");
	std::cout << "\033[38;5;179m" << "    1   2   3   4   5   6   7   8   9  " << std::endl;
	std::cout << "\033[96m" << "  +---+---+---\033[38;5;179m+\033[96m---+---+---\033[38;5;179m+\033[96m---+---+---+" << std::endl;
	for (int i = 0; i < 9; i++) {
		std::cout << "\033[38;5;179m" << i + 1 << "\033[96m" << " |";
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 2 && j != 8) {
				if (board[i][j] == 0) {
					std::cout << " \033[48;5;240m \033[0m\033[96m \033[38;5;179m|\033[96m";
				}
				else if (board[i][j] != solution[i][j]) {
					std::cout << " " << "\033[91m" << board[i][j] << "\033[96m" << " " << "\033[38;5;179m|\033[96m";
				}
				else {
					std::cout << " " << "\033[38;5;213m" << board[i][j] << "\033[96m" << " " << "\033[38;5;179m|\033[96m";
				}
			}
			else {
				if (board[i][j] == 0) {
					std::cout << " \033[48;5;240m \033[0m\033[96m |";
				}
				else if (board[i][j] != solution[i][j]) {
					std::cout << " " << "\033[91m" << board[i][j] << "\033[96m" << " " << "|";
				}
				else {
					std::cout << " " << "\033[38;5;213m" << board[i][j] << "\033[96m" << " " << "|";
				}
			}
		}
		if (i % 3 == 2&&i!=8 ) {
			std::cout << "\n  \033[38;5;179m+---+---+---+---+---+---+---+---+---+" << std::endl;
		}
		else {
			std::cout << "\n  +---+---+---\033[38;5;179m+\033[96m---+---+---\033[38;5;179m+\033[96m---+---+---+" << std::endl;
		}
	}
	std::cout << "Press any key to exit this valid board.";
	std::cout << "\033[0m" << "\n\n\n" << std::endl;
	_getch();
}