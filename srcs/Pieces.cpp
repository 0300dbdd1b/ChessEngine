#include "../includes/Pieces.hpp"
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;


bool Piece::decode(unsigned char c)
{
	this->color = isupper(c);
	const char *pos = strchr(PIECES, c);
	if (pos)
	{
		this->piece = *pos;
	}
	else
	{
		this->piece = EMPTY;
	}
	return true;
}

Piece::Piece()
{
	this->piece = EMPTY;
	this->color = WHITE;

}

Piece::Piece(unsigned char c)
{

	this->decode(c);

}

Piece Piece::operator=(const Piece &piece)
{
	this->color = piece.color;
	this->piece = piece.piece;
	return (*this);
}

void Piece::move(const t_move move)
{
	
	return;
}

t_move * Piece::get_knight_moves(const char *pos)
{
	t_move *a;
	return a;
}
