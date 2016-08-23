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

	// solubilité test
	if (IsPuzzleSolvable(CurNpuzzle->FirstState) == false)
	{
		std:: cout << "Puzzle not resolvable, exiting." << std::endl;
		exit (0);
	}

	AStarTurn(CurNpuzzle->FirstState);
}

/*
**	Peut on resoudre ce puzzle ? 
*/

bool					Resolver::IsPuzzleSolvable(PuzzleState &State)
{
	Point 										ZeroStartPos;
	Point 										ZeroTargetPos;
	int 										ManhattanDistanceZero;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int											x;
	int											y;
	std::vector<int> 							MergedPuzzleValues;

	// =====> parite du zero //
	// get First state Zero pos;
	ZeroStartPos = PStools::GetPuzzleZeroPosition(State);
	// get Target state Zero pos;
	ZeroTargetPos = PStools::GetPuzzleZeroPosition(CurNpuzzle->TargetState);

	ManhattanDistanceZero = abs(ZeroTargetPos.getX() - ZeroStartPos.getX()) + abs(ZeroTargetPos.getY() - ZeroStartPos.getY());

	// =====> parite du puzzle

	x = 0;
	y = 0;
	// put the puzzle in straight 1 dimension vector
	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			MergedPuzzleValues.push_back(*col);
		}
	}

	std::vector <int>::iterator		val;
	// debug printing
	/*for (val = MergedPuzzleValues.begin(); val != MergedPuzzleValues.end(); val++)
	{
		std::cout << std::to_string(*val) << " ";
	}*/

	unsigned int				swapNb = 0;
	// sort this array to know if the needed inversions moves are even or odd;
	/*for (val = MergedPuzzleValues.begin(); val != MergedPuzzleValues.end(); val++)
	{
		if (val + 1 != MergedPuzzleValues.end() && *val > *(val + 1))
		{
			while (val + 1 != MergedPuzzleValues.end() && *val > *(val + 1))
			{
				std::iter_swap(val, val + 1);
				if (*val != 0)
					swapNb += 1;
				val = val + 1;
			}
			val = MergedPuzzleValues.begin();
		}
	}*/
		swapNb = getInvCount(MergedPuzzleValues);
	// Formula for sovability for non snail tile game ...
	//( (grid width odd) && (#inversions even) )  ||  ( (grid width even) && ((blank on odd row from bottom) == (#inversions even)) )
	if (
		PStools::IsOdd(CurNpuzzle->PuzzleSize)
		&& PStools::IsEven(swapNb)
		)
	{
		// odd grid width. even number of inversion ==> solvable;
		std::cout << "solvable -> grid width odd, inversions even." << std::endl;

		std::cout << "Pwidth : " << CurNpuzzle->PuzzleSize << std::endl;
		std::cout << "Inversion Nb : " << swapNb << std::endl;
		std::cout << "Zero Y pos : " << ZeroStartPos.getY() << std::endl;
		read(0, NULL, 1);
		return (true);
	}

	//if (PStools::IsEven(CurNpuzzle->PuzzleSize) && PStools::IsEven(CurNpuzzle->PuzzleSize - (ZeroStartPos.getY())) && PStools::IsOdd(swapNb))
	if (
		PStools::IsEven(CurNpuzzle->PuzzleSize) 
		&& PStools::IsEven(abs(ZeroStartPos.getX() - ZeroStartPos.getX()) + abs(ZeroStartPos.getY() - ZeroStartPos.getY())) 
		&& PStools::IsOdd(swapNb)
		)
	{
		std::cout << "solvable -> grid width even, blank on even row from the bottom, inversion odd" << std::endl;

		std::cout << "Pwidth : " << CurNpuzzle->PuzzleSize << std::endl;
		std::cout << "Inversion Nb : " << swapNb << std::endl;
		std::cout << "Zero Y pos from bot : " << (CurNpuzzle->PuzzleSize - ZeroStartPos.getY()) << std::endl;
		read(0, NULL, 1);
		return (true);
	}

	//if (PStools::IsEven(CurNpuzzle->PuzzleSize) && PStools::IsOdd(CurNpuzzle->PuzzleSize - (ZeroStartPos.getY())) && PStools::IsEven(swapNb))
	if (
		PStools::IsEven(CurNpuzzle->PuzzleSize)
		&& PStools::IsOdd(abs(ZeroStartPos.getX() - ZeroStartPos.getX()) + abs(ZeroStartPos.getY() - ZeroStartPos.getY()))
		&& PStools::IsEven(swapNb)
		)
	{
		std::cout << "solvable -> grid width even, blank on odd row from the bottom, inversion even" << std::endl;

		std::cout << "Pwidth : " << CurNpuzzle->PuzzleSize << std::endl;
		std::cout << "Inversion Nb : " << swapNb << std::endl;
		std::cout << "Zero Y pos from bot : " << (CurNpuzzle->PuzzleSize - ZeroStartPos.getY()) << std::endl;
		read(0, NULL, 1);
		return (true);
	}

	std::cout << "Unsolvable" << std::endl;

	std::cout << "Pwidth : " << CurNpuzzle->PuzzleSize << std::endl;
	std::cout << "Inversion Nb : " << swapNb << std::endl;
	std::cout << "Zero Y pos from bot : " << (CurNpuzzle->PuzzleSize - ZeroStartPos.getY()) << std::endl;

	std::cout << "*** press ctrl + D to launch resolution of the puzzle ***" << std::endl;

	read(0, NULL, 1);
	return (true);
}

