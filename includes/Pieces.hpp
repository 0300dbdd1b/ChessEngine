#ifndef __PIECES__
# define __PIECES__
# include <string>

using namespace std;

#ifndef PIECES
#define PIECES " PRNBQKprnbqk" // Default value if not provided by the compiler
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
    {BROOK, BKNIGHT, BBISHOP, BQUEEN, BKING, BBISHOP, BKNIGHT, BROOK,
     BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN, BPAWN,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN, WPAWN,
     WROOK, WKNIGHT, WBISHOP, WQUEEN, WKING, WBISHOP, WKNIGHT, WROOK};



typedef struct s_move
{
	const unsigned char *from;
	const unsigned char *to;
}t_move;

class Piece
{
	public:
	bool color;		// The Color of the Piece (0 for white - 1 for black)
	char piece;		// The Name of the Piece (0 - blank, 1 - pawn, 2 - knight, 3 - bishop, 4 - rook, 5 - queen, 6 - king)

	Piece();
	Piece(unsigned char c);
	bool decode(unsigned char c);
	Piece operator=(const Piece &piece);
	void move(const t_move move);
	t_move *get_knight_moves(const char *pos);
};

#endif
