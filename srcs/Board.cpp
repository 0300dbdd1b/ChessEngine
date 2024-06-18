#include "../includes/Board.hpp"
#include "../includes/Pieces.hpp"
#include <cctype>
#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdangling-gsl"

using namespace std;

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
	/*	1st bit = black_can_long_castle
		2nd bit = black_can_short_castle
		3rd bit = white_can_long_castle
		4th bit = white_can_short_castle
		5th bit = turn_to_move
	*/
	set(BASEPOS, 0b11110);
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

void Board::advanced_print(bool color) {
    const std::string white_bg = "\033[47m";
    const std::string black_bg = "\033[40m";
    const std::string reset = "\033[0m";
    const std::string white_piece_color = "\033[34m"; // Cyan for white pieces
    const std::string black_piece_color = "\033[31m"; // Green for black pieces
    char display;
    std::string piece_color;

    if (color == BLACK) { // Print the board from black perspective
        std::cout << "Black Perspective :" << std::endl;
        for (unsigned char i = 0; i < 64; i++) {
            display = this->board[(int(i / 8) * 8) + 7 - (i % 8)].piece;
            piece_color = this->board[(int(i / 8) * 8) + 7 - (i % 8)].color == WHITE ? white_piece_color : black_piece_color;
            if (i % 8 == 0) {
                if (i > 0)
                    std::cout << "|" << (i / 8);
                std::cout << std::endl;
            }

            if ((i / 8 + i % 8) % 2 == 0)
                std::cout << white_bg << " " << piece_color << display << " " << reset;
            else
                std::cout << black_bg << " " << piece_color << display << " " << reset;
        }

        std::cout << "|8" << std::endl << "------------------" << std::endl;
        std::cout << "H G F E D C B A |" << std::endl << std::endl;
        return;
    } else if (color == WHITE) { // Print the board from white perspective
        std::cout << "White Perspective :" << std::endl;
        for (unsigned char i = 64; i > 0; i--) {
            display = this->board[(int((i - 1) / 8) * 8) + 7 - ((i - 1) % 8)].piece;
            piece_color = this->board[(int((i - 1) / 8) * 8) + 7 - ((i - 1) % 8)].color == WHITE ? white_piece_color : black_piece_color;
            if (i % 8 == 0)
                std::cout << std::endl << int(i / 8) << "| ";

            if (((i - 1) / 8 + (i - 1) % 8) % 2 == 0)
                std::cout << white_bg << " " << piece_color << display << " " << reset;
            else
                std::cout << black_bg << " " << piece_color << display << " " << reset;
        }
        std::cout << std::endl << "------------------" << std::endl;
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
	to[2] = 0;
	
	cout << "FROM : " << from << " TO : " << to << endl;
	this->at(to) = this->at(from);
	this->at(from) = Piece();

	move_list.add_last(move_str);
	this->turn_to_move = !this->at(to).color;
	return (*this);
}

// List<const char *> Board::get_slider_move(const char *pos)
// {
// 	char piece = at(pos).piece;
// 	const char *from;
// 	const char *to;
// 	return;
// }



List<t_move>Board::get_vertical_moves(const char *pos)
{
	List<t_move> output;
	t_move move;
	char index = case_to_num(pos);
	bool color = this->at(pos).color;
	for (char i = index+8; i < 64; i+=8)
	{

		move.from = (const unsigned char*)pos;
		move.to = num_to_case(i);
		if (at(i).piece == EMPTY)
		{
			output.add_last(move);
		}
		if ((at(i).piece != EMPTY) & (at(i).color != color))
		{
			output.add_last(move);
			break;
		}
	}
	for (char i = index-8; i < 64; i-=8)
	{

		move.from = (const unsigned char*)pos;
		move.to = num_to_case(i);
		if (at(i).piece == EMPTY)
		{
			output.add_last(move);
		}
		if ((at(i).piece != EMPTY) & (at(i).color != color))
		{
			output.add_last(move);
			break;
		}
	}

	return (output);
}


List<t_move> Board::get_horizontal_moves(const char* pos) {
    List<t_move> output;
    t_move move;
    char index = case_to_num(pos);
    bool color = this->at(pos).color;
    char row_start = index / 8 * 8;
    char row_end = row_start + 7;

    for (char i : {index + 1, index - 1}) {
        while (i >= row_start && i <= row_end) {
            move.from = (const unsigned char*)pos;
            move.to = num_to_case(i);
            if (at(i).piece == EMPTY) {
                output.add_last(move);
            } else {
                if (at(i).color != color) {
                    output.add_last(move);
                }
                break;
            }
            i += (i > index) ? 1 : -1;
        }
    }

    return output;
}



List<t_move> Board::get_diagonal_moves(const char* pos) {
    List<t_move> output;
    t_move move;
    char index = case_to_num(pos);
    bool color = this->at(pos).color;
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    int row, col, target_index;

    for (auto& dir : directions) {
        row = index / 8;
        col = index % 8;
        for (int i = 1; row + i * dir[0] < 8 && row + i * dir[0] >= 0 && col + i * dir[1] < 8 && col + i * dir[1] >= 0; ++i) {
            target_index = (row + i * dir[0]) * 8 + (col + i * dir[1]);
            move.from = (const unsigned char*)pos;
            move.to = num_to_case(target_index);
            if (at(target_index).piece == EMPTY) {
                output.add_last(move);
            } else {
                if (at(target_index).color != color) {
                    output.add_last(move);
                }
                break;
            }
        }
    }

    return output;
}



List<t_move> Board::get_knight_moves(const char* pos) {
    List<t_move> output;
    t_move move;
    char index = case_to_num(pos);
    bool color = this->at(pos).color;
    int knight_moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    int row = index / 8;
    int col = index % 8;

    for (auto& move_dir : knight_moves) {
        int new_row = row + move_dir[0];
        int new_col = col + move_dir[1];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            int target_index = new_row * 8 + new_col;
            move.from = (const unsigned char*)pos;
            move.to = num_to_case(target_index);
            if (at(target_index).piece == EMPTY || at(target_index).color != color) {
                output.add_last(move);
            }
        }
    }

    return output;
}



