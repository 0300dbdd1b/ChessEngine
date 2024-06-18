#include "../includes/Game.hpp"
#include "../includes/Board.hpp"


using namespace std;
int main()
{

	Board board;
	Game game (board);
	// make a move
	t_move move {"h2" ,"h4"};
	game.board.move(move);
	//board.move("g7g5");
	
	// print the board from white perspective
	game.board.advanced_print(WHITE);
	cout << "EVAL : " << game.eval() << endl;
	// 

	List<t_move> moves = game.board.get_moves(WHITE);
	for  (size_t i = 0; i < moves.size(); i++)
	{
		cout << moves.at(i).from << " " << moves.at(i).to << endl;
	}

}
