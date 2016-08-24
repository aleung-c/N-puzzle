/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resolver.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:50:20 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/26 18:50:24 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Npuzzle.hpp"

Resolver::Resolver()
{

}

Resolver::Resolver(t_NpuzzleData *nPuzzle)
{
	this->CurNpuzzle = nPuzzle;

}

Resolver::~Resolver()
{

}


void						Resolver::Start()
{
	CurNpuzzle->NbOfMoves = 0;
	CurNpuzzle->FirstState.Cost = CurNpuzzle->CurHeuristic(CurNpuzzle->FirstState.Values);

	// Solubilité test
	if (IsPuzzleSolvable(CurNpuzzle->FirstState) == false)
	{
		// ◦ The puzzle may be unsolvable, in which case you have to inform the user and exit
		std:: cout << "Puzzle not resolvable, exiting." << std::endl;
		exit (0);
	}

	AStarTurn(CurNpuzzle->FirstState);
}

/*
**	Peut on resoudre ce puzzle ? 
*/
bool						Resolver::IsPuzzleSolvable(PuzzleState &State) // seems to work on 3 and 4 puzzles.
{
	Point 										ZeroStartPos;
	Point 										ZeroTargetPos;
	int 										ManhattanDistanceZero;
	int 										ManhattanDistanceState;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	std::vector<int> 							MergedPuzzleValues;

	// =====> get puzzle datas.
	// get First state Zero pos;
	ZeroStartPos = PStools::GetPuzzleZeroPosition(State);
	// get Target state Zero pos;
	ZeroTargetPos = PStools::GetPuzzleZeroPosition(CurNpuzzle->TargetState);
	ManhattanDistanceState = Heuristic::Manhattan(State.Values);
	ManhattanDistanceZero = abs(ZeroTargetPos.getX() - ZeroStartPos.getX()) + abs(ZeroTargetPos.getY() - ZeroStartPos.getY());
	MergedPuzzleValues = PStools::GetMergedValuesFromSnailState(State);	// straight 1D array values.
	// get number of inversion in puzzle for regular puzzle;
	unsigned int				swapNb = getInvCount(MergedPuzzleValues);

	// Display puzzle analysis informations.
	std::cout << KGRN "Puzzle Datas:" KRESET << std::endl;
	std::cout << "Puzzle width : " << CurNpuzzle->PuzzleSize << std::endl;
	std::cout << "StartState Manhattan distance : " << ManhattanDistanceState << std::endl;
	std::cout << "Zero Manhattan distance : " << ManhattanDistanceZero << std::endl;
	std::cout << "Inversion Nb : " << swapNb << std::endl;
	if (PStools::IsEven(ManhattanDistanceState + swapNb))
	{
		std::cout << KGRN "SOLVABLE" KRESET << " -> (Nb inversions + manhattan) = even." << std::endl;
		std::cout << "*** press Return to launch resolution of the puzzle ***" << std::endl;
		read(0, NULL, 1);
		return (true);
	}
	std::cout << KRED "UNSOLVABLE" KRESET << std::endl;
	// TODO: exit the program by returning false;
	std::cout << "*** press Return to launch resolution of the puzzle ***" << std::endl;
	read(0, NULL, 1);
	return (true); // <- here;
}

// A utility function to count inversions in given array 'arr[]'
int							Resolver::getInvCount(std::vector<int> arr)
{
    int inv_count = 0;
    int puzzleMaxSize = CurNpuzzle->PuzzleSize * CurNpuzzle->PuzzleSize;

    for (int i = 0; i < puzzleMaxSize - 1; i++)
        for (int j = i+1; j < puzzleMaxSize; j++)
             // Value 0 is used for empty space
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}

