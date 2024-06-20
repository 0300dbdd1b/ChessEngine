#include "../includes/Game.hpp"
#include "../includes/Board.hpp"


using namespace std;
int main()
{

	Board board;
	Game game (board);
	// make a move
	t_move move1 {"h2" ,"h4"};
	t_move move2 {"g7" ,"g5"};

	t_move move3 {"h4" ,"g5"};
	//board.move("g7g5");
	game.board.move(move1);
	game.board.move(move2);
	game.board.move(move3);
	
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
