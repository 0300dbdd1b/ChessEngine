#ifndef __GAME__
# define __GAME__
# include "./Board.hpp"

#include <iostream>
#include <string>
#include <list>
#include <set>

// Assuming the necessary definitions for List, t_move, Board, Piece, etc.

class Game 
{
	public:
    Game(Board& board) : board(board) {}
    int eval();

    void compute_control_and_captures(bool side, int &controlled_squares, int &captured_pieces);

	Board& board;
};


#endif