/*
**	Main A star function.
*/
void						Resolver::AStarTurn(PuzzleState &State)
{
	bool						IsResolved = false;
	PuzzleState 				&CurState = State;

	// Add first state to OpenedList;
	CurNpuzzle->OpenedList.push_back(CurState);
	while (!IsResolved && CurNpuzzle->OpenedList.size() != 0)
	{
		// ====> Turn Start 
		// Turn Status Display
		if (CurNpuzzle->DisplayTurns == true)
		{
			printf(KGRN "Turn %d\n" KRESET, CurNpuzzle->ResolverTurn);
			PStools::PrintPuzzleState(CurState);
			printf("State Cost : %d", CurState.Cost);
		}
		// End Turn Status display
		// ===> Check if end reached;
		if ((std::strcmp(CurNpuzzle->TargetState.ValuesString.c_str(), CurState.ValuesString.c_str())) == 0)
		{
			// Current state is result --> Resolved;
			EndFound(CurState);
			IsResolved = true;
			break;
		}
		// ====> Not end ===> engage new turn;
		CurNpuzzle->ResolverTurn += 1;
		CurNpuzzle->ClosedList.push_back(CurState); // Add previous state to closed list.
		PStools::RemoveStateFromVector(CurNpuzzle->OpenedList, CurState); // Remove previous state from opened list;
		// ====> Expand States =====>
		ExpandState(CurState); // expand and add to OpenedList directly;
		if (CurNpuzzle->DisplayTurns == true)
		{
			printf("Open list size = %lu\n", CurNpuzzle->OpenedList.size());
			printf("Closed list size = %lu\n", CurNpuzzle->ClosedList.size());
		}
		CurState = SelectOpenListState(State);
		//sleep(1);
	}
}

/*
**	Called when target state found;
*/
void						Resolver::EndFound(PuzzleState &State) // TODO: a finir, ne fonctionne pas.
{
	std::cout << std::endl << KYEL "Solution found!" KRESET << std::endl;
	/*
		◦ Total number of states ever selected in the "opened" set (complexity in time)
		◦ Maximum number of states ever represented in memory at the same time
		during the search (complexity in size)
		◦ Number of moves required to transition from the initial state to the final state,
		according to the search
		◦ The ordered sequence of states that make up the solution, according to the
		search
	*/
	std::cout << "Complexity in time: " << CurNpuzzle->ResolverTurn << std::endl;
	std::cout << "Complexity in size: " << CurNpuzzle->OpenedList.size() + CurNpuzzle->ClosedList.size() << std::endl;

	std::vector<PuzzleState>				PathFromStart;
	CurNpuzzle->NbOfMoves = 0;
	PuzzleState *tmp = &State;
	while (tmp)
	{
		CurNpuzzle->NbOfMoves += 1;
		PathFromStart.push_back(*tmp); // <-- !! It's reversed !!
		tmp = tmp->ParentState;
	}

	std::cout << "Nb of Moves required from Start to End: " << CurNpuzzle->NbOfMoves << std::endl << std::endl;
	std::cout << "*** press Return to see puzzle resolution ***" << std::endl;
	read(0, NULL, 1);

	int CurNbOfMoves = 0;
	for(std::vector<PuzzleState>::reverse_iterator it = PathFromStart.rbegin(); it != PathFromStart.rend(); ++it) // <-- !! It's reversed !!
	{
		std::cout << std::endl << KYEL "Move " << CurNbOfMoves << ":" KRESET << std::endl;
		PStools::PrintPuzzleState(*it);
		CurNbOfMoves += 1;
	}


	exit (0);
}

