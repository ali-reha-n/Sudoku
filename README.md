# Sudoku (C++ Console Game)

A fully interactive Sudoku game implemented in C++ using backtracking, coloured console graphics, scoring, hints, validation, and difficulty levels.

This project generates a random Sudoku solution, creates a playable board based on difficulty, and allows the user to play using a clean terminal interface.

# Features
## Random Sudoku Generator

1. Uses a recursive backtracking algorithm.

2. Ensures every puzzle has one unique solution.

## Three Difficulty Levels

1. Easy – 5 clues per row

2. Medium – 3 clues per row

3. Hard – 2 clues per row

## Coloured Terminal UI

1. Gold and Cyan grid lines

2. Pink numbers

3. Gray background for empty cells

4. Red markings for incorrect entries

## Gameplay Functions

1. Add numbers to the board

2. Get hints

3. View incorrect entries compared to solution

4. Automatically solve the board

## Live score updates

# Scoring System
- Valid move	                            +10
- Invalid move	                            -5
- Replace your previous valid move	        -5
- Replace with invalid move	                -10
- Hint	                                    -5
- View wrong entries	                    -20
- Solve puzzle	                            -50

# Code Logic and Flow:

- Start
- Initialization of board and solution with 0s
- Display greetings, playing instructions and take the difficulty from user
- Generate a solution
- Generate a board according to the difficulty level
- Start the playing function and go on until game is solved
-    |
-    |--> Enter a number in grid
-    |--> Ask for a hint
-    |--> View the current board validity with respect to the solution
-    |--> Solve the board.
- End

# Playing Instructions:
Just start up the game it has sufficent instructions to make you learn along the way.

# AI Tool Reflections:
AI was used for syntax and colour codes most of the times. Rarely it was used for base logic understanding for flowcharts. Other than that all of the code is human generated. 

# Future Improvemnets:
- Add a UI
- Use vectors for the sake of simplicity
- Add the user to enter any valid grid size
- Implement timer based scoring 
- Account for memory efficiency and make it more memory efficient
- Handling scoring more efficiently and set benchmarks for scoring


*Real joy comes from discovering stuff, not if you know everything beforehand.*