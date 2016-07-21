
#include "../includes/Npuzzle.hpp"

t_NpuzzleData		Npuzzle;
/***********************************Public Method***********************************/
int				Heuristic::Manhattan(std::vector< std::vector <int> > Values)
{
	int Distance = 0;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
        	Distance += Heuristic::DistanceManhattan(new Point(col - row->begin(), row - Values.begin()), Heuristic::GetCoordFromValue(*col));
    }
    return (Distance);
}

int 			Heuristic::CasesWronglyPlaced(std::vector< std::vector <int> > Values)
{
	int nbWrong = 0;
	int i = 1;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
        	if (!(i == *col || (i == (int)(Values.size() * Values.size()) && *col == 0)))
        		nbWrong++;	
        	i++;
        }
    }
    return (nbWrong);
}

int 				Heuristic::CasesTrulyPlaced(std::vector< std::vector <int> > Values)
{
	int nbTrue = 0;
	int i = 1;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
        	if ((i == *col || (i == (int)(Values.size() * Values.size()) && *col == 0)))
        		nbTrue++;
        	i++;
        }
    }
    return (nbTrue);
}
/***********************************End Of Public Method***********************************/

/***********************************Private Method*****************************************/
int					Heuristic::DistanceManhattan(Point *Source, Point *Target)
{
	 return (std::abs(Target->getX() - Source->getX()) + std::abs(Target->getY() - Source->getY()));
}

Point				*Heuristic::GetCoordFromValue(int Value)
{
	std::vector< std::vector <int> > Values = Npuzzle.TargetState.Values;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
        	if (*col == Value)
        		return (new Point(col - row->begin(), row - Values.begin()));
        }
    }
    return (new Point(0,0));
}
/************************************End of Private Method***********************************/

