#ifndef __BOARD__
# define __BOARD__

# include <cstring>
# include <set>
# include "./Pieces.hpp"
# include "./List.hpp"

using namespace std;
class Board
{
	public:
		List<t_move> move_list;
		Board();
		Board(const char *setup, const char info=0b01111);
		~Board();
		void set(const char *setup, const char info=0b01111);		// Setup the Board with determined position
		void print(bool color);					// Print the Board, 0 for the white PoV - 1 for the black PoV
		void advanced_print(bool color);
		bool square_color(const char pos);
		bool square_color(const char *pos);		// Get the color of a square
		Piece& at(const char index);
		Piece& at(const char *pos);				// Returns the Piece in a determined square	
		Board& move(t_move &move);
		char case_to_num(const char *pos);
		const char *num_to_case(char index);
		
		List<t_move>get_legal_moves(bool side);
		List<t_move>get_moves(bool side);
		List<t_move>get_moves(const char *post);
		List<t_move>get_diagonal_moves(const char *pos);
		List<t_move>get_vertical_moves(const char *pos); 
		List<t_move>get_horizontal_moves(const char *pos);
		List<t_move>get_knight_moves(const char *pos);
		List<t_move>get_pawn_moves(const char *pos);
		List<t_move>get_king_moves(const char *pos);
		List<t_move>get_queen_moves(const char *pos);
		List<t_move>get_rook_moves(const char *pos);
		void compute_control_and_captures(bool side, int &controlled_squares, int &captured_pieces);
		
		double eval();
		const char *hex_setup;
		bool turn_to_move;
		bool black_can_long_castle;
		bool black_can_short_castle;
		bool white_can_long_castle;
		bool white_can_short_castle;

		Piece board[64];
 
		void init(void);
		//List<const char *> get_slider_move(const char *pos);
	public:
		const char squares[64][3] = {
			"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
			"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
			"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
			"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
			"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
			"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
			"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
			"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"
			};


};



#endif
