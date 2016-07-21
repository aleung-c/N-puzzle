
#include "../includes/Npuzzle.hpp"

int				Heuristic::Manhattan(int x1, int y1, int x2, int y2)
{
	return (std::abs(x2 - x1) + std::abs(y2 - y1));
}

int 			Heuristic::CasesWronglyPlaced(std::vector< std::vector <int> > Values)
{
	int nbWrong = 0;
	int i = 0;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
        	i++;
        	if (i != *col)
        		nbWrong++;
        }
    }
    return (nbWrong);
}

int 				Heuristic::CasesTrulyPlaced(std::vector< std::vector <int> > Values)
{
	int nbTrue = 0;
	int i = 0;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++) 
	{
    	for (col = row->begin(); col != row->end(); col++) 
    	{
        	i++;
        	if (i == *col)
        		nbTrue++;
        }
    }
    return (nbTrue);
}