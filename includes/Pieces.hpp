#ifndef __PIECES__
# define __PIECES__
# include <string>

using namespace std;
# include "./utils.hpp"

#ifndef PIECES
#define PIECES ".PRNBQKprnbqk" // Default value if not provided by the compiler
#endif

constexpr bool WHITE = false;
constexpr bool BLACK = true;

constexpr char EMPTY = PIECES[0];
constexpr char WPAWN = PIECES[1];
constexpr char WROOK = PIECES[2];
constexpr char WKNIGHT = PIECES[3];
constexpr char WBISHOP = PIECES[4];
constexpr char WQUEEN = PIECES[5];
constexpr char WKING = PIECES[6];
constexpr char BPAWN = PIECES[7];
constexpr char BROOK = PIECES[8];
constexpr char BKNIGHT = PIECES[9];
constexpr char BBISHOP = PIECES[10];
constexpr char BQUEEN = PIECES[11];
constexpr char BKING = PIECES[12];

constexpr char BASEPOS[] =
    {WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK,
     WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN,
     BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK};
class Piece
{
	public:
	bool color;		// The Color of the Piece (0 for white - 1 for black)
	char piece;		// The Name of the Piece (0 - blank, 1 - pawn, 2 - knight, 3 - bishop, 4 - rook, 5 - queen, 6 - king)

	Piece();
	Piece(unsigned char c);
	bool decode(unsigned char c);
	Piece operator=(const Piece &piece);
};

#endif
