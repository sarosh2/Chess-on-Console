/*
The group member names are as follows:
	Name			|	CMS ID
	Sarosh			|	305963
	Talha Waheed	|	282575
	Mutahar Amir	|	289909
	Talha Munir		|	303660
*/

/*The code allocates integer values to pieces in the following pattern (empty spaces are 0, which are printed as the default case)

			Black | White
	Pawn	  1	  |	  7
	Rook	  2	  |	  8
	Knight	  3	  |	  9
	Bishop	  4	  |	  10
	Queen	  5	  |	  11
	King	  6	  |	  12
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void draw_board();//draws the chess board from the perspective of the player whose turn it is
void draw_border_up();//draws the top border with columns named alphabetically and a horizontal line below it to give the board shape
void draw_border_down();;//draws the bottom border with columns named alphabetically and a horizontal line above it to give the board shape
void draw_row(int);//draws each row for the chess board
void draw_column(int, int, int);//draws each column; for the chess board
void draw(int, int, int);//determines where to draw pieces and calls appropriate functions to draws those pieces

void draw_blank(int, int, int);//draws a blank white or black square

void draw_pawn_black(int, int, int);//draws a pawn in the given square
void draw_pawn_white(int, int, int);

void draw_rook_black(int, int, int);//draws a rook in the given square
void draw_rook_white(int, int, int);

void draw_bishop_black(int, int, int);//draws a bishop in the given square
void draw_bishop_white(int, int, int);

void draw_queen_black(int, int, int);//draws a queen in the given square
void draw_queen_white(int, int, int);

void draw_king_black(int, int, int);//draws a king in the given square
void draw_king_white(int, int, int);

void draw_knight_black(int, int, int);//draws a king in the given square
void draw_knight_white(int, int, int);

int offer_draw(char*);//offers draw by the player who's turn it is
void print_errors(int, int, int, int, int*);//prints error messages based on the is_illegal function
void update_position(int, int, int, int);// updates the position according to user input in the positions array
void special_cases(int, int, int, int);
int is_illegal(int, int, int, int);//checks whether given move is legal or not
int is_colliding(int, int, int, int);//gives the number of the piece facing another piece in a given path
int is_under_threat(int, int, int);//tells if the given piece or square is under threat by the enemy
int is_draw();//tells if a draw has occured
int is_checkmate(int, int, int, int);
void pawn_promotion(int, int, int, int);//promotes pawns when they reach the end of the board
int sign(int);//tells if the number given is positive or negative
void multiply_by_i(int complex[]);//multiplies complex nummbers by imaginary number i

void chess_engine(int level, int* move_final);
void best_move(int color, int* move);
int worth(int move_to_row, int move_to_column);
void smallest(int* move_final);
void biggest(int* move_final);

//Default
int positions[8][8] = { {2,3,4,5,6,4,3,2},//black pieces are numbered 1 to 6
						{1,1,1,1,1,1,1,1},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{0,0,0,0,0,0,0,0},
						{7,7,7,7,7,7,7,7},//white pieces are numbered 7 to 12
						{8,9,10,11,12,10,9,8} };//the positions array makes a pseudo chess board with 8 rows and 8 columns
//position array stores the piece at every column.

//storing information regarding special moves and conditions
int special_moves[9][2] = { {0,0},  //0. Storing if the queen side rooks have moved. (left white, right black. Used for castling)
							{0,0},  //1. Storing if the king side rooks have moved. (left white, right black. Used for castling)
							{0,0},  //2. Storing if the kings have moved. (left white, right black. Used for castling)
							{0,4},  //3. Storing the current position of the black king. (Used to determine checkmate, check and stalemate)
							{7,4},  //4. Storing the current position of the white king. (Used to determine checkmate, check and stalemate)
							{8,8},  //5. Storing the current piece threatening a block. (determined through the is_under threat and is_colliding function. Used to determine checkmate and stalemate)
							{8,8},  //6. Storing the columns of pawns that can be captured through en_passant. (left black, right white)
							{7,0},  //7. Storing the position of the square that's being highlighted
							{8,8} };//8. Storing the position of the square that's been selected previously

int turn = 0;//stores the current turn we're on
char empty_char = '\0';//empty character to store enter character in whenever input is taken from user

int checked_moves[100][5];
int counter = 0;

int main()
{ 
	char will_play = '\0'; //stores whether user wishes to play chess or not
	//size of these arrays is 4 to allow fgets to store \n the array which is then replaced with \0
	printf("Welcome to chess!\n");
	printf("You can use both uppercase and lowercase letters\n");
	do
	{
		//asks user if they want to play game or not, keeps asking until the user responds properly
		printf("Do you wish to play chess?(Y or N) ");
		scanf_s("%c", &will_play);
		scanf_s("%c", &empty_char);
		will_play = toupper(will_play);
	}
	while (will_play != 'Y' && will_play != 'N');

	while (will_play == 'Y')
	{
		int move = 0;
		int move_from[2] = { 8, 8 };
		int move_to[2] = {8, 8};
		special_moves[8][0] = 8;
		special_moves[8][1] = 8;
		if (turn % 2 == 0)//on white's turn
		{
			do
			{
				system("cls");
				draw_board();
				switch (toupper(_getch()))
				{
				case 'W':
					if (turn % 2)
					{
						special_moves[7][0]++;
						break;
					}
					else
					{
						special_moves[7][0]--;
						break;
					}
				case 'S':
					if (turn % 2)
					{
						special_moves[7][0]--;
						break;
					}
					else
					{
						special_moves[7][0]++;
						break;
					}
				case 'D':
					if (turn % 2)
					{
						special_moves[7][1]--;
						break;
					}
					else
					{
						special_moves[7][1]++;
						break;
					}
				case 'A':
					if (turn % 2)
					{
						special_moves[7][1]++;
						break;
					}
					else
					{
						special_moves[7][1]--;
						break;
					}
				case 'O':
					offer_draw(&will_play);
					break;
				case '\r':
					if (move == 0)
					{
						special_moves[8][0] = move_from[0] = special_moves[7][0];
						special_moves[8][1] = move_from[1] = special_moves[7][1];
						move++;
					}
					else
					{
						special_moves[8][0] = 8;
						special_moves[8][1] = 8;
						move_to[0] = special_moves[7][0];
						move_to[1] = special_moves[7][1];
						move = 0;
					}
				default:
					break;
				}
			}
			while (is_illegal(move_from[0], move_from[1], move_to[0], move_to[1]));
		}
		else//on black's turn
		{
			turn--;
			system("cls");
			draw_board();
			turn++;
			int move_final[4] = { 8,8,8,8 };
			chess_engine(2, move_final);
			counter = 0;
			move_from[0] = move_final[0];
			move_from[1] = move_final[1];
			move_to[0] = move_final[2];
			move_to[1] = move_final[3];
		}

		//asks the user to move

		//update information regarding special cases if necessary
		special_cases(move_from[0], move_from[1], move_to[0], move_to[1]);

		//update the position of the piece selected by user
		update_position(move_from[0], move_from[1], move_to[0], move_to[1]);
		turn++;

	}
	printf("Thank you for playing :) \n");
	return 0;
}

void draw_board()
{
	draw_border_up();

	if (turn % 2 == 0)
	{
		for (int row = 0; row < 8; row++)
		{
			draw_row(row);
		}
	}
	else
	{
		for (int row = 7; row >= 0; row--)
		{
			draw_row(row);
		}
	}
	//8 rows to be printed

	draw_border_down();
}

void draw_border_up()
{
	if (turn % 2 == 0)
	{
		//the columns are named alphabetically
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 8; i++)
			printf("     %c     ", 'A' + i);
		printf("\n");

		//A line is printed to give the board its upper border
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 88; i++)
			printf("%c", 196);
		printf("\n");
	}
	else
	{
		//the columns are named alphabetically
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 7; i >= 0; i--)
			printf("     %c     ", 'A' + i);
		printf("\n");

		//A line is printed to give the board its upper border
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 88; i++)
			printf("%c", 196);
		printf("\n");
	}
}

void draw_border_down()
{
	if (turn % 2 == 0)
	{
		//A line is printed to give the board its upper border
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 88; i++)
			printf("%c", 196);
		printf("\n");

		//the columns are named alphabetically
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 8; i++)
			printf("     %c     ", 'A' + i);
		printf("\n");
	}
	else
	{
		//A line is printed to give the board its upper border
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 0; i < 88; i++)
			printf("%c", 196);
		printf("\n");

		//the columns are named alphabetically
		printf("\t\t\t\t\t\t   ");//to centralize the board
		for (int i = 7; i >= 0; i--)
			printf("     %c     ", 'A' + i);
		printf("\n");
	}
}

void draw_row(int row)
{
	//each row of the chess board is made up of five lines 
	for (int line = 0; line < 5; line++)
	{
		/*there are 8 columns in each row of the chess board,
		loop is iterated 10 times to allow numbering of rows on the left and right edges.
		Column is 0 at left edge, and 9 at right edge */

		if (turn % 2 == 0)//board drawn from white's perspective
		{
			for (int column = 0; column < 10; column++)
			{
				draw_column(row, line, column);
			}
		}
		else
		{
			for (int column = 9; column >= 0; column--)//board drawn from black's perspective
			{
				draw_column(row, line, column);
			}
		}
		printf("\n");//a new line begins after all the columns have been drawn	
	}
}

