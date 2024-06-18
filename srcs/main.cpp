#include "../includes/Game.hpp"
#include "../includes/Board.hpp"


using namespace std;
int main()
{

	Board board;
	Game game (board);
	// make a move
	game.board.move("h2h4");
	board.move("g7g5");
	
	game.board.turn_to_move = BLACK;
	// print the board from white perspective
	game.board.advanced_print(WHITE);
	cout << "EVAL : " << game.eval() << endl;
	// 

	List<t_move> moves = game.board.get_moves(WHITE);
	for  (int i = 0; i < moves.size(); i++)
	{
		cout << moves.at(i).from << " " << moves.at(i).to << endl;
	}

}
