
#include "Npuzzle.hpp"

/*
**	All Heuristic fonctions to solve the n-puzzle
*/
class Heuristic
{
	public:
		static int				Manhattan(std::vector< std::vector <int> > Values);
		static int 				CasesWronglyPlaced(std::vector< std::vector <int> > Values);
		static int 				CasesTrulyPlaced(std::vector< std::vector <int> > Values);

	private: 
		static	int				DistanceManhattan(Point *Source, Point *Target);
		static  Point			*GetCoordFromValue(int Value);
};
