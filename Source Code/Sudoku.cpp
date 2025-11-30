#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>

inline void initialize(int array1[9][9], int array2[9][9]);
bool generatesolution(int array[9][9], int row = 0,int column=0);
bool columnvalid(int array[9][9], int x, int y);
bool gridvalid(int array[9][9], int x, int y);
bool rowvalid(int array[9][9], int x, int y);
void display(int array[9][9]);
void generateboard(int board[9][9], int  solution[9][9] , int forbiddenrows[] , int forbiddencolumns[], int choice);
bool solved(int board[9][9],int solution[9][9]);
void displayboardvalidity(int board[9][9], int solution[9][9]);
void greetings(int board[9][9], int solution[9][9], int &choice);
void play(int board[9][9], int solution[9][9], int forbiddenrows[], int forbiddencolumns[]);

void main() {
	srand(time(0));
	int choice;
	int board[9][9], solution[9][9], forbiddenrows[81] = { 0 }, forbiddencolumns[81] = {0};

	initialize(board, solution);

	greetings(board, solution,choice );

	generatesolution(solution);
	generateboard(board, solution , forbiddenrows,forbiddencolumns, choice);

	play(board, solution, forbiddenrows, forbiddencolumns);


}

inline void initialize(int array1[9][9], int array2[9][9]) {//initializes the arrays with 0s
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			array1[i][j] = 0;
			array2[i][j] = 0;
		}
	}
}

bool generatesolution(int array[9][9], int row , int column ) {
	if (row == 9) return true;

	int nextrow = (column == 8 ? row + 1 : row);
	int nextcolumn = (column == 8 ? 0 : column + 1);

	int digits[9] = { 1,2,3,4,5,6,7,8,9 };
	for (int i = 0; i < 9; i++) {
		int j = rand() % (i + 1);
		std::swap(digits[i], digits[j]);
	}

	for (int k = 0; k < 9; k++) {
		array[row][column] = digits[k];

		if (rowvalid(array, row, column) && columnvalid(array, row, column) && gridvalid(array, row, column)) {
			if (generatesolution(array, nextrow, nextcolumn))
				return true;
		}
	}

	array[row][column] = 0;
	return false;
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
			if (j % 3 == 2 && j != 8) {//displays the golden coloured vertical lines at appropriate places
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
		if (i % 3 == 2 && i != 8) {//displays golden lines for appropriate rows for visibility
			std::cout << "\n  \033[38;5;179m+---+---+---+---+---+---+---+---+---+" << std::endl;
		}
		else {
			std::cout << "\n  +---+---+---\033[38;5;179m+\033[96m---+---+---\033[38;5;179m+\033[96m---+---+---+" << std::endl;
		}
	}
	std::cout << "\033[0m" << "\n" << std::endl;
}
void generateboard( int board[9][9], int solution[9][9], int forbiddenrows[] , int forbiddencolumns[] , int choice) {
	int pos , pusher=0, difficulty;
	switch (choice) {
	case 1:
		difficulty = 5;
		break;
	case 2 :
		difficulty = 3;
		break;
	case 3:
		difficulty = 2;
		break;
	default:
		break;
	}
	for (int i = 0; i < 9; i++) {//traverses rows
		for (int j = 0; j < difficulty; j++) {//randomly assigns numbers in a board for display for each row depending on the difficulty
			pos = rand() % 9;
			board[i][pos] = solution[i][pos];
			forbiddenrows[pusher] = i+1;
			forbiddencolumns[pusher++] = pos+1;
		}
	}
}

bool solved(int board[9][9], int solution[9][9]) {//checks if board == solution
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != solution[i][j])return 0;
		}
	}
	return 1;
}