void							Resolver::ExpandState(PuzzleState &State)
{
	std::vector<PuzzleState>					RetStates;

	Point										zeroPos;
	Point										tmpPos;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int											y = 0;
	int											x = 0;
	PuzzleState									NewState;

	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (*col == 0)
			{
				zeroPos.setCoord(x, y);
				State.ZeroPos = zeroPos;
				// Up, right, down, left --> Clock wise rotation from zero;
				// UP Position
				if ((zeroPos.getY() - 1) >= 0) // UP pos free ?
				{
					// Get required values for swap
					tmpPos = zeroPos;
					tmpPos.setY(zeroPos.getY() - 1);

					// Create and set values of new state;
					CreateNewPuzzleState(State, tmpPos, zeroPos);
					RetStates.push_back(NewState);
				}

				// RIGHT Position (see UP pos for comments)
				if ((zeroPos.getX() + 1) < State.PuzzleSize)
				{
					tmpPos = zeroPos;
					tmpPos.setX(zeroPos.getX() + 1);
					CreateNewPuzzleState(State, tmpPos, zeroPos);
					//RetStates.push_back(NewState);
				}

				// DOWN Position (see UP pos for comments)
				if ((zeroPos.getY() + 1) < State.PuzzleSize)
				{
					tmpPos = zeroPos;
					tmpPos.setY(zeroPos.getY() + 1);

					//PuzzleState			NewState;
					CreateNewPuzzleState(State, tmpPos, zeroPos);
					//RetStates.push_back(NewState);
				}

				// LEFT Position (see UP pos for comments)
				if ((zeroPos.getX() - 1) >= 0)
				{
					tmpPos = zeroPos;
					tmpPos.setX(zeroPos.getX() - 1);

					//PuzzleState			NewState;
					CreateNewPuzzleState(State, tmpPos, zeroPos);
					//RetStates.push_back(NewState);
				}
				//return (RetStates); // zero found and expanded.
			}
		}
		x = 0;
	}

	//return (RetStates);
}

/*
**	Optimization fix : now Also Adds the new state to the open list;
*/
void			Resolver::CreateNewPuzzleState(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	PStools::SetValuesString(NewState);
 	if (!IsInList(CurNpuzzle->OpenedList, NewState) && !IsInList(CurNpuzzle->ClosedList, NewState))
	{
		// Set the values of the new State;
		NewState.ZeroPos = TmpPos;
		NewState.ParentState = new PuzzleState();
		*(NewState.ParentState) = State;

		// Cost Evaluation
		NewState.Cost = CurNpuzzle->CurHeuristic(NewState.Values);
		// Heuristic addition;
		NewState.Cost += Heuristic::CasesWronglyPlaced(NewState.Values);

		// Add the new state to the open list !
		CurNpuzzle->OpenedList.push_back(NewState);
	}
}


PuzzleState			&Resolver::SelectOpenListState(PuzzleState &PreviousState) // TODO: a transformer en priority queue
{

	PuzzleState &Ret = CurNpuzzle->OpenedList[0];
	for (int i = 0; i < (int)CurNpuzzle->OpenedList.size(); i++)
	{
		//std::cout << "searching cost = " << CurNpuzzle->OpenedList[i].Cost << std::endl;
		if (CurNpuzzle->OpenedList[i].Cost < PreviousState.Cost)
		{
			//std::cout << "found lesser cost" << std::endl;
			Ret = CurNpuzzle->OpenedList[i];
		}
	}
	//std::cout << "NOT lesser cost" << std::endl;
	return (Ret);
}


void				Resolver::AddStatesToOpenList(std::vector<PuzzleState> expandedStates)
{
	for (int i = 0; i < (int)expandedStates.size(); i++)
	{
		if (!IsInList(CurNpuzzle->OpenedList, expandedStates[i]) && !IsInList(CurNpuzzle->ClosedList, expandedStates[i]))
		{
			CurNpuzzle->OpenedList.push_back(expandedStates[i]);
		}
	}
}

bool						Resolver::IsInList(std::vector<PuzzleState> &List, PuzzleState &State)
{

	for (int i = 0; i < (int)List.size(); i++)
	{
		// pour chaque element de la liste;
		if ((std::strcmp(State.ValuesString.c_str(), List[i].ValuesString.c_str())) == 0)
		{
			return (true);
		}
	}
	return (false);
}