void draw_column(int row, int line, int column)
{
	if (turn % 2 == 0)
	{
		//the first column is printed to centralize the board on the screen and to number the rows from 1 to 8
		if (column == 0)
		{
			if (line == 2)
				printf("\t\t\t\t\t\t%d %c", 8 - row, 179);/* rows are numbered in descending order, because in traditional chess,
													  player on bottom is white and the numbering starts with white's side as row 1 */
			else
				printf("\t\t\t\t\t\t  %c", 179);
		}
		else if (column == 9)
		{
			if (line == 2)
				printf("%c %d", 179, 8 - row); //number of row is given on every third line of the row
			else
				printf("%c", 179);
		}
		else // pieces printed if needed, otherwise blank squares drawn
		{
			draw(row, line, column);
		}
	}
	else
	{
		//the first column is printed to centralize the board on the screen and to number the rows from 1 to 8
		if (column == 9)
		{
			if (line == 2)
				printf("\t\t\t\t\t\t%d %c", 8 - row, 179);/* rows are numbered in descending order, because in traditional chess,
													  player on bottom is white and the numbering starts with white's side as row 1 */
			else
				printf("\t\t\t\t\t\t  %c", 179);
		}
		else if (column == 0)
		{
			if (line == 2)
				printf("%c %d", 179, 8 - row); //number of row is given on every third line of the row
			else
				printf("%c", 179);
		}
		else // pieces printed if needed, otherwise blank squares drawn
		{
			draw(row, line, column);
		}
	}
	
}

void draw(int row, int line, int column) //draws pieces in their respective places
{
	/*The code allocates integer values to pieces in the following pattern (empty spaces are 0, which are printed as the default case)

			Black | White
	Pawn	  1	  |	  7
	Rook	  2	  |	  8
	Knight	  3	  |	  9
	Bishop	  4	  |	  10
	Queen	  5	  |	  11
	King	  6	  |	  12
	*/
	switch (positions[row][column - 1])
	{
	case 1:
		draw_pawn_black(row, line, column);
		break;
	case 2:
		draw_rook_black(row, line, column);
		break;
	case 3:
		draw_knight_black(row, line, column);
		break;
	case 4:
		draw_bishop_black(row, line, column);
		break;
	case 5:
		draw_queen_black(row, line, column);
		break;
	case 6:
		draw_king_black(row, line, column);
		break;
	case 7:
		draw_pawn_white(row, line, column);
		break;
	case 8:
		draw_rook_white(row, line, column);
		break;
	case 9:
		draw_knight_white(row, line, column);
		break;
	case 10:
		draw_bishop_white(row, line, column);
		break;
	case 11:
		draw_queen_white(row, line, column);
		break;
	case 12:
		draw_king_white(row, line, column);
		break;
	default:
		draw_blank(row, line, column);
		break;
	}
}

void draw_blank(int row, int line, int column) // tells which piece needs to be drawn
{
	if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
	{
		if (turn % 2)
		{
			printf("\033[0;35m");
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);//white section of the current line
			printf("\033[0m");
		}
		else
		{
			printf("\033[0;34m");
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);//white section of the current line
			printf("\033[0m");
		}
	}
	else if (!is_illegal(special_moves[8][0], special_moves[8][1], row, column - 1))
	{
		if ((row + column) % 2 == 0)
		{
			switch (line)
			{
			case 2:
				printf("    ");//black section of the current line
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
				printf("%c%c%c", 219, 219, 219);//black section of the current line
				printf("\033[0m");
				printf("    ");//black section of the current line
				break;
			default:
				printf("           ");//black section of the current line
				break;
			}
		}
		else
		{
			switch (line)
			{
			case 2:
				printf("%c%c%c%c", 219, 219, 219, 219);
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
				printf("%c%c%c", 219, 219, 219);//black section of the current line
				printf("\033[0m");
				printf("%c%c%c%c", 219, 219, 219, 219);
				break;
			default:
				printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);//white section of the current line
				break;
			}
		}
	}
	else if ((row + column) % 2 == 0)
	{
		printf("           ");//black section of the current line
	}
	else
	{
		printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);//white section of the current line
	}
	
}

void draw_pawn_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's shape
		{
		case 0:
			printf("           ");
			break;
		case 1:
			printf("           ");
			break;
		case 2:
			printf("    (_)    ");
			break;
		case 3:
			printf("   /___\\   ");
			break;
		case 4:
			printf("  |_____|  ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 2:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("(_)");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("(_)");
					printf("\033[0m");
				}
			}
			else
			{
				printf("(_)");
			}
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 3:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("/___\\");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("/___\\");
					printf("\033[0m");
				}
			}
			else
			{
				printf("/___\\");
			}
			printf("%c%c%c", 219, 219, 219);
			break;
		case 4:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|_____|");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|_____|");
					printf("\033[0m");
				}
			}
			else
			{
				printf("|_____|");
			}
			printf("%c%c", 219, 219);
			break;
		}
	}
}
void draw_pawn_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's shape
		{
		case 0:
			printf("           ");
			break;
		case 1:
			printf("           ");
			break;
		case 2:
			printf("    (%c)    ", 176);
			break;
		case 3:
			printf("   /%c%c%c\\   ", 178, 176, 177);
			break;
		case 4:
			printf("  |%c%c%c%c%c|  ", 178, 178, 176, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 2:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("(%c)", 176);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("(%c)", 176);
					printf("\033[0m");
				}
			}
			else
			{
				printf("(%c)", 176);
			}
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 3:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("/%c%c%c\\", 178, 176, 177);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("/%c%c%c\\", 178, 176, 177);
					printf("\033[0m");
				}
			}
			else
			{
				printf("/%c%c%c\\", 178, 176, 177);
			}
			printf("%c%c%c", 219, 219, 219);
			break;
		case 4:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|%c%c%c%c%c|", 178, 178, 176, 177, 177);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|%c%c%c%c%c|", 178, 178, 176, 177, 177);
					printf("\033[0m");
				}
			}
			else
			{
				printf("|%c%c%c%c%c|", 178, 178, 176, 177, 177);
			}
			printf("%c%c", 219, 219);
			break;
		}
	}
}

