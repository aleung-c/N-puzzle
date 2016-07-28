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

void							Resolver::Start()
{
	

	CurNpuzzle->NbOfMoves = 0;

	AStarTurn(CurNpuzzle->FirstState);

	
}

void						Resolver::AStarTurn(PuzzleState &State)
{
	std::vector<PuzzleState>	expandedStates;

	// Expand state;
	State.Cost = CurNpuzzle->CurHeuristic(CurNpuzzle->FirstState.Values);
	std::cout << "State Cost : " << CurNpuzzle->FirstState.Cost << "\n";
	expandedStates = ExpandState(CurNpuzzle->FirstState);

	// Debug printing for state expansion.
	for (int i = 0; i < (int)expandedStates.size(); i++)
	{
		std::cout << KGRN "new state created\n" KRESET;
		PStools::PrintPuzzleState(expandedStates[i]);
		/*if (!std::strcmp(CurNpuzzle->TargetState.ValuesString, expandedStates[i].ValuesString))
		{
			AStarTurn(expandedStates[i]);
		}
		else
		{

			std::cout << "End found" << std::endl;
			exit (0);
		}*/
	}


	

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
				std::cout << *col << " found at " << zeroPos.getX() << "x " << zeroPos.getY() << "y\n";
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
			}
		}
		x = 0;
	}

	return (RetStates);
}

PuzzleState		Resolver::CreateNewPuzzleState(PuzzleState &State, Point TmpPos, Point zeroPos)
{
	PuzzleState			NewState;

	NewState = State;
	PStools::SwapPuzzleValues(NewState, TmpPos, zeroPos);
	NewState.ZeroPos = TmpPos;
	NewState.ParentState = &State;
	return (NewState);
}



