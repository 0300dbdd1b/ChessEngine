#include "../includes/Board.hpp"
#include "../includes/Pieces.hpp"
#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdangling-gsl"


Board::~Board(void)
{
	move_list.empty();
}

void Board::init()
{
	black_can_long_castle = true;
	black_can_short_castle = true;
	white_can_long_castle = true;
	white_can_short_castle = true;
	turn_to_move = WHITE;
	
}

void Board::set(const char *hex_setup)
{
	for (unsigned char i = 0; i < 64; i++)
	{
		board[i] = Piece(hex_setup[i]);
	}
}

Board::Board(const char *hex_setup)
{
	set(hex_setup);
}

Board::Board()
{
	set(BASEPOS);

	init();
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
			if (this->board[(int(i/8)*8) + 7-(i%8)].color == false)
				display = toupper(display);
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
			if (this->board[(int((i-1)/8)*8) + 7 -((i-1)%8)].color == false)
				display = toupper(display);
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
Board& Board::move(const char *move)
{
	const char *from = substr(move,0,2);
	const char *to = substr(move,2,4);
	Piece piece = this->at(from); 
	this->at(from) = Piece();
	this->at(to) = piece;
	move_list.add_last(move);
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

unsigned const char *Board::num_to_case(unsigned const char index)
{
	return (squares[index]);
}