void draw_rook_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("           ");
			break;
		case 1:
			printf("  |_|_|_|  ");
			break;
		case 2:
			printf("   |___|   ");
			break;
		case 3:
			printf("  _|___|_  ");
			break;
		case 4:
			printf(" |_______| ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|_|_|_|");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|_|_|_|");
					printf("\033[0m");
				}
			}
			else
			{
				printf("|_|_|_|");
			}
			printf("%c%c", 219, 219);
			break;
		case 2: case 3:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|___|");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|___|");
					printf("\033[0m");
				}
			}
			else
			{
				printf("|___|");
			}
			printf("%c%c%c", 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|_______|");
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|_______|");
					printf("\033[0m");
				}
			}
			else
			{
				printf("|_______|");
			}
			printf("%c", 219);
			break;
		}
	}
}
void draw_rook_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("           ");
			break;
		case 1:
			printf("  |%c_%c_%c|  ", 178, 176, 177);
			break;
		case 2:
			printf("   |%c%c%c|   ", 178, 176, 177);
			break;
		case 3:
			printf("  _|%c%c%c|_  ", 178, 176, 177);
			break;
		case 4:
			printf(" |%c%c%c%c%c%c%c| ", 178, 178, 178, 176, 177, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|%c_%c_%c|", 178, 176, 177);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|%c_%c_%c|", 178, 176, 177);
					printf("\033[0m");
				}
			}
			else
			{
				printf("|%c_%c_%c|", 178, 176, 177);
			}
			printf("%c%c", 219, 219);
			break;
		case 2: case 3:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|%c%c%c|", 178, 176, 177);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|%c%c%c|", 178, 176, 177);
					printf("\033[0m");
				}
			}
			else
			{
				printf("|%c%c%c|", 178, 176, 177);
			}
			printf("%c%c%c", 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
					printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
					printf("\033[0m");
				}
				else
				{
					printf("\033[0;34m");
					printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
					printf("\033[0m");
				}
			}
			else
			{
				printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
			}
			printf("%c", 219);
			break;
		}
	}
}

void draw_bishop_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("     _     ");
			break;
		case 1:
			printf("    (_)    ");
			break;
		case 2:
			printf("   (___)   ");
			break;
		case 3:
			printf("  __|_|__  ");
			break;
		case 4:
			printf(" |_______| ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("(_)");
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 2:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("(___)");
			printf("\033[0m");
			printf("%c%c%c", 219, 219, 219);
			break;
		case 3:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_|");
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_______|");
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}
void draw_bishop_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("     _     ");
			break;
		case 1:
			printf("    (%c)    ", 176);
			break;
		case 2:
			printf("   (%c%c%c)   ", 178, 176, 177);
			break;
		case 3:
			printf("  __|%c|__  ", 176);
			break;
		case 4:
			printf(" |%c%c%c%c%c%c%c| ", 178, 178, 178, 176, 177, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("(%c)", 176);
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 2:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("(%c%c%c)", 178, 176, 177);
			printf("\033[0m");
			printf("%c%c%c", 219, 219, 219);
			break;
		case 3:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c|", 176);
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}