void displayboardvalidity(int board[9][9], int solution[9][9]) {//same as the display function but prints the non-matching values of solution and board in red
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
				else if (board[i][j] != solution[i][j]) {//changed lines as compared to display
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
				else if (board[i][j] != solution[i][j]) {//changed lines as compared to display 
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

void greetings(int board[9][9], int solution[9][9], int &choice) {//initial greetings and difficulty selection
	do {
		std::cout << "\033[38;5;213mWelcome to Sudoku! \n\n" << std::endl;
		std::cout << "\033[96mPlaying Instructions :" << std::endl;
		std::cout << "1. You can fill all the empty cells with a value that is in accordance with Sudoku rules. " << std::endl;
		std::cout << "2. You cannot modify any value of the pre-filled grid." << std::endl;
		std::cout << "3. You can modify your filled in values." << std::endl;
		std::cout << "4. A unique solution exists for every generated sudoku game.You can check if your moves match the current solution. " << std::endl;
		std::cout << "5. A hint will fill a random empty cell on the board." << std::endl;
		std::cout << "6. You can request the full solution anytime and your game will be terminated." << std::endl;
		std::cout << "\033[38;5;179m\nScoring Logic: " << std::endl;
		std::cout << "Valid Move = +10\n";
		std::cout << "Invalid Move = -5\n";
		std::cout << "Replacing a previously filled cell with valid move = -5\n";
		std::cout << "Replacing a previously filled cell with invalid move = -10\n";
		std::cout << "Hint = -5\n";
		std::cout << "View you board values as compared to the solution = -20\n";
		std::cout << "Solve the board = -50\n";
		std::cout << "\nChoose your difficulty:\n";
		std::cout << "\033[92m1. Easy\n";
		std::cout << "\033[93m2. Medium\n";
		std::cout << "\033[91m3. Hard\n";
		std::cout << "\033[38;5;179mYour Choice(1-3): ";
		std::cin >> choice;
		system("cls");
	} while (choice!=1 && choice!=2 && choice !=3);

}
//playing function
void play(int board[9][9], int solution[9][9], int forbiddenrows[], int forbiddencolumns[]) {
	int row, column, digit, choice, score = 0;
	bool unmodifiable = false;

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
		if (choice == 1) {//adding a number in the grid
			unmodifiable = 0;
			std::cout << "Row: ";
			std::cin >> row;
			if (row < 1 || row>9) {//validates row
				std::cout << "Invalid Value Entered.Press any key to try Again!" << std::endl;
				_getch();
				system("cls");
				continue;
			}
			std::cout << "Column: ";
			std::cin >> column;
			if (column < 1 || column>9) {//validates column
				std::cout << "Invalid Value Entered.Press any key to try again!" << std::endl;
				_getch();
				system("cls");
				continue;
			}
			for (int i = 0; i < 81; i++) {//checks if a pre generated forbidden block was entered by user for changing
				if (forbiddenrows[i] == row && forbiddencolumns[i] == column) {
					std::cout << "You cannot modify any value of the pre-generated board. Only empty or your own filled values." << std::endl;
					std::cout << "Press any key to try again!";
					_getch();
					system("cls");
					unmodifiable = 1;
					break;
				}
				if (forbiddencolumns[i] == 0)break;
			}
			if (unmodifiable)continue;
			std::cout << "Digit:";
			std::cin >> digit;
			if (digit < 1 || digit>9) {//validates input of digit
				std::cout << "Invalid Values Entered.Press any key to try again!" << std::endl;
				_getch();
				system("cls");
				continue;
			}
			if (board[row - 1][column - 1] != 0) {//score deduction if a non zero block was modified.
				board[row - 1][column - 1] = digit;
				score -= 5;
			}
			else {//score addition if a non zero block was modified
				board[row - 1][column - 1] = digit;
				score += 10;
			}
			//invalid input handling
			if (!rowvalid(board, row - 1, column - 1) || !columnvalid(board, row - 1, column - 1) || !gridvalid(board, row - 1, column - 1)) {
				std::cout << "Invalid. Press any key to try again!" << std::endl;
				_getch();
				if (board[row - 1][column - 1] != 0) {// more score deducted if block is non zero and input is invalid
					score -= 5;
				}
				else {//in case of invalid entry in non zero block, the previously added 10 is deducted and -5 is the net score deducted
					score -= 15;
				}
				board[row - 1][column - 1] = 0;
			}
			system("cls");
		}
		else if (choice == 2) {//hint logic
			do {//runs randomly until it finds an empty block
				row = rand() % 9;
				column = rand() % 9;
			} while (board[row][column] != 0);
			board[row][column] = solution[row][column];
			std::cout << "\nA digit  will be placed in 3 seconds at:\nRow: " << row + 1 << "\nColumn: " << column + 1 << std::endl;
			std::cout << "Press any key to continue!";
			_getch();
			system("cls");
			score -= 5;
		}
		else if (choice == 3) {//displays how many entries are wrong wrt to the solution
			displayboardvalidity(board, solution);
			system("cls");
			score -= 15;
		}
		else if (choice == 4) {//makes board=solution and loop is exited
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					board[i][j] = solution[i][j];
				}
			}
			score -= 50;
		}
		else {//handling invalid choice
			std::cout << "Invalid Choice. Press any key to try Again!" << std::endl;
			_getch();
			system("cls");
		}
	}
	system("cls");
	display(board);

	std::cout << "\033[84mCongratulations! Sudoku Solved.";
}