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
	CurNpuzzle->CurTCostFromBeginning = 0;
	ApplyHeuristics(CurNpuzzle->FirstState);
	CurNpuzzle->FirstState.TCost = 0;
	// Solubilité test
	if (IsPuzzleSolvable(CurNpuzzle->FirstState) == false)
	{
		// ◦ The puzzle may be unsolvable, in which case you have to inform the user and exit
		std:: cout << "Puzzle not resolvable, exiting..." << std::endl;
		return ;
	}
	// Start puzzle resolution with Astar.
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

	// check if puzzle values are correct;
	if (InitPuzzle::ArePuzzleValuesCorrect(CurNpuzzle) == false)
	{
		std::cout << "Puzzle values incorrect" << std::endl;
		return (false);
	}

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

	MergedPuzzleValues.clear();
	// Display puzzle analysis informations.
	std::cout << KGRN "Puzzle first state datas:" KRESET << std::endl;
	//std::cout << "Puzzle width : " << CurNpuzzle->PuzzleSize << std::endl;
	std::cout << "Manhattan distance : " << ManhattanDistanceState << std::endl;
	if (CurNpuzzle->IsGreedySearchSelected)
	{
		std::cout << "Using Greedy search instead of A star" << std::endl;
	}
	else if (CurNpuzzle->IsDijkstraSearchSelected)
	{
		std::cout << "Using Dijkstra search instead of A star" << std::endl;
	}
	//std::cout << "Zero Manhattan distance : " << ManhattanDistanceZero << std::endl;
	std::cout << "Inversion Nb : " << swapNb << std::endl;
	if (PStools::IsEven(ManhattanDistanceState + swapNb))
	{
		std::cout << KGRN "SOLVABLE" KRESET << std::endl;
		std::cout << "*** press Return to launch resolution of the puzzle ***" << std::endl;
		read(0, NULL, 1);
		return (true);
	}
	std::cout << KRED "UNSOLVABLE" KRESET << std::endl;
	return (false); // <- here;
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
	//CurNpuzzle->OpenedList.push_back(CurState);
	CurNpuzzle->OpenedListQueue.push(CurState);
	CurNpuzzle->OpenedListStrings.push_back(CurState.ValuesString);
	while (!IsResolved && CurNpuzzle->OpenedListQueue.size() != 0)
	{
		// ====> Turn Start 
		// Turn Status Display
		if (CurNpuzzle->DisplayTurns == true)
		{
			printf(KGRN "Turn %d\n" KRESET, CurNpuzzle->ResolverTurn);
			PStools::PrintPuzzleState(CurState);
			printf("State HCost : %d\n", CurState.HCost);
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
		//PStools::RemoveStateFromVector(CurNpuzzle->OpenedList, CurState); // Remove previous state from opened list;
		RemoveStringFromVector(CurState.ValuesString);
		CurNpuzzle->OpenedListQueue.pop();
		// ====> Expand States =====>
		ExpandState(CurState); // expand and add to OpenedList directly;
		if (CurNpuzzle->DisplayTurns == true)
		{
			printf("Open list size = %lu\n", CurNpuzzle->OpenedListQueue.size());
			printf("Closed list size = %lu\n", CurNpuzzle->ClosedList.size());
			printf("Cur TCost from beginning = %d\n\n", CurNpuzzle->CurTCostFromBeginning);
		}
		//CurState = SelectOpenListState(State);
		CurState = CurNpuzzle->OpenedListQueue.top();
		CurNpuzzle->CurTCostFromBeginning = CurState.TCost;
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
	std::cout << "Complexity in size: " << CurNpuzzle->OpenedListQueue.size() + CurNpuzzle->ClosedList.size() << std::endl;

	std::vector<PuzzleState>				PathFromStart;
	CurNpuzzle->NbOfMoves = 0;
	PuzzleState *tmp = &State;
	while (tmp)
	{
		CurNpuzzle->NbOfMoves += 1;
		PathFromStart.push_back(*tmp); // <-- !! It's reversed !!
		tmp = tmp->ParentState;
	}
	CurNpuzzle->NbOfMoves -= 1;

	if (CurNpuzzle->IsGreedySearchSelected)
	{
		int CurNbOfMoves = 0;
		for(std::vector<PuzzleState>::reverse_iterator it = PathFromStart.rbegin();
		it != PathFromStart.rend();
		++it, CurNbOfMoves++) // <-- !! It's reversed !!
		{}
		std::cout << "Nb of Moves required from Start to End: " << CurNbOfMoves << std::endl << std::endl;
	}
	else
	{
		std::cout << "Nb of Moves required from Start to End: " << State.TCost << std::endl << std::endl;
	}

	std::cout << "*** press Return to see puzzle resolution ***" << std::endl;
	read(0, NULL, 1);

	int CurNbOfMoves = 0;
	for(std::vector<PuzzleState>::reverse_iterator it = PathFromStart.rbegin(); it != PathFromStart.rend(); ++it) // <-- !! It's reversed !!
	{
		std::cout << KYEL "Move " << CurNbOfMoves << ":" KRESET << std::endl;
		PStools::PrintPuzzleState(*it);
		CurNbOfMoves += 1;
	}
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
				// Up, right, down, left --> Clockwise rotation from zero;
				// UP Position
				if ((zeroPos.getY() - 1) >= 0) // UP pos free ?
				{
					// Get required values for swap
					tmpPos = zeroPos;
					tmpPos.setY(zeroPos.getY() - 1);
					// Create and set values of new state;
					CreateNewPuzzleState(State, tmpPos, zeroPos);
				}

				// RIGHT Position (see UP pos for comments)
				if ((zeroPos.getX() + 1) < State.PuzzleSize)
				{
					tmpPos = zeroPos;
					tmpPos.setX(zeroPos.getX() + 1);
					CreateNewPuzzleState(State, tmpPos, zeroPos);
				}

				// DOWN Position (see UP pos for comments)
				if ((zeroPos.getY() + 1) < State.PuzzleSize)
				{
					tmpPos = zeroPos;
					tmpPos.setY(zeroPos.getY() + 1);
					CreateNewPuzzleState(State, tmpPos, zeroPos);
				}

				// LEFT Position (see UP pos for comments)
				if ((zeroPos.getX() - 1) >= 0)
				{
					tmpPos = zeroPos;
					tmpPos.setX(zeroPos.getX() - 1);
					CreateNewPuzzleState(State, tmpPos, zeroPos);
				}
			}
		}
		x = 0;
	}
}