void draw_king_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("     _     ");
			break;
		case 1:
			printf("  /\\/ \\/\\  ");
			break;
		case 2:
			printf("  \\ - - /  ");
			break;
		case 3:
			printf("  _\\___/_  ");
			break;
		case 4:
			printf(" |_______| ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("/\\/ \\/\\");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 2:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("\\ - - /");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("_\\___/_");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_______|");
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}
void draw_king_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("     _     ");
			break;
		case 1:
			printf("  /\\/%c\\/\\  ", 176);
			break;
		case 2:
			printf("  \\%c-%c-%c/  ", 178, 176, 177);
			break;
		case 3:
			printf("  _\\%c%c%c/_  ", 178, 176, 177);
			break;
		case 4:
			printf(" |%c%c%c%c%c%c%c| ", 178, 178, 178, 176, 177, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("/\\/%c\\/\\", 176);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 2:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("\\%c-%c-%c/", 178, 176, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("_\\%c%c%c/_", 178, 176, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}

void draw_queen_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("   __-__   ");
			break;
		case 1:
			printf("   )___(   ");
			break;
		case 2:
			printf("  |_____|  ");
			break;
		case 3:
			printf("  __|_|__  ");
			break;
		case 4:
			printf(" |_______| ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 223, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf(")___(");
			printf("\033[0m");
			printf("%c%c%c", 219, 219, 219);
			break;
		case 2:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_____|");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_|");
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_______|");
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}
void draw_queen_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf("   __-__   ");
			break;
		case 1:
			printf("   )%c%c%c(   ", 178, 176, 177);
			break;
		case 2:
			printf("  |%c%c%c%c%c|  ", 178, 178, 176, 177, 177);
			break;
		case 3:
			printf("  __|%c|__  ", 176);
			break;
		case 4:
			printf(" |%c%c%c%c%c%c%c| ", 178, 178, 178, 176, 177, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 223, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c%c%c", 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf(")%c%c%c(", 178, 176, 177);
			printf("\033[0m");
			printf("%c%c%c", 219, 219, 219);
			break;
		case 2:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c%c%c%c%c|", 178, 178, 176, 177, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c%c%c", 219, 219, 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c|", 176);
			printf("\033[0m");
			printf("%c%c%c%c", 219, 219, 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}

void draw_knight_black(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf(" _______   ");
			break;
		case 1:
			printf("  / -   \\  ");
			break;
		case 2:
			printf(" /_/|   /  ");
			break;
		case 3:
			printf("  _/___|_  ");
			break;
		case 4:
			printf(" |_______| ");
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf(" / -   \\");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 2:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("/_/|   /");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("_/___|_");
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|_______|");
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}
void draw_knight_white(int row, int line, int column)
{
	if ((row + column) % 2 == 0)
	{
		if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
		{
			if (turn % 2)
			{
				printf("\033[0;35m");
			}
			else
			{
				printf("\033[0;34m");
			}
		}
		switch (line) //each line contains a different section of the piece's sprite
		{
		case 0:
			printf(" _______   ");
			break;
		case 1:
			printf("  /%c-%c%c%c\\  ", 178, 176, 177, 177);
			break;
		case 2:
			printf(" /_/|%c%c%c/  ", 176, 177, 177);
			break;
		case 3:
			printf("  _/%c%c%c|_  ", 178, 176, 177);
			break;
		case 4:
			printf(" |%c%c%c%c%c%c%c| ", 178, 178, 178, 176, 177, 177, 177);
			break;
		}
		printf("\033[0m");
	}
	else //different sprite printed depending on whether the piece is printed on a black or white square
	{
		switch (line)
		{
		case 0:
			printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
			break;
		case 1:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf(" /%c-%c%c%c\\", 178, 176, 177, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 2:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("/_/|%c%c%c/", 176, 177, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 3:
			printf("%c%c", 219, 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("_/%c%c%c|_", 178, 176, 177);
			printf("\033[0m");
			printf("%c%c", 219, 219);
			break;
		case 4:
			printf("%c", 219);
			if ((row == special_moves[7][0] && column - 1 == special_moves[7][1]) || (row == special_moves[8][0] && column - 1 == special_moves[8][1]))
			{
				if (turn % 2)
				{
					printf("\033[0;35m");
				}
				else
				{
					printf("\033[0;34m");
				}
			}
			printf("|%c%c%c%c%c%c%c|", 178, 178, 178, 176, 177, 177, 177);
			printf("\033[0m");
			printf("%c", 219);
			break;
		}
	}
}

int offer_draw(char *will_play)
{
	int choice = 0;
	do
	{
		printf("Player %d is offering a draw, what would player %d like to do?\n", (turn % 2) + 1, ((turn + 1) % 2) + 1);
		printf("1. Accept\n2. Decline\n");
		scanf_s("%d", &choice);
		scanf_s("%c", &empty_char);
	} 
	while (choice > 2 || choice < 1);
	if (choice == 1)
	{
		printf("Draw by agreement\n");
		*will_play = 'N';
		return 1;
	}
	else
	{
		printf("Draw offer declined. Game continues.\n");
		return 0;
	}
}

void print_errors(int move_from_row, int move_from_column, int move_to_row, int move_to_column, int* illegal)
{
	//prints different error messages based on the is_illegal function
	switch (is_illegal(move_from_row, move_from_column, move_to_row, move_to_column))
	{
	case 1:
		printf("You have to make a move inside the board silly!\n");
		break;
	case 2:
		printf("You can't move a black piece, it's white's turn.\n");
		break;
	case 3:
		printf("You can't do that.\n");
		break;
	case 4:
		printf("Your king will be in check, you can't do that.\n");
		break;
	case 5:
		printf("You can't move a white piece, it's black's turn.\n");
		break;
	case 6:
		printf("You can't move the pawn there, there's a piece there.\n");
		break;
	case 7:
		printf("The pawn can't move that much, one block at a time.\n");
		break;
	case 8:
		printf("Pawns can only kill diagonally. Who're you trying to kill? Air?!\n");
		break;
	case 9:
		printf("Pawn rules:\n");
		printf("1. Moves one block forward in a straight line.\n");
		printf("2. Can move two blocks if moving the first time.\n");
		printf("3. Can capture enemy pieces, but only diagonally.(They must also be only one block away)\n");
		printf("4. If an enemy pawn is moved two blocks and lands adjacent to one of your pawns, your pawn can capture it by moving diagonally in that pawn's direction (En Passant)\n");
		printf("5. You can never go back with a pawn\n");
		printf("I don't know what you're doing, but if you're seeing this, it ain't right chief.\n");
		break;
	case 10:
		printf("You can only move straight with rooks.\n");
		break;
	case 11:
		printf("Knights move in an L shape. You can either go two blocks vertically and one horizontally or vice versa.\n");
		break;
	case 12:
		printf("Bishops move diagonally only.\n");
		break;
	case 13:
		printf("You can only move straight or diagonally with a queen, not wherever you want.\n");
		break;
	case 14:
		printf("King can't move into check.\n");
		break;
	case 15:
		printf("You can't castle with a piece you've moved already.\n");
		break;
	case 16:
		printf("You can't castle through blocks that are under threat by the enemy.\n");
		break;
	case 17:
		printf("The king can't move that much, one block at a time.\n");
		break;
	default:
		*illegal = 0;
		break;
	}
}

void update_position(int move_from_row, int move_from_column, int move_to_row, int move_to_column)
{
	//updates positions in the positions array and the positions of the two kings if necessary.
	positions[move_to_row][move_to_column] = positions[move_from_row][move_from_column];
	positions[move_from_row][move_from_column] = 0;

	if (positions[move_to_row][move_to_column] == 6)
	{
		special_moves[3][0] = move_to_row;
		special_moves[3][1] = move_to_column;
	}
	else if (positions[move_to_row][move_to_column] == 12)
	{
		special_moves[4][0] = move_to_row;
		special_moves[4][1] = move_to_column;
	}
}

void special_cases(int move_from_row, int move_from_column, int move_to_row, int move_to_column)
{
	if (turn % 2)
	{
		if (positions[move_from_row][move_from_column] == 1)
		{
			if (move_from_row == 1 && move_to_row == 3)
			{
				special_moves[6][0] = move_to_column;
			}
			else if (move_to_row - move_from_row == abs(move_to_column - move_from_column) && special_moves[6][1] == move_to_column)
			{
				positions[move_from_row][move_to_column] = 0;
			}
		}
		else if (positions[move_from_row][move_from_column] == 6 && abs(move_from_column - move_to_column) == 2)
		{
			positions[0][move_to_column - sign(move_to_column - move_from_column)] = positions[0][7 * (sign(move_to_column - move_from_column) + 1) / 2];
			positions[0][7 * (sign(move_to_column - move_from_column) + 1) / 2] = 0;
		}
	}
	else
	{
		if (positions[move_from_row][move_from_column] == 7)
		{
			if (move_from_row == 6 && move_to_row == 4)
			{
				special_moves[6][1] = move_to_column;
			}
			else if (move_from_row - move_to_row == abs(move_to_column - move_from_column) && special_moves[6][0] == move_to_column)
			{
				positions[move_from_row][move_to_column] = 0;
			}
		}
		else if (positions[move_from_row][move_from_column] == 12 && abs(move_from_column - move_to_column) == 2)
		{
			positions[7][move_to_column - sign(move_to_column - move_from_column)] = positions[7][7 * (sign(move_to_column - move_from_column) + 1) / 2];
			positions[7][7 * (sign(move_to_column - move_from_column) + 1) / 2] = 0;
		}
	}
	//updates information and takes care of special cases such as castling, en_passant and pawn promotion.
	if (special_moves[6][turn % 2])
	{
		special_moves[6][turn % 2] = 8;
	}
	switch (positions[move_from_row][move_from_column])
	{
	case 1: case 7: 
		if (move_to_row == 7 * (turn % 2))
		{
			pawn_promotion(move_from_row, move_from_column, move_to_row, move_to_column);
		}
		break;
	case 6:
		special_moves[2][1] = 1;
		break;
	case 12:
		special_moves[2][0] = 1;
		break;
	case 2: case 8:
		if (move_from_column == 0)
		{
			special_moves[0][turn % 2] = 1;
		}
		else if (move_from_column == 7)
		{
			special_moves[1][turn % 2] = 1;
		}
		break;
	default:
		break;
	}
}

int is_illegal(int move_from_row, int move_from_column, int move_to_row, int move_to_column)
{
	for (int iteration = 0; iteration < counter; iteration++)
	{
		if (checked_moves[iteration][0] == move_from_row && checked_moves[iteration][1] == move_from_column && checked_moves[iteration][2] == move_to_row && checked_moves[iteration][3] == move_to_column)
		{
			return 1;
		}
	}
	if (move_from_row > 7 || move_from_row < 0 || move_from_column > 7 || move_from_column < 0 || move_to_row > 7 || move_to_row < 0 || move_to_column > 7 || move_to_column < 0)
	{
		//checks if the move is occuring outside the board.
		return 1;
	}

	if (turn % 2 == 0)//on white's turn.
	{
		if (positions[move_from_row][move_from_column] > 0 && positions[move_from_row][move_from_column] < 7)//if a black piece is being moved.
		{
			return 2;
		}
		else if (positions[move_to_row][move_to_column] >= 7)//if a white piece is being captured.
		{
			return 3;
		}
		int piece_at_position = positions[move_to_row][move_to_column];// the piece at the location where the user has asked to move.
		update_position(move_from_row, move_from_column, move_to_row, move_to_column);//make the move the user has given to test it out.
		if (special_moves[6][0] == move_to_column && move_from_row == 3)
		{
			positions[move_from_row][move_to_column] = 0;
		}
		if (is_under_threat(special_moves[4][0], special_moves[4][1], 12))//if the move causes the player's king to be in check in any way, give an error.
		{
			update_position(move_to_row, move_to_column, move_from_row, move_from_column);//reset the position.
			positions[move_to_row][move_to_column] = piece_at_position;//restores a piece if it was captured in the test move.
			if (special_moves[6][0] == move_to_column && move_from_row == 3)//undo en_passant if it was done.
			{
				positions[move_from_row][move_to_column] = 1;
			}
			return 4;
		}
		else
		{
			update_position(move_to_row, move_to_column, move_from_row, move_from_column);//reset the position to further check the validity of the move.
			positions[move_to_row][move_to_column] = piece_at_position;//restores a piece if it was captured in the test move.
			if (special_moves[6][0] == move_to_column && move_from_row == 3)//undo en_passant if it was done.
			{
				positions[move_from_row][move_to_column] = 1;
			}
		}
	}
	else//on black's turn
	{
		if (positions[move_from_row][move_from_column] >= 7)//if a white piece is being moved.
		{
			return 5;
		}
		else if (positions[move_to_row][move_to_column] > 0 && positions[move_to_row][move_to_column] < 7)//if a black piece is being captured.
		{
			return 3;
		}
		int piece_at_position = positions[move_to_row][move_to_column];//the piece at the location where the user has asked to move.
		update_position(move_from_row, move_from_column, move_to_row, move_to_column);//make the move to test it.
		if (special_moves[6][1] == move_to_column && move_from_row == 4)//special condition to check for en_passant.
		{
			positions[move_from_row][move_to_column] = 0;
		}
		if (is_under_threat(special_moves[3][0], special_moves[3][1], 6))//if the move causes the player's king to be in check anyhow, return error.
		{
			update_position(move_to_row, move_to_column, move_from_row, move_from_column);//reset the position.
			positions[move_to_row][move_to_column] = piece_at_position;//restores a piece if it was captured in the test move.
			if (special_moves[6][1] == move_to_column && move_from_row == 4)//undo en_passant if it was done.
			{
				positions[move_from_row][move_to_column] = 7;
			}
			return 4;
		}
		else
		{
			update_position(move_to_row, move_to_column, move_from_row, move_from_column);//reset the position to further check the validity of the move.
			positions[move_to_row][move_to_column] = piece_at_position;//restores a piece if it was captured in the test move.
			if (special_moves[6][1] == move_to_column && move_from_row == 4)//undo en_passant if it was done.
			{
				positions[move_from_row][move_to_column] = 7;
			}
		}
	}

	if (is_colliding(move_from_row, move_from_column, move_to_row, move_to_column))//if there's a collision in the path given.
	{
		return 3;
	}

	switch (positions[move_from_row][move_from_column])//check the piece at the position from which the user has requested to move.
	{
	case 1:
		if (move_from_column == move_to_column)//checks if the move occurs within the same column, as pawns usually move.
		{
			if (positions[move_to_row][move_to_column])//if there's a piece where the pawn is to be moved.
			{
				return 6;
			}
			else if (move_from_row == 1 && move_to_row - move_from_row == 2)//checks if the pawn is moving for the first time or not. It can move up to two squares if so.
			{
				return 0;
			}
			else if (move_to_row - move_from_row == 1)//check whether the move is of one block or not.
			{
				return 0;
			}
			else
			{
				return 7;
			}
		}
		else if (abs(move_from_row - move_to_row) == abs(move_to_column - move_from_column) && move_to_row - move_from_row == 1)//checks if move is diagonal and one block.
		{
			if (positions[move_to_row][move_to_column] >= 7)//if there's a white piece is being captured.
			{
				return 0;
			}
			else if (move_to_column == special_moves[6][1] && move_from_row == 4)
			{
				return 0;
			}
			else
			{
				return 8;
			}
		}
		else
		{
			return 9;
		}
	case 2: case 8:
		if (move_from_column == move_to_column || move_from_row == move_to_row)//checks if the move occurs within the same column or row, as rooks usually move.
		{
			return 0;
		}
		else
		{
			return 10;
		}
	case 3: case 9:
		if ((abs(move_to_column - move_from_column) == 2 && abs(move_from_row - move_to_row) == 1) || (abs(move_to_column - move_from_column) == 1 && abs(move_from_row - move_to_row) == 2))
		{
			//checks whether the move occurs in an L shape.
			return 0;
		}
		else
		{
			return 11;
		}
	case 4: case 10:
		if (abs(move_from_row - move_to_row) == abs(move_to_column - move_from_column)) //if the move is diagonal.
		{
			return 0;
		}
		else
		{
			return 12;
		}
	case 5: case 11:
		if (abs(move_from_row - move_to_row) == abs(move_to_column - move_from_column) || move_from_column == move_to_column || move_from_row == move_to_row) //if the move is diagonal or straight.
		{
			return 0;
		}
		else
		{
			return 13;
		}
	case 6: case 12:
		if (abs(move_from_column - move_to_column) <= 1 && abs(move_to_row - move_from_row) <= 1) //if the move is diagonal or straight.
		{
			if (is_under_threat(move_to_row, move_to_column, 6 + (6 * ((turn + 1) % 2))))//king can't move into check.
			{
				return 14;
			}
			else
			{
				return 0;
			}
		}
		else if (abs(move_to_column - move_from_column) == 2 && move_from_row == move_to_row)
		{
			int sign_column = sign(move_to_column - move_from_column);
			if (special_moves[2][turn % 2] == 1 || special_moves[(sign_column + 1) / 2][turn % 2] == 1)
			{
				return 15;
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					if (is_under_threat(move_from_row, move_from_column + i * sign_column, 6 + (6 * ((turn + 1) % 2))))
					{
						return 16;
					}
				}
			}
			return 0;
		}
		else
		{
			return 17;
		}
	case 7:
		if (move_from_column == move_to_column)//checks if the move occurs within the same column, as pawns usually move.
		{
			if (positions[move_to_row][move_to_column])//if there's a piece where the pawn is to be moved.
			{
				return 6;
			}
			else if (move_from_row == 6 && move_from_row - move_to_row == 2)//checks if the pawn is moving for the first time or not. It can move up to two squares if so.
			{
				return 0;
			}
			else if (move_from_row - move_to_row == 1)//check whether the move is of one block or not.
			{
				return 0;
			}
			else
			{
				return 7;
			}
		}
		else if (abs(move_from_row - move_to_row) == abs(move_to_column - move_from_column) && move_from_row - move_to_row == 1)//checks if move is diagonal and one block.
		{
			if (positions[move_to_row][move_to_column] > 0 && positions[move_to_row][move_to_column] < 7)//if there's a black piece where the pawn is to be moved.
			{
				return 0;
			}
			else if (move_to_column == special_moves[6][0] && move_from_row == 3)
			{
				return 0;
			}
			else
			{
				return 8;
			}
		}
		else
		{
			return 9;
		}
	default:
		return 3;
	}
}

int is_colliding(int move_from_row, int move_from_column, int move_to_row, int move_to_column)
{
	int change = 0;//change between either the rows or columns.
	int sign_row = sign(move_to_row - move_from_row);//checks if the change in rows is positive or negative.
	int sign_column = sign(move_to_column - move_from_column);//checks if the change in columns is positive or negative.
	if (move_from_column == move_to_column)//if columns aren't changing, use the change in rows, otherwise, use the change in columns.
	{
		change = abs(move_from_row - move_to_row);
	}
	else
	{
		change = abs(move_to_column - move_from_column);
	}
	if (move_from_column == move_to_column || move_from_row == move_to_row || abs(move_from_column - move_to_column) == abs(move_from_row - move_to_row))//if the move occurs in a straight line or diagonal.
	{
		//loops until either the index goes outside the positions array or the entire path between the move from block and move to block has been checked.
		for (int position = 1; (position < change) && (move_from_row + (position * sign_row) >= 0) && (move_from_row + (position * sign_row) <= 7) && (move_from_column + (position * sign_column) >= 0) && (move_from_column + (position * sign_column) <= 7); position++)
		{
			//if a piece is found between the move to block and the move from block, the location of that piece is saved and it's type is returned as its value in the positions array.
			if (positions[move_from_row + (position * sign_row)][move_from_column + (position * sign_column)])
			{
				special_moves[5][0] = move_from_row + (position * sign_row);
				special_moves[5][1] = move_from_column + (position * sign_column);
				return positions[move_from_row + (position * sign_row)][move_from_column + (position * sign_column)];
			}
		}
	}
	return 0;
}

int is_under_threat(int position_row, int position_column, int piece)//checks if the piece given is under threat by a piece of the opposite colour.
{
	//complex numbers are used as directional vectors, where the first entry relates to columns and second to rows.
	int complex_straight[2] = { 1, 0 };
	int complex_diagonal[2] = { 1, 1 };
	switch (piece)
	{
	case 1: case 2: case 3: case 4: case 5: case 6://if the piece is black.

		for (int turns = 0; turns < 4; turns++)//checks for a white rook or queen in the same columns or rows as the piece.
		{
			//every even turn, columns are checked in the direction of the second entry in the complex vector, and rows are checked every odd turn.
			switch (is_colliding(position_row, position_column, (position_row * ((turns + 1) % 2)) + ((turns % 2) * (3.5 + (4.5 * complex_straight[1]))) , (position_column * (turns % 2)) + (((turns + 1) % 2) * (3.5 + (4.5 * complex_straight[0])))))
			{
			case 11: case 8:
				return 1;
			}
			multiply_by_i(complex_straight);
		}
		for (int turns = 0; turns < 4; turns++)//checking diagonals for white bishop and queen in a similar loop stucture as rooks.
		{
			switch (is_colliding(position_row, position_column, position_row + (complex_diagonal[1] * 8), position_column + (complex_diagonal[0] * 8)))
			{
			case 11: case 10:
				return 1;
			}
			multiply_by_i(complex_diagonal);
		}
		for (int turns = 0; turns < 8; turns++)//checking for white knight using the diagonal vector.
		{
			//on even turns, the rows are incremented by 1 in the direction of the complex vector and the columns by 2.
			//On odd turns, rows are incremented by 2 and columns by 1 to create an L shape similar to the movement of a knight.
			if (position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2)))) >= 0 && position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2)))) <= 7 && position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2)))) >= 0 && position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2)))) <= 7)
			{
				//The above check checks if the indexes are inside the positions array. 
				if (positions[position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2))))][position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))))] == 9)
				{
					//make the position of the knight the position of the checking piece.
					special_moves[5][0] = position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2))));//row the knight is on.
					special_moves[5][0] = position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))));//column the knight is on.
					return 1;
				}
			}
			if (turns % 2)
			{
				multiply_by_i(complex_diagonal);
			}
		}
		for (int turns = 0; turns < 8; turns++)//checking for white king.
		{
			if (position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)) >= 0 && position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)) <= 7 && position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)) >= 0 && position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)) <= 7)
			{
				if (positions[position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2))][position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2))] == 12)
				{
					//since the king can't check another king, the position of the checking piece isn't updated
					return 1;
				}
			}
			if (turns % 2)
			{
				multiply_by_i(complex_diagonal);
			}
			else
			{
				multiply_by_i(complex_straight);
			}
		}
		//check for white pawns diagonally in front of the piece.
		if (positions[position_row + 1][position_column + 1] == 7)
		{
			special_moves[5][0] = position_row + 1;
			special_moves[5][1] = position_column + 1;
			return 1;
		}
		else if (positions[position_row + 1][position_column - 1] == 7)
		{
			special_moves[5][0] = position_row + 1;
			special_moves[5][1] = position_column - 1;
			return 1;
		}
		return 0;
	case 7: case 8: case 9: case 10: case 11: case 12://if the piece is white.
		for (int turns = 0; turns < 4; turns++)//checks for a black rook or queen in the same columns or rows as the piece.
		{
			//every even turn, columns are checked in the direction of the second entry in the complex vector, and rows are checked every odd turn.
			switch (is_colliding(position_row, position_column, (position_row * ((turns + 1) % 2)) + ((turns % 2) * (3.5 + (4.5 * complex_straight[1]))), (position_column * (turns % 2)) + (((turns + 1) % 2) * (3.5 + (4.5 * complex_straight[0])))))
			{
			case 5: case 2:
				return 1;
			}
			multiply_by_i(complex_straight);
		}
		for (int turns = 0; turns < 4; turns++)//checking diagonals for black bishop and queen in a similar loop structure as rooks.
		{
			switch (is_colliding(position_row, position_column, position_row + (complex_diagonal[1] * 8), position_column + (complex_diagonal[0] * 8)))
			{
			case 5: case 4:
				return 1;
			}
			multiply_by_i(complex_diagonal);
		}
		for (int turns = 0; turns < 8; turns++)//checking for black knight using the diagonal vector.
		{
			//on even turns, the rows are incremented by 1 in the direction of the complex vector and the columns by 2. 
			//On odd turns, rows are incremented by 2 and columns by 1 to create an L shape similar to the movement of a knight.
			if (position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2)))) >= 0 && position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2)))) <= 7 && position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2)))) >= 0 && position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2)))) <= 7)
			{
				//The above check checks if the indexes are inside the positions array.
				if (positions[position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2))))][position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))))] == 3)
				{
					//make the position of the knight the position of the checking piece.
					special_moves[5][0] = position_row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2))));//row the knight is at.
					special_moves[5][1] = position_column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))));//column the knight is at.
					return 1;
				}
			}
			if (turns % 2)
			{
				multiply_by_i(complex_diagonal);
			}
		}
		for (int turns = 0; turns < 8; turns++)//checking for black king.
		{
			//since the king can move in any direction, the straight vector is used on even turns and the diagonal complex vector is used on odd turns.
			if (position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)) >= 0 && position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)) <= 7 && position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)) >= 0 && position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)) <= 7)
			{
				if (positions[position_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2))][position_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2))] == 6)//if there's a king around the piece
				{
					//since the king can't check another king, the position of the checking piece isn't updated
					return 1;
				}
			}
			if (turns % 2)
			{
				multiply_by_i(complex_diagonal);
			}
			else
			{
				multiply_by_i(complex_straight);
			}
		}
		//check for black pawn diagonally in front of the piece.
		if (positions[position_row - 1][position_column + 1] == 1)
		{
			special_moves[5][0] = position_row - 1;
			special_moves[5][1] = position_column + 1;
			return 1;
		}
		else if (positions[position_row - 1][position_column - 1] == 1)
		{
			special_moves[5][0] = position_row - 1;
			special_moves[5][1] = position_column - 1;
			return 1;
		}
		return 0;
	default:
		return 0;
	}
}