List<t_move> Board::get_pawn_moves(const char* pos) {
    List<t_move> output;
    t_move move;
    char index = case_to_num(pos);
    bool color = this->at(pos).color;
    int row = index / 8;
    int col = index % 8;
    int direction = color == WHITE ? 1 : -1;
    int start_row = color == WHITE ? 1 : 6;
    int end_row = color == WHITE ? 7 : 0;
    
    // Forward move
    int forward_index = index + direction * 8;
    if (forward_index >= 0 && forward_index < 64 && at(forward_index).piece == EMPTY) {
        move.from = (const unsigned char*)pos;
        move.to = num_to_case(forward_index);
        output.add_last(move);

        // Double forward move from starting position
        if (row == start_row) {
            int double_forward_index = forward_index + direction * 8;
            if (at(double_forward_index).piece == EMPTY) {
                move.to = num_to_case(double_forward_index);
                output.add_last(move);
            }
        }
    }

    // Captures
    int capture_moves[2] = {direction * 8 + 1, direction * 8 - 1};
    for (int i = 0; i < 2; ++i) {
        int capture_index = index + capture_moves[i];
        int new_col = col + (i == 0 ? 1 : -1);
        if (capture_index >= 0 && capture_index < 64 && new_col >= 0 && new_col < 8) {
            if (at(capture_index).piece != EMPTY && at(capture_index).color != color) {
                move.from = (const unsigned char*)pos;
                move.to = num_to_case(capture_index);
                output.add_last(move);
            }
        }
    }

    return output;
}


List<t_move> Board::get_queen_moves(const char* pos) {
    List<t_move> output;

    // Get all vertical moves
    List<t_move> vertical_moves = get_vertical_moves(pos);
    for (size_t i = 0; i < vertical_moves.size(); ++i) {
        output.add_last(vertical_moves.at(i));
    }

    // Get all horizontal moves
    List<t_move> horizontal_moves = get_horizontal_moves(pos);
    for (size_t i = 0; i < horizontal_moves.size(); ++i) {
        output.add_last(horizontal_moves.at(i));
    }

    // Get all diagonal moves
    List<t_move> diagonal_moves = get_diagonal_moves(pos);
    for (size_t i = 0; i < diagonal_moves.size(); ++i) {
        output.add_last(diagonal_moves.at(i));
    }

    return output;
}