/*
**	Optimization fix : now Also Adds the new state to the open list;
*/
void			Resolver::CreateNewPuzzleState(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	if (CurNpuzzle->IsGreedySearchSelected == true)
	{
		GreedyNodeCreation(State, TmpPos, zeroPos);
	}
	else if (CurNpuzzle->IsDijkstraSearchSelected == true)
	{
		DijkstraNodeCreation(State, TmpPos, zeroPos);
	}
	else
	{
		AstarNodeCreation(State, TmpPos, zeroPos);
	}
}

void		Resolver::AstarNodeCreation(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	PStools::SetValuesString(NewState);
	// HCost Evaluation
	ApplyHeuristics(NewState);
	NewState.TCost = CurNpuzzle->CurTCostFromBeginning + 1;
	if (IsInList(CurNpuzzle->ClosedList, NewState))
	{
		PreviousState = GetStateInList(CurNpuzzle->ClosedList, NewState);
		if ((PreviousState.TCost + PreviousState.HCost) < (NewState.TCost + NewState.HCost))
		{
			// skip;
			return ;
		}
	}
	else if (IsStringInList(CurNpuzzle->OpenedListStrings, NewState.ValuesString))
	{
		PreviousState = GetStateInPQ(NewState);
		if ((PreviousState.TCost + PreviousState.HCost) < (NewState.TCost + NewState.HCost))
		{
			// skip;
			return ;
		}
	}
	// Set the values of the new State;
	NewState.ZeroPos = TmpPos;
	NewState.ParentState = new PuzzleState();
	*(NewState.ParentState) = State;

	// Add the new state to the open list !
	//CurNpuzzle->OpenedList.push_back(NewState);
	CurNpuzzle->OpenedListStrings.push_back(NewState.ValuesString);
	CurNpuzzle->OpenedListQueue.push(NewState);
}