int is_draw()
{
	int pieces[2][2] = { {0, 0},
						 {0, 0} };//counts the number of pieces, top row is black, bottom row is white, left column is bishops and knights, right column is pieces other than them.
	for (int row = 0; row < 8; row++)//checking if the only pieces left are a knight or a bishop.
	{
		for (int column = 0; column < 8; column++)
		{
			if (positions[row][column] == 3 || positions[row][column] == 4)//if it's a black bishop or a knight.
			{
				pieces[0][0]++;
			}
			else if (positions[row][column] == 9 || positions[row][column] == 10)//if it's a white bishop or a knight.
			{
				pieces[1][0]++;
			}
			else if (positions[row][column] >= 7)//if it's a white piece other than bishop and knight.
			{
				pieces[1][1]++;
			}
			else if (positions[row][column] > 0)//if it's a black piece other than bishop or knight.
			{
				pieces[0][1]++;
			}
		}
	}
	if (pieces[0][0] <= 1 && pieces[1][0] <= 1 && pieces[0][1] == 1 && pieces[1][1] == 1)// if only the kings are left with one bishop or knight each or less.
	{
		printf("Draw by insufficient material.\n");
		return 1;
	}
	for (int row = 0; row < 8; row++)//iterates throught the entire positions array. Similar techniques are used as in the is_under threat function.
	{
		for (int column = 0; column < 8; column++)
		{
			int complex_straight[2] = { 1, 0 };
			int complex_diagonal[2] = { 1, 1 };
			if (positions[row][column] == 1 + (6 * ((turn + 1) % 2)))//if the piece is a pawn.
			{
				multiply_by_i(complex_straight);
				for (int turns = 1; turns < 4; turns++)//checks if the pawn can legally move one block forward either straight or diagonally.
				{
					if (!is_illegal(row, column, row + (((turn % 2) * 2) - 1) * ((complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2))), column + (((turn % 2) * 2) - 1) * ((complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)))))//if a move is possible one block in any direction
					{
						return 0;
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
					else
					{
						multiply_by_i(complex_straight);
					}
				}
			}
			else if (positions[row][column] == 2 + (6 * ((turn + 1) % 2)))//if the piece is a rook.
			{
				for (int turns = 0; turns < 4; turns++)//checks if the rook can legally move one block straight in any direction.
				{
					if (!is_illegal(row, column, row + complex_straight[1], column + complex_straight[0]))//if a move is possible one bloack in any direction.
					{
						return 0;
					}
					multiply_by_i(complex_straight);
				}
			}
			else if (positions[row][column] == 3 + (6 * ((turn + 1) % 2)))//if the piece is a knight.
			{
				for (int turns = 0; turns < 8; turns++)//checks if the knight can legally move anywhere in its surrounding.
				{
					if (!is_illegal(row, column, row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2)))), column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))))))
					{
						return 0;
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
				}
			}
			else if (positions[row][column] == 4 + (6 * ((turn + 1) % 2)))//if the piece is a bishop.
			{
				for (int turns = 0; turns < 4; turns++)
				{
					if (!is_illegal(row, column, row + complex_diagonal[1], column + complex_diagonal[0]))//if a move is possible one block in any direction.
					{
						return 0;
					}
					multiply_by_i(complex_diagonal);
				}
			}
			else if (positions[row][column] == 5 + (6 * ((turn + 1) % 2)) || positions[row][column] == 6 + (6 * ((turn + 1) % 2)))//if the piece is a king or queen.
			{
				for (int turns = 0; turns < 8; turns++)
				{
					if (!is_illegal(row, column, row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)), column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2))))
					{
						//if a move is possible one block in any direction.
						return 0;
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
					else
					{
						multiply_by_i(complex_straight);
					}
				}
			}
		}
	}
	//if no piece of the player can make a legal move, it's a stalemate.
	printf("Draw by Stalemate\n");
	return 1;
}

