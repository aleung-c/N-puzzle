/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PuzzleState.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 17:45:08 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 17:45:10 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Npuzzle.hpp"

PuzzleState::PuzzleState() : ParentState(NULL)
{

}

PuzzleState::~PuzzleState()
{

}

void PuzzleState::MakeDefault()
{
	int y = 0;
	int x = 0;
	int val = 0;

	this->PuzzleSize = 4;
	while (y < this->PuzzleSize)
	{
		std::vector<int> tmp;
		while (x < this->PuzzleSize)
		{
			tmp.push_back(val);
			x++;
			val++;
		}
		this->Values.push_back(tmp);
		y++;
		x = 0;
	}
}


void PuzzleState::TargetState()
{
	int y = 0;
	int x = 0;
	int val = 1;

	this->PuzzleSize = 4;
	while (y < this->PuzzleSize)
	{
		std::vector<int> tmp;
		while (x < this->PuzzleSize)
		{
			if (val == (this->PuzzleSize * this->PuzzleSize))
				val = 0;
			tmp.push_back(val);
			x++;
			val++;
		}
		this->Values.push_back(tmp);
		y++;
		x = 0;
	}
}

void PuzzleState::PrintPuzzleState()
{
	int y = 0;
	int x = 0;

	while (y < PuzzleSize)
	{
		while (x < PuzzleSize)
		{
			std::cout << Values[y][x] << " ";
			x++;
		}
		std::cout << "\n";
		y++;
		x = 0;
	}
	std::cout << "\n";
}