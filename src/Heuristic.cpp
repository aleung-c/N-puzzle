
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
    int y = 0;
    int x = 0;
	std::vector< std::vector<int> >::iterator row;
	std::vector<int>::iterator col;

	for (row = Values.begin(); row != Values.end(); row++, y++) 
	{
    	for (col = row->begin(); col != row->end(); col++, x++) 
    	{
        	if (*col != Npuzzle.TargetState.Values[y][x])
        		nbWrong++;	
        }
        x = 0;
    }
    return (nbWrong);
}

int 				Heuristic::CasesTrulyPlaced(std::vector< std::vector <int> > Values)
{
	int nbWrong = 0;
    int y = 0;
    int x = 0;
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;

    for (row = Values.begin(); row != Values.end(); row++, y++) 
    {
        for (col = row->begin(); col != row->end(); col++, x++) 
        {
            if (*col == Npuzzle.TargetState.Values[y][x])
                nbWrong++;  
        }
        x = 0;
    }
    return (nbWrong);
}

int              Heuristic::TilesOutOfRowandColumns(std::vector< std::vector <int> > Values)
{
    int nbWrong = 0;
    int y = 0;
    int x = 0;
    Point *point;
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;

    for (row = Values.begin(); row != Values.end(); row++, y++) 
    {
        for (col = row->begin(); col != row->end(); col++, x++) 
        {
            point = Heuristic::GetCoordFromValue(*col);
            if (point->getX() != x)
                nbWrong++;
            if (point->getY() != y)
                nbWrong++;
        }
        x = 0;
    }
    printf("Heuristic Tiles: %d\n", nbWrong);
    return (nbWrong);
}

int              Heuristic::ManhattanImproved(std::vector< std::vector<int> > Values)
{
    int Distance = 0;
    int x = 0;
    int y = 0;
    
    std::vector<std::vector<int> > Tab(Values.size(), std::vector<int>(Values.size(), 0));
    std::vector< std::vector<int> >::iterator row;
    std::vector<int>::iterator col;

    for (row = Values.begin(); row != Values.end(); row++, y++) 
    {
        for (col = row->begin(); col != row->end(); col++, x++) 
        {
             if ((Tab[y][x] = Heuristic::DistanceManhattan(new Point(col - row->begin(), row - Values.begin()), Heuristic::GetCoordFromValue(*col))) == 1)
             {
                if ((x - 1 >= 0 && Tab[y][x - 1] == 1 && PStools::IsTruePosition(Npuzzle.TargetState, *col, Point(x - 1, y))) 
                    || (y - 1 >= 0 && Tab[y - 1][x] == 1 && PStools::IsTruePosition(Npuzzle.TargetState, *col, Point(x, y - 1))))
                if (x - 1 >= 0 && Tab[y][x - 1] == 1 && PStools::IsTruePosition(Npuzzle.TargetState, *col, Point(x - 1, y)))
                {
                    printf("x: %d y: %d\n", x, y);
                    Distance += 2;
                }
             }
             Distance += Tab[y][x];
        }
        x = 0;
    }
    return (Distance);
}
/***********************************End Of Public Method***********************************/

/***********************************Private Method*****************************************/
int					Heuristic::DistanceManhattan(Point *Source, Point *Target)
{
	 return (abs(Target->getX() - Source->getX()) + abs(Target->getY() - Source->getY()));
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