int is_checkmate(int king_row, int king_column, int piece_row, int piece_column)
{
	//uses techniques similar to those used in the is_colliding and is_under threat and is_draw functions
	int complex_straight[2] = { 1, 0 };//complex vector (change in column, change in row)
	int complex_diagonal[2] = { 1, 1 };
	int change = 0;//change between either rows or columns
	int sign_row = sign(piece_row - king_row);
	int sign_column = sign(piece_column - king_column);
	for (int turns = 0; turns < 8; turns++)//can the king move anywhere
	{
		if (!is_illegal(king_row, king_column, king_row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)), king_column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2))))//if a move is possible one block in any direction
		{
			return 0;
		}
		if (turns % 2)
		{
			multiply_by_i(complex_diagonal);
		}
		else
		{
			multiply_by_i(complex_straight);
		}
	}

	//can a piece interfere between the king and the checking piece.
	if (king_column == piece_column)//if columns of the king and the checking piece are the same, use the change in rows, otherwise use the change in columns 
	{
		change = abs(piece_row - king_row);
	}
	else
	{
		change = abs(piece_column - king_column);
	}
	if (king_column == piece_column || king_row == piece_row || abs(king_column - piece_column) == abs(king_row - piece_row))//if the checking piece is a pawn, bishop, rook or queen.
	{
		//This loop runs from one block ahead of the king's position, to the piece checking it.
		//It checks if that piece can either be killed or can a piece come between the king and the piece checking it.
		for (int position = 1; (position <= change) && (king_row + (position * sign_row) >= 0) && (king_row + (position * sign_row) <= 7) && (king_column + (position * sign_column) >= 0) && (king_column + (position * sign_column) <= 7); position++)
		{
			//is the piece under threat by any of the player's pieces
			if (is_under_threat(king_row + (position * sign_row), king_column + (position * sign_column), 6 + (6 * (turn % 2)))) 
			{
				//is it legal to kill the piece
				if (!is_illegal(special_moves[5][0], special_moves[5][1], king_row + (position * sign_row), king_column + (position * sign_column)))
				{
					return 0;
				}
			}
		}
	}
	else if ((abs(king_column - piece_column) == 2 && abs(king_row - piece_row) == 1) || (abs(king_column - piece_column) == 1 && abs(king_row - piece_row) == 2))//if the checking piece is a knight.
	{
		if (is_under_threat(piece_row, piece_column, 6 + (6 * (turn % 2))))//is the piece under threat by any of the player's pieces
		{
			if (!is_illegal(special_moves[5][0], special_moves[5][1], piece_row, piece_column))//is it legal to kill the piece
			{
				return 0;
			}
		}
	}
	return 1;
}

