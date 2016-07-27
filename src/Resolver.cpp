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
	std::vector<PuzzleState>	expandedStates;

	if (CurNpuzzle)
	{
		// Expand first state;
		CurNpuzzle->FirstState.Cost = CurNpuzzle->CurHeuristic(CurNpuzzle->FirstState.Values);

		std::cout << "First State Cost : " << CurNpuzzle->FirstState.Cost << "\n";

		expandedStates = ExpandState(CurNpuzzle->FirstState);


	}
}

std::vector<PuzzleState>	Resolver::ExpandState(PuzzleState State)
{

	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	
	std::vector<PuzzleState>					RetStates;

	Point										ZeroPos;
	Point										TmpPos;
	//int											TmpVal;

	int y = 0;
	int x = 0;

	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (*col == 0)
			{
				ZeroPos.setCoord(x, y);
				std::cout << *col << " found at " << ZeroPos.getX() << "x " << ZeroPos.getY() << "y\n";

				// Up, right, down, left --> Clock wise rotation from zero;
				
				if (ZeroPos.getY() - 1 >= 0) // up pos free ?
				{
					TmpPos =  ZeroPos;
					// Create new state, swap values.
					//std::cout << "new state created\n";

					// Declare new state;
					PuzzleState			NewState;
					NewState = State;
				}
			}
		}
		x = 0;
	}

	return (RetStates);
}