List<t_move> Board::get_king_moves(const char* pos) {
    List<t_move> output;
    t_move move;
    char index = case_to_num(pos);
    bool color = this->at(pos).color;
    int king_moves[8][2] = {{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int row = index / 8;
    int col = index % 8;

    for (auto& move_dir : king_moves) {
        int new_row = row + move_dir[0];
        int new_col = col + move_dir[1];
        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8) {
            int target_index = new_row * 8 + new_col;
            move.from = (const unsigned char*)pos;
            move.to = num_to_case(target_index);
            if (at(target_index).piece == EMPTY || at(target_index).color != color) {
                output.add_last(move);
            }
        }
    }

    return output;
}


List<t_move> Board::get_rook_moves(const char* pos) {
    List<t_move> output;
    List<t_move> moves;

    // Get all vertical moves
    moves = get_vertical_moves(pos);
    for (size_t i = 0; i < moves.size(); ++i) {
        output.add_last(moves.at(i));
    }

    // Get all horizontal moves
    moves = get_horizontal_moves(pos);
    for (size_t i = 0; i < moves.size(); ++i) {
        output.add_last(moves.at(i));
    }

    return output;
}


List<t_move> Board::get_moves(const char* pos) {
    List<t_move> output;
    char piece = this->at(pos).piece;

    switch (piece) {
        case WPAWN:
        case BPAWN:
            output = get_pawn_moves(pos);
            break;
        case WKNIGHT:
        case BKNIGHT:
            output = get_knight_moves(pos);
            break;
        case WBISHOP:
        case BBISHOP:
            output = get_diagonal_moves(pos);
            break;
        case WROOK:
        case BROOK:
            output = get_rook_moves(pos);
            break;
        case WQUEEN:
        case BQUEEN:
            output = get_queen_moves(pos);
            break;
        case WKING:
        case BKING:
            output = get_king_moves(pos);
            break;
        default:
            // No valid piece at the position
            break;
    }

    return output;
}

List<t_move> Board::get_moves(bool side) 
{
    List<t_move> all_moves;
    for (int i = 0; i < 64; ++i) 
	{
        Piece piece = this->at(i);

        if  ((piece.piece != EMPTY) && ((side == WHITE && piece.color == WHITE) || (side == BLACK && piece.color == BLACK))) 
		{
            // Convert index to position string
            const unsigned char* pos = num_to_case(i);
			//cout << "LA POSITION EST " << pos << endl;
            List<t_move> piece_moves = get_moves(reinterpret_cast<const char *>(pos));
            for (int j = 0; j < piece_moves.size(); ++j) 
			{
                all_moves.add_last(piece_moves.at(j));
            }
        }
    }
    return all_moves;
}


unsigned const char Board::case_to_num(const char *pos)
{
	unsigned char col = pos[0] - 'a';
	unsigned char row = pos[1] - '0' - 1;
	unsigned const char result = row * 8 + col;
	return (result);
}

unsigned const char* Board::num_to_case(char index) {
	return this->squares[index];
}

void Board::compute_control_and_captures(bool side, int &controlled_squares, int &captured_pieces) 
{
    controlled_squares = 0;
    captured_pieces = 0;

    List<t_move> moves = get_moves(side);
	std::set<string> controlled_positions; // To track unique controlled squares

    for (size_t i = 0; i < moves.size(); ++i) {
        t_move move = moves.at(i);
        std::string to_pos(reinterpret_cast<const char*>(move.to));

        if (controlled_positions.find(to_pos) == controlled_positions.end()) {
            controlled_positions.insert(to_pos);
            controlled_squares++;
        }

        Piece target_piece = this->at((const char *)move.to);
        if (target_piece.piece != EMPTY && target_piece.color != (side == WHITE ? WHITE : BLACK)) {
            captured_pieces++;
        }
    }
}

double Board::eval() {
    int white_controlled_squares = 0, black_controlled_squares = 0;
    int white_captured_pieces = 0, black_captured_pieces = 0;

    // Compute control and captures for white
    compute_control_and_captures(WHITE, white_controlled_squares, white_captured_pieces);

    // Compute control and captures for black
    compute_control_and_captures(BLACK, black_controlled_squares, black_captured_pieces);

    // Calculate the evaluation score
    int control_eval = white_controlled_squares - black_controlled_squares;
    int capture_eval = white_captured_pieces - black_captured_pieces;

    return (double)(control_eval + capture_eval);
}