void pawn_promotion(int move_from_row, int move_from_column, int move_to_row, int move_to_column)//promotes a pawn if it reaches the end of the board
{
	char choice;
	printf("Please choose from the following to promote your pawn to:\nQ for queen\nR for rook\nB for bishop\nK for knight\n");
	scanf_s(" %c", &choice);
	scanf_s("%c", &empty_char);
	choice = toupper(choice);

	switch (choice)
	{
	case 'Q':
		positions[move_from_row][move_from_column] = 11 - ((turn % 2) * 6);
		break;

	case 'R':
		positions[move_from_row][move_from_column] = 8 - ((turn % 2) * 6);
		break;

	case 'B':
		positions[move_from_row][move_from_column] = 10 - ((turn % 2) * 6);
		break;

	case 'K':
		positions[move_from_row][move_from_column] = 9 - ((turn % 2) * 6);
		break;
	}
}

int sign(int a)//determines the sign of a number given as either +1, -1 or 0.
{
	if (a > 0)
	{
		return 1;
	}
	else if (a < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void multiply_by_i(int complex[])//multiples a complex number by imaginary number 'i'.
{
	int temp = -*(complex + 1);
	*(complex + 1) = *complex;
	*complex = temp;
}

void chess_engine(int level, int* move_final)
{
	int move[4] = { 8,8,8,8 };
	int turn_temp = turn;
	int positions_copy[8][8];
	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			positions_copy[row][column] = positions[row][column];
		}
	}


	int move_value = 0;
	best_move((turn + 1) % 2, move_final);
	positions[move_final[2]][move_final[3]] = positions[move_final[0]][move_final[1]];
	positions[move_final[0]][move_final[1]] = 0;
	move_value += worth(move_final[2], move_final[3]) * ((2 * ((turn + 1) % 2)) - 1);
	turn++;
	for (int layer = 1; layer < level; layer++)
	{
		best_move((turn + 1) % 2, move);
		positions[move_final[2]][move_final[3]] = positions[move_final[0]][move_final[1]];
		positions[move_final[0]][move_final[1]] = 0;
		move_value += worth(move[2], move[3]) * (2 * ((turn + 1) % 2) - 1);
		turn++;
	}

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			positions[row][column] = positions_copy[row][column];
		}
	}
	turn = turn_temp;

	if (move_final[0] != 8)
	{
		checked_moves[counter][0] = move_final[0];
		checked_moves[counter][1] = move_final[1];
		checked_moves[counter][2] = move_final[2];
		checked_moves[counter][3] = move_final[3];
		checked_moves[counter][4] = move_value;
		counter++;
		chess_engine(level, move_final);
	}
	if (turn % 2)
	{
		smallest(move_final);
	}
	else
	{
		biggest(move_final);
	}
}