void		Resolver::GreedyNodeCreation(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	PStools::SetValuesString(NewState);
	// HCost Evaluation
	ApplyHeuristics(NewState);
	//NewState.TCost = CurNpuzzle->CurTCostFromBeginning + 1;
	if (!IsStringInList(CurNpuzzle->OpenedListStrings, NewState.ValuesString) && !IsInList(CurNpuzzle->ClosedList, NewState))
	{
		// Set the values of the new State;
		NewState.ZeroPos = TmpPos;
		NewState.ParentState = new PuzzleState();
		*(NewState.ParentState) = State;

		// Add the new state to the open list !
		CurNpuzzle->OpenedListStrings.push_back(NewState.ValuesString);
		CurNpuzzle->OpenedListQueue.push(NewState);
	}
}

void		Resolver::DijkstraNodeCreation(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	PStools::SetValuesString(NewState);
	// ! No HCost Evaluation
	NewState.TCost = CurNpuzzle->CurTCostFromBeginning + 1;
	if (!IsStringInList(CurNpuzzle->OpenedListStrings, NewState.ValuesString) && !IsInList(CurNpuzzle->ClosedList, NewState))
	{
		// Set the values of the new State;
		NewState.ZeroPos = TmpPos;
		NewState.ParentState = new PuzzleState();
		*(NewState.ParentState) = State;

		// Add the new state to the open list !
		CurNpuzzle->OpenedListStrings.push_back(NewState.ValuesString);
		CurNpuzzle->OpenedListQueue.push(NewState);
	}
}

void			Resolver::ApplyHeuristics(PuzzleState &State)
{
	State.HCost = 0;
	if (CurNpuzzle->IsManhattanSelected)
	{
		State.HCost += Heuristic::Manhattan(State.Values);
	}
	if (CurNpuzzle->IsWronglyPlacedSelected)
	{
		State.HCost += Heuristic::CasesWronglyPlaced(State.Values);
	}
	if (CurNpuzzle->IsOutOfRowAndColSelected)
	{
		State.HCost += Heuristic::TilesOutOfRowandColumns(State.Values);
	}
}

bool						Resolver::IsInList(std::vector<PuzzleState> &List, PuzzleState &State)
{
	for (int i = 0; i < (int)List.size(); i++)
	{
		if ((std::strcmp(State.ValuesString.c_str(), List[i].ValuesString.c_str())) == 0)
		{
			return (true);
		}
	}
	return (false);
}

PuzzleState					Resolver::GetStateInList(std::vector<PuzzleState> &List, PuzzleState &State)
{
	for (int i = 0; i < (int)List.size(); i++)
	{
		if ((std::strcmp(State.ValuesString.c_str(), List[i].ValuesString.c_str())) == 0)
		{
			return (List[i]);
		}
	}
	return (State);
}

PuzzleState					Resolver::GetStateInPQ(PuzzleState &State)
{
	for (std::vector<PuzzleState>::iterator  it = CurNpuzzle->OpenedListQueue.begin();
			it != CurNpuzzle->OpenedListQueue.end();
			it++)
	{
		if ((std::strcmp(it->ValuesString.c_str(), State.ValuesString.c_str())) == 0)
		{
			return (*it);
		}
	}
	return (State);
}

bool						Resolver::IsStringInList(std::vector<std::string> &List, std::string str)
{
	for (int i = 0; i < (int)List.size(); i++)
	{
		if ((std::strcmp(str.c_str(), List[i].c_str())) == 0)
		{
			return (true);
		}
	}
	return (false);
}

void						Resolver::RemoveStringFromVector(std::string str)
{
	int Lsize = CurNpuzzle->OpenedListStrings.size();
	
	for (int i = 0; i < Lsize; i++)
	{
		if ((std::strcmp(str.c_str(), CurNpuzzle->OpenedListStrings[i].c_str())) == 0)
		{
			CurNpuzzle->OpenedListStrings.erase (CurNpuzzle->OpenedListStrings.begin() + i);
			return ;
		}
	}
	return ;
}
