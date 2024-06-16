
#include "../includes/Board.hpp"


using namespace std;
int main()
{

	Board board;
	// make a move
	board.move("h2h4");
	
	// print the board from white perspective
	board.print(WHITE);

	// 
	board.move_list.print();
	cout << "aled : " <<  board.squares[7] << endl;
	cout << +board.case_to_num("h8") << endl;
	cout << board.num_to_case(11) << endl;

	List<t_move> moves = board.get_vertical_moves("d2");
	for  (int i = 0; i < moves.size(); i++)
	{
		cout << moves.at(i).from << " ";
		cout << moves.at(i).to << endl;
	}

}
