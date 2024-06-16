#ifndef __PIECES__
# define __PIECES__
# include <string>

# include "./utils.hpp"

# define WHITE bool(false)
# define BLACK bool(true)
# define EMPTY char(0)
# define PAWN char(1)
# define KNIGHT char(2)
# define BISHOP char(3)
# define ROOK char(4)
# define QUEEN char(5)
# define KING char(6)

class Piece
{
	public:
	bool color;		// The Color of the Piece (0 for white - 1 for black)
	char piece;		// The Name of the Piece (0 - blank, 1 - pawn, 2 - knight, 3 - bishop, 4 - rook, 5 - queen, 6 - king)

	Piece();
	Piece(unsigned char hex_piece);
	bool decode(unsigned char hex_piece);
	Piece operator=(const Piece &piece);
};

#endif