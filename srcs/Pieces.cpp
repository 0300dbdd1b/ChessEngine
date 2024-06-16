#include "../includes/Pieces.hpp"
#include <iostream>

using namespace std;
bool Piece::decode(unsigned char hex_piece)
{
	std::string hex_str = "0123456789abcdef";
	hex_piece = (char)(hex_str.find(hex_piece));
	this->color = hex_piece & 1;
	this->piece = hex_piece >> 1;
	return true;
}

Piece::Piece()
{
	this->piece = 0;
	this->color = false;

}

Piece::Piece(unsigned char hex_piece)
{
	this->decode(hex_piece);

}

Piece Piece::operator=(const Piece &piece)
{
	this->color = piece.color;
	this->piece = piece.piece;
	return (*this);
}