void best_move(int color, int* move)
{
	move[0] = 8;
	move[1] = 8;
	move[2] = 8;
	move[3] = 8;

	for (int row = 0; row < 8; row++)
	{
		for (int column = 0; column < 8; column++)
		{
			int complex_straight[2] = { 1, 0 };
			int complex_diagonal[2] = { 1, 1 };
			if (positions[row][column] == 1 + (color * 6))//pawn
			{
				if (row == 1 + (color * 5))
				{
					int row_to = row + 2 * ((((color + 1) % 2) * 2) - 1);
					if (!is_illegal(row, column, row_to, column))//if a move is possible one block in any direction
					{
						if (worth(row_to, column) > worth(move[2], move[3]))
						{
							move[0] = row;
							move[1] = column;
							move[2] = row_to;
							move[3] = column;
						}
					}
				}
				multiply_by_i(complex_straight);
				for (int turns = 1; turns < 4; turns++)//checks if the pawn can legally move one block forward either straight or diagonally.
				{
					int row_to = row + ((((color + 1) % 2) * 2) - 1) * ((complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2)));
					int column_to = column + ((((color + 1) % 2) * 2) - 1) * ((complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2)));
					if (!is_illegal(row, column, row_to, column_to))//if a move is possible one block in any direction
					{
						if (worth(row_to, column_to) > worth(move[2], move[3]))
						{
							move[0] = row;
							move[1] = column;
							move[2] = row_to;
							move[3] = column_to;
						}
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
					else
					{
						multiply_by_i(complex_straight);
					}
				}
			}
			else if (positions[row][column] == 2 + (color * 6))//rook
			{
				for (int turns = 0; turns < 4; turns++)//checks if the rook can legally move one block straight in any direction.
				{
					for (int distance = 1; distance < 8; distance++)
					{
						int row_to = row + distance * complex_straight[1];
						int column_to = column + distance * complex_straight[0];
						if (!is_illegal(row, column, row_to, column_to))//if a move is possible one block in any direction
						{
							if (worth(row_to, column_to) > worth(move[2], move[3]))
							{
								move[0] = row;
								move[1] = column;
								move[2] = row_to;
								move[3] = column_to;
							}
						}
					}
					multiply_by_i(complex_straight);
				}
			}
			else if (positions[row][column] == 3 + (color * 6))//knight
			{
				for (int turns = 0; turns < 8; turns++)//checks if the knight can legally move anywhere in its surrounding.
				{
					int row_to = row + (complex_diagonal[1] * ((2 * (turns % 2)) + (1 * ((turns + 1) % 2))));
					int column_to = column + (complex_diagonal[0] * ((2 * ((turns + 1) % 2)) + (1 * (turns % 2))));
					if (!is_illegal(row, column, row_to, column_to))
					{
						if (worth(row_to, column_to) > worth(move[2], move[3]))
						{
							move[0] = row;
							move[1] = column;
							move[2] = row_to;
							move[3] = column_to;
						}
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
				}
			}
			else if (positions[row][column] == 4 + (color * 6))//bishop
			{
				for (int turns = 0; turns < 4; turns++)
				{
					for (int distance = 1; distance < 8; distance++)
					{
						int row_to = row + distance * complex_diagonal[1];
						int column_to = column + distance * complex_diagonal[0];
						if (!is_illegal(row, column, row_to, column_to))//if a move is possible one block in any direction.
						{
							if (worth(row_to, column_to) > worth(move[2], move[3]))
							{
								move[0] = row;
								move[1] = column;
								move[2] = row_to;
								move[3] = column_to;
							}
						}
					}
					multiply_by_i(complex_diagonal);
				}
			}
			else if (positions[row][column] == 5 + (color * 6))//queen
			{
				for (int turns = 0; turns < 8; turns++)
				{
					for (int distance = 1; distance < 8; distance++)
					{
						int row_to = row + distance * (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2));
						int column_to = column + distance * (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2));
						if (!is_illegal(row, column, row_to, column_to))
						{
							if (worth(row_to, column_to) > worth(move[2], move[3]))
							{
								move[0] = row;
								move[1] = column;
								move[2] = row_to;
								move[3] = column_to;
							}
						}
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
					else
					{
						multiply_by_i(complex_straight);
					}
				}
			}
			else if (positions[row][column] == 6 + (color * 6))//king
			{
				for (int turns = 0; turns < 8; turns++)
				{
					int row_to = row + (complex_straight[1] * ((turns + 1) % 2)) + (complex_diagonal[1] * (turns % 2));
					int column_to = column + (complex_straight[0] * ((turns + 1) % 2)) + (complex_diagonal[0] * (turns % 2));
					if (!is_illegal(row, column, row_to, column_to))
					{
						if (worth(row_to, column_to) > worth(move[2], move[3]))
						{
							move[0] = row;
							move[1] = column;
							move[2] = row_to;
							move[3] = column_to;
						}
					}
					if (turns % 2)
					{
						multiply_by_i(complex_diagonal);
					}
					else
					{
						multiply_by_i(complex_straight);
					}
				}
			}
		}
	}
}

int worth(int move_to_row, int move_to_column)
{
	if (move_to_row >= 0 && move_to_row <= 7 && move_to_column >= 0 && move_to_column <= 7)
	{
		switch (positions[move_to_row][move_to_column])
		{
		case 1: case 7:
			return 1;
		case 2: case 8:
			return 5;
		case 3: case 4: case 9: case 10:
			return 3;
		case 5: case 11:
			return 9;
		case 6: case 12:
			return 100;
		default:
			return 0;
		}
	}
	else
	{
		return -1;
	}
}

void biggest(int* move_final)
{
	int biggest = checked_moves[0][4];
	int location = 0;
	for (int i = 1; i < counter; i++)
	{
		if (checked_moves[i][4] > biggest)
		{
			biggest = checked_moves[i][4];
			location = i;
		}
	}
	move_final[0] = checked_moves[location][0];
	move_final[1] = checked_moves[location][1];
	move_final[2] = checked_moves[location][2];
	move_final[3] = checked_moves[location][3];
}

void smallest(int* move_final)
{
	int smallest = checked_moves[0][4];
	int location = 0;
	for (int i = 1; i < counter; i++)
	{
		if (checked_moves[i][4] < smallest)
		{
			smallest = checked_moves[i][4];
			location = i;
		}
	}
	move_final[0] = checked_moves[location][0];
	move_final[1] = checked_moves[location][1];
	move_final[2] = checked_moves[location][2];
	move_final[3] = checked_moves[location][3];
}