/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			printf("%d ", values[i][j]);
		}
		printf("\n");
	}
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	int i;
	// placing ship 5
	for (i = 1; i < 6; i++)
	{
		map[MAP_SIZE - i][MAP_SIZE - 1] = 5;
	}

	// placing ship 4
	for (i = 0; i < 4; i++)
	{
		map[MAP_SIZE - 1][i] = 4;
	}

	// placing ship 3
	for (i = 0; i < 3; i++)
	{
		map[2][1 + i] = 3;
	}

	// placing ship 2
	for (i = 0; i < 2; i++)
	{
		map[i][0] = 2;
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int i, position, number;
	int vertical, horizontal;

	number = rand();
	position = number % 2;

	// check is ship being added is verticle or horiontal
	if (position == 1)
	{
		// get cordinates
		horizontal = (rand() % (MAP_SIZE));
		vertical = (rand() % ((MAP_SIZE - 1) - (size - 1) + 1)) + size - 1;

		// place the ship

		for (i = vertical; i > (vertical - size); i--)
		{
			map[i][horizontal] = size;
		}
	}
	else
	{
		// get cordinates
		vertical = (rand() % (MAP_SIZE));
		horizontal = (rand() % ((MAP_SIZE - 1) - (size - 1) + 1)) + size - 1;

		// place the ship

		for (i = horizontal; i > (horizontal - size); i--)
		{
			map[vertical][i] = size;
		}
	}

	// if position is 1 add ship vertically
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int counter = 0;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == value)
			{
				counter++;
			}
		}
	}
	return counter;
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int direction = 0;
	*row = 0;
	*col = 0;

	// locate the ship.
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == size)
			{
				*row = i;
				*col = j;

				i = MAP_SIZE;
				j = MAP_SIZE;
			}
		}
	}

	// determine the orientation
	if (((*row + 1) < MAP_SIZE) || ((*row - 1) >= 0))
	{
		if (map[*row + 1][*col] == size)
		{
			direction = 2;
		}

		if (map[*row - 1][*col] == size)
		{
			direction = 2;
		}
	}

	if (((*row + 1) < MAP_SIZE) || ((*row - 1) >= 0))
	{
		if (map[*row][*col + 1] == size)
		{
			direction = 1;
		}

		if (map[*row][*col - 1] == size)
		{
			direction = 1;
		}
	}

	return direction;
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int shipRow, shipCol;
	int direction = 0;
	int i, j, k;
	int check;

	check = CountValues(size, map);
	if (check != size)
	{
		return 0;
	}

	direction = TopLeftPosition(size, &shipRow, &shipCol, map);

	if (direction == 0)
	{
		return 0;
	}

	// if direction is vertical
	if (direction == 2)
	{

		for (i = shipRow; i < shipRow + size; i++)
		{
			if ((i < MAP_SIZE) && (i >= 0))
				if (map[i][shipCol] != size)
				{
					return 0;
				}
		}

		for (i = shipRow; i < shipRow + size; i++)
		{

			// checks left and right
			for (j = (shipCol - 1); j < (shipCol + 2); j++)
			{
				if ((i < MAP_SIZE) && (i >= 0) && (j >= 0) && (j < MAP_SIZE))
				{

					if ((map[i][j] != 0) && (map[i][j] != size))
					{
						return 0;
					}
				}
			}
			for (k = (i - 1); k < (i + 2); k++)
			{
				if ((i < MAP_SIZE) && (i >= 0) && (k >= 0) && (k < MAP_SIZE))
				{
					if ((map[k][shipCol] != 0) && (map[k][shipCol] != size))
					{
						return 0;
					}
				}
			}
		}
	}

	if (direction == 1)
	{
		for (i = shipCol; i < shipCol + size; i++)
		{
			if ((i < MAP_SIZE) && (i >= 0))
				if (map[shipRow][i] != size)
				{
					return 0;
				}
		}

		for (i = shipCol; i < (shipCol + size); i++)
		{

			for (j = (shipRow - 1); j < (shipRow + 2); j++)
			{
				if ((i < MAP_SIZE) && (i >= 0) && (j >= 0) && (j < MAP_SIZE))
				{

					if ((map[j][i] != 0) && (map[j][i] != size))
					{
						return 0;
					}
				}
			}

			for (k = (i - 1); k < (i + 2); k++)
			{

				if ((k >= 0) && (k < MAP_SIZE))
				{

					if ((map[shipRow][k] != 0) && (map[shipRow][k] != size))
					{

						return 0;
					}
				}
			}
		}
	}

	return 1;
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	int counter = 0;
	int i, j, k;
	int valid = 0;
	int check;

	// put all values to zero
	for (j = 0; j < MAP_SIZE; j++)
	{
		for (k = 0; k < MAP_SIZE; k++)
		{

			map[j][k] = 0;
		}
	}

	// place a ship
	for (i = 2; i < 6; i++)
	{
		valid = 0;
		while (valid == 0)
		{
			AddRandomShip(i, map);
			valid = IsShipValid(i, map);

			if (valid == 0)
			{
				for (j = 0; j < MAP_SIZE; j++)
				{
					for (k = 0; k < MAP_SIZE; k++)
					{
						if (map[j][k] == i)
						{
							map[j][k] = 0;
						}
					}
				}
			}
		}
	}

	for (i = 2; i < 6; i++)
	{
		if (IsShipValid(i, map))
		{
			counter++;
		}
	}

	if (counter == 4)
	{
		return;
	}
	else
	{
		InitialiseRandomMap(map);
	}
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int counter = 0;
	int i, j, k;
	int shiprow = 0, shipcol = 0;
	int direction;
	int destroycounter = 0;

	if (shots[row][col] != 0)
	{
		return;
	}

	// tells us how many shots have been made
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (shots[i][j] != 0)
			{
				counter++;
			}
		}
	}

	if (map[row][col] == 0)
	{
		shots[row][col] = counter + 1;
	}
	else if (map[row][col] != 0)
	{
		shots[row][col] = 1000 + counter + 1;
	}

	// check if ship is destroyed
	for (i = 2; i < 6; i++)
	{
		destroycounter = 0;
		// get cordinates of the ships present
		direction = TopLeftPosition(i, &shiprow, &shipcol, map);

		if (direction == 1)
		{
			for (j = shipcol; j < shipcol + i; j++)
			{
				if (shots[shiprow][j] != 0)
				{
					destroycounter++;
				}

				if (destroycounter == i)
				{
					for (k = shipcol; k < shipcol + i; k++)
					{
						if (shots[shiprow][k] < 2000)
						{
							shots[shiprow][k] = shots[shiprow][k] - 1000 + (i * 1000);
						}
					}
				}
			}
		}
		else if (direction == 2)
		{
			for (j = shiprow; j < shiprow + i; j++)
			{
				if (shots[j][shipcol] != 0)
				{
					destroycounter++;
				}

				if (destroycounter == i)
				{
					for (k = shiprow; k < shiprow + i; k++)
					{
						if (shots[k][shipcol] < 2000)
						{
							shots[k][shipcol] = shots[k][shipcol] - 1000 + (i * 1000);
						}
					}
				}
			}
		}
	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] != 0)
			{
				if (shots[i][j] == 0)
				{
					return 0;
				}
			}
		}
	}

	return 1;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













