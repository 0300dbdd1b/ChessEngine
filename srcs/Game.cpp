#include "../includes/Game.hpp"

void Game::compute_control_and_captures(bool side, int &controlled_squares, int &captured_pieces) {
    controlled_squares = 0;
    captured_pieces = 0;

    List<t_move> moves = board.get_moves(side);
    std::set<std::string> controlled_positions; // To track unique controlled squares

    for (size_t i = 0; i < moves.size(); ++i) {
        t_move move = moves.at(i);
        std::string to_pos(reinterpret_cast<const char*>(move.to));

        if (controlled_positions.find(to_pos) == controlled_positions.end()) {
            controlled_positions.insert(to_pos);
            controlled_squares++;
        }

        Piece target_piece = board.at((const char *)move.to);
        if (target_piece.piece != EMPTY && target_piece.color != (side == WHITE ? WHITE : BLACK)) {
            captured_pieces++;
        }
    }
}

int Game::eval() {
    int white_controlled_squares = 0, black_controlled_squares = 0;
    int white_captured_pieces = 0, black_captured_pieces = 0;


    // Compute control and captures for white
	cout << "EVAL :\n" << "WHITE CONTROLLED : " << white_controlled_squares << "\nWHITE_CAPTURE : " << white_captured_pieces << endl;
	cout << "BLACK CONTROLLED : " << black_controlled_squares << "\nBLACK_CAPTURE : " << black_captured_pieces << endl;
    compute_control_and_captures(WHITE, white_controlled_squares, white_captured_pieces);

    // Compute control and captures for black
    compute_control_and_captures(BLACK, black_controlled_squares, black_captured_pieces);

    if (board.turn_to_move == WHITE)
	{
		white_captured_pieces *= 2;
	}
	else
	{
		black_captured_pieces *=2;
	}
		// Calculate the evaluation score
    int control_eval = white_controlled_squares - black_controlled_squares;
    int capture_eval = white_captured_pieces - black_captured_pieces;

    return control_eval + capture_eval;
}
