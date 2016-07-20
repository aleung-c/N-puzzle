
#include "Npuzzle.hpp"

/*
**	All Heuristic fonctions to solve the n-puzzle
*/
class Heuristic
{
	public:
		static int				Manhattan(int x1, int y1, int x2, int y2);
		static int 				CasesWronglyPlaced(std::vector< std::vector <int> > Values);
		static int 				CasesTrulyPlaced(std::vector< std::vector <int> > Values);
};
