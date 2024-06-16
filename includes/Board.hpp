#ifndef __BOARD__
# define __BOARD__

# include "./Pieces.hpp"
# include "./List.hpp"

class Board
{
	public:
		List<const char *> move_list;
		Board();
		Board(std::string hex_setup);
		~Board();
		void set(std::string hex_setup);		// Setup the Board with determined position
		void print(bool color);					// Print the Board, 0 for the white PoV - 1 for the black PoV
		bool square_color(const char pos);
		bool square_color(const char *pos);		// Get the color of a square
		Piece& at(const char index);
		Piece& at(const char *pos);				// Returns the Piece in a determined square	
		Board& move(const char *move);
		unsigned const char case_to_num(const char *pos);
		unsigned const char *num_to_case(unsigned const char index);
		List<t_move>get_vertical_moves(const char *pos); 
	private:
		std::string hex_setup;
		bool turn_to_move;
		bool black_can_long_castle;
		bool black_can_short_castle;
		bool white_can_long_castle;
		bool white_can_short_castle;

		Piece board[64];

		void init(void);
		const char *get_pawn_move(const char *pos);
		//List<const char *> get_slider_move(const char *pos);
	public:
		unsigned const char squares[64][3] = {
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