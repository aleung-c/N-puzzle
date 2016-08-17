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
	int 										ManhattanDistanceState;
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int x = 0;
	int y = 0;

	// =====> parite du zero //
	// get First state Zero pos;
	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (*col == 0)
			{
				ZeroStartPos.setX(x);
				ZeroStartPos.setY(y);
				break;
			}
		}
	}

	x = 0;
	y = 0;
	// get Target state Zero pos;
	for (row = CurNpuzzle->TargetState.Values.begin(); row != CurNpuzzle->TargetState.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (*col == 0)
			{
				ZeroTargetPos.setX(x);
				ZeroTargetPos.setY(y);
				break;
			}
		}
	}
	ManhattanDistanceState = Heuristic::Manhattan(State.Values);
	ManhattanDistanceZero = std::sqrt((ZeroTargetPos.getX() - ZeroStartPos.getX()) * (ZeroTargetPos.getX() - ZeroStartPos.getX())
									+ (ZeroTargetPos.getY() - ZeroStartPos.getY()) * (ZeroTargetPos.getY() - ZeroStartPos.getY()));


	// =====> parite du puzzle // TODO : new technique a tester.
	std::vector <int> 		MergedPuzzleValues;

	x = 0;
	y = 0;
	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			MergedPuzzleValues.push_back(*col);
		}
	}

	std::vector <int>::iterator		val;
	for (val = MergedPuzzleValues.begin(); val != MergedPuzzleValues.end(); val++)
	{
		std::cout << std::to_string(*val) << " ";
	}

	int swapNb = 0;
	// sort this array to know if the needed swap moves are even or odd;
	for (val = MergedPuzzleValues.begin(); val != MergedPuzzleValues.end(); val++)
	{
		if (*val > *(val + 1))
		{
			std::iter_swap(val, val + 1);
			val = MergedPuzzleValues.begin();
			swapNb += 1;
		}

	}

	ManhattanDistanceState = swapNb + 1;
	if ((ManhattanDistanceState % 2 != 0 && ManhattanDistanceZero % 2 != 0) || (ManhattanDistanceState % 2 == 0 && ManhattanDistanceZero % 2 == 0))
	{
		std::cout << "Solubilité test = parite identique | state = " << ManhattanDistanceState << " ; Zero = " << ManhattanDistanceZero << std::endl;
		sleep(6);
		return (true);
	}
	std::cout << "Solubilité test = parite NON identique | state = " << ManhattanDistanceState << " ; Zero = " << ManhattanDistanceZero << std::endl;
	sleep(1);
	return (true);
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
		std::cout << KGRN "Turn " << CurNpuzzle->NbOfMoves << ":" KRESET << std::endl;
		PStools::PrintPuzzleState(CurState);
		std::cout << "State Cost : " << CurState.Cost << "\n";
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


		std::cout << "Open list size = " << CurNpuzzle->OpenedList.size() << "\n";
		std::cout << "Closed list size = " << CurNpuzzle->ClosedList.size() << "\n" << std::endl;

		CurState = SelectOpenListState(State);
		//sleep(1);
		//if (CurNpuzzle->OpenedList.size() != 0)
			//AStarTurn(SelectOpenListState(State));

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









