#include "../includes/Board.hpp"
#include "../includes/Pieces.hpp"
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdangling-gsl"


Board::~Board(void)
{
	move_list.empty();
}


void Board::set(const char *setup, const char info)
{
	for (unsigned char i = 0; i < 64; i++)
	{
		board[i] = Piece(setup[i]);
	}

	black_can_long_castle = bool((info >> 4) & 1);
	black_can_short_castle = bool((info >> 3) & 1);
	white_can_long_castle = bool((info >> 2) & 1);
	white_can_short_castle = bool((info >> 1) & 1);
	turn_to_move = (info & 1);
    std::cout << "black_can_long_castle: " << black_can_long_castle << std::endl;
    std::cout << "black_can_short_castle: " << black_can_short_castle << std::endl;
    std::cout << "white_can_long_castle: " << white_can_long_castle << std::endl;
    std::cout << "white_can_short_castle: " << white_can_short_castle << std::endl;
    std::cout << "turn_to_move: " << turn_to_move << std::endl;
}

Board::Board(const char *setup, const char info)
{
	set(setup, info);
}

Board::Board()
{
	/*	5th bit = black_can_long_castle
		4th bit = black_can_short_castle
		3rd bit = black_can_short_castle
		2nd bit = black_can_long_castle
		1st bit = turn_to_move
	*/
	set(BASEPOS, 0b10111);
}

void Board::print(bool color)
{
	char display;
	if (color == BLACK) // Print the board from black perspective
	{
		std::cout << "Black Perspective :" << std::endl;
		for (unsigned char i = 0; i < 64; i++)
		{
			display = this->board[(int(i/8)*8) + 7-(i%8)].piece;
			if (i%8 == 0)
			{
				if (i>0)
					std::cout << "|" << (i/8);
				std::cout  << std::endl;	
			}
			std::cout << display << " ";
	
		}

		std::cout << "|8" << std::endl << "------------------" << std::endl;
		std::cout << "H G F E D C B A |" << std::endl << std::endl;
		return;
	}
	else if (color == WHITE) // Print the board from white perspective
	{
		std::cout << "White Perspective :" << std::endl;
		for (unsigned char i = 64; i > 0 ; i--)
		{
			display = this->board[(int((i-1)/8)*8) + 7 -((i-1)%8)].piece;
			if (i%8 == 0)
				std::cout << std::endl << int(i/8) << "| ";
			std::cout << display << " ";
		}
		std::cout << std::endl <<  "------------------" << std::endl;
		std::cout << " | A B C D E F G H" << std::endl << std::endl;
		return;
	}
}

bool Board::square_color(const char pos)
{
	unsigned char col = (char)int(pos%8) ;
	unsigned char row = (char)int(pos/8) ;
	if (row & 1)
		return !(1 -(col & 1));
	else
		return !(col & 1); 
}

bool Board::square_color(const char *pos)
{
	char col = pos[0] - 'a';
	char row = pos[1] - '0' - 1;
	if (row & 1)
		return !(1 -(col & 1));
	else
		return !(col & 1); 
}

Piece& Board::at(const char index)
{
	char row = index%8 + 'a';
	char col = index/8 + '0' + 1;
	if ((index >= 64) || (index < 0))
		return (this->at("a1"));
	char pos[3] = {row,col,'\0'};
	return (this->at(pos));
}

Piece& Board::at(const char *pos)
{
	if (strlen(pos) != 2)
		return (this->at("a1"));
	unsigned char col = tolower(pos[0]) - 'a';
	unsigned char row = tolower(pos[1]) - '0'- 1;
	if ((row >= 8) || (col >= 8))
		return (this->at("a1"));
	return (this->board[(row*8)+col]);
}

// Move a piece on the board
Board& Board::move(const char *move_str)
{
	string move(move_str);
	cout << "LA STRING EST : " << move  << endl;

	char from[3];
	strncpy(from, move.c_str(), 2);
	from[2] = 0;
	//const char *from = move.substr(0,2).c_str();
	//const char *to = move.substr(2,4).c_str();
	char to[3];
	strncpy(to, move.c_str() + 2,  2);
	from[2] = 0;
	
	cout << "FROM : " << from << " TO : " << to << endl;
	Piece piece = this->at(from); 
	this->at(from) = Piece();
	this->at(to) = piece;
	move_list.add_last(move_str);
	return (*this);
}

// List<const char *> Board::get_slider_move(const char *pos)
// {
// 	char piece = at(pos).piece;
// 	const char *from;
// 	const char *to;
// 	return;
// }

const char *Board::get_pawn_move(const char *pos)
{	
	return (pos);
}


List<t_move>Board::get_vertical_moves(const char *pos)
{
	List<t_move> output;
	t_move move;
	char index = case_to_num(pos);
	for (char i = index+8; i < 64; i+=8)
	{

		move.from = (const unsigned char*)pos;
		move.to = num_to_case(i);
		std::cout << "move : " << move.to << std::endl;
		if (at(i).piece == EMPTY)
		{
			output.add_last(move);
			std::cout << move.to << std::endl;
		}
		if (at(i).piece != EMPTY)
		{
			output.add_last(move);
			break;
		}
	}
	for (char i = index-8; i < 64; i-=8)
	{

		move.from = (const unsigned char*)pos;
		move.to = num_to_case(i);
		std::cout << "move : " << move.to << std::endl;
		if (at(i).piece == EMPTY)
		{
			output.add_last(move);
			std::cout << move.to << std::endl;
		}
		if (at(i).piece != EMPTY)
		{
			output.add_last(move);
			break;
		}
	}

	return (output);
}

unsigned const char Board::case_to_num(const char *pos)
{
	unsigned char col = pos[0] - 'a';
	unsigned char row = pos[1] - '0' - 1;
	unsigned const char result = row * 8 + col;
	return (result);
}

unsigned const char *Board::num_to_case(char index)
{
	return (squares[index]);
}