// A utility function to count inversions in given array 'arr[]'
int							Resolver::getInvCount(std::vector<int> arr)
{
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i+1; j < 9; j++)
             // Value 0 is used for empty space
             if (arr[j] && arr[i] &&  arr[i] > arr[j])
                  inv_count++;
    return inv_count;
}


void						Resolver::AStarTurn(PuzzleState &State)
{
	std::vector<PuzzleState>	expandedStates;
	bool						IsResolved = false;
	PuzzleState 				&CurState = State;

	//CurState = State;
	CurNpuzzle->OpenedList.push_back(CurState);
	while (!IsResolved && CurNpuzzle->OpenedList.size() != 0)
	{
		// ====> Turn Start 

		// Turn Status Display
		if (CurNpuzzle->DisplayTurns == true)
		{
			std::cout << KGRN "Turn " << CurNpuzzle->NbOfMoves << ":" KRESET << std::endl;
			PStools::PrintPuzzleState(CurState);
			std::cout << "State Cost : " << CurState.Cost << "\n";
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
		CurNpuzzle->NbOfMoves += 1;
		// Add previous state to closed list.
		CurNpuzzle->ClosedList.push_back(CurState);
		// Remove previous state from opened list;
		//if (CurNpuzzle->NbOfMoves >= 1)
		PStools::RemoveStateFromVector(CurNpuzzle->OpenedList, CurState);
		
		// ====> Expand States =====>
		expandedStates = ExpandState(CurState);
		// For each expanded state;
		AddStatesToOpenList(expandedStates);

		if (CurNpuzzle->DisplayTurns == true)
		{
			std::cout << "Open list size = " << CurNpuzzle->OpenedList.size() << "\n";
			std::cout << "Closed list size = " << CurNpuzzle->ClosedList.size() << "\n" << std::endl;
		}
		CurState = SelectOpenListState(State);
		//sleep(1);
		//if (CurNpuzzle->OpenedList.size() != 0)
			//AStarTurn(SelectOpenListState(State));

	}
}


void						Resolver::EndFound(PuzzleState &State)
{
	std::cout << "End found" << std::endl;
	PStools::PrintPuzzleState(State);
	exit (0);
}

std::vector<PuzzleState>	Resolver::ExpandState(PuzzleState &State)
{
	std::vector<PuzzleState>					RetStates;

	Point										zeroPos;
	Point										TmpPos;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int											y = 0;
	int											x = 0;

	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (*col == 0)
			{
				zeroPos.setCoord(x, y);
				//std::cout << *col << " found at " << zeroPos.getX() << "x " << zeroPos.getY() << "y\n";
				State.ZeroPos = zeroPos;
				// Up, right, down, left --> Clock wise rotation from zero;
				// UP Position
				if ((zeroPos.getY() - 1) >= 0) // UP pos free ?
				{
					// Get required values for swap
					TmpPos = zeroPos;
					TmpPos.setY(zeroPos.getY() - 1);

					// Create and set values of new state;
					PuzzleState			NewState;
					NewState = CreateNewPuzzleState(State, TmpPos, zeroPos);
					RetStates.push_back(NewState);
				}

				// RIGHT Position (see UP pos for comments)
				if ((zeroPos.getX() + 1) < State.PuzzleSize)
				{
					TmpPos = zeroPos;
					TmpPos.setX(zeroPos.getX() + 1);

					PuzzleState			NewState;
					NewState = CreateNewPuzzleState(State, TmpPos, zeroPos);
					RetStates.push_back(NewState);
				}

				// DOWN Position (see UP pos for comments)
				if ((zeroPos.getY() + 1) < State.PuzzleSize)
				{
					TmpPos = zeroPos;
					TmpPos.setY(zeroPos.getY() + 1);

					PuzzleState			NewState;
					NewState = CreateNewPuzzleState(State, TmpPos, zeroPos);
					RetStates.push_back(NewState);
				}

				// LEFT Position (see UP pos for comments)
				if ((zeroPos.getX() - 1) >= 0)
				{
					TmpPos = zeroPos;
					TmpPos.setX(zeroPos.getX() - 1);

					PuzzleState			NewState;
					NewState = CreateNewPuzzleState(State, TmpPos, zeroPos);
					RetStates.push_back(NewState);
				}
				return (RetStates); // zero found and expanded.
			}
		}
		x = 0;
	}

	return (RetStates);
}

PuzzleState			Resolver::CreateNewPuzzleState(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	PuzzleState			NewState;

	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	NewState.ZeroPos = TmpPos;
	NewState.ParentState = &State;
	PStools::SetValuesString(NewState);
	NewState.Cost = CurNpuzzle->CurHeuristic(NewState.Values);
	return (NewState);
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









