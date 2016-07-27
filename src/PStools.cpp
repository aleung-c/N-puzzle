/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PStools.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:47:44 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/27 14:47:46 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Npuzzle.hpp"

int			PStools::GetStateValue(PuzzleState &State, Point coord)
{
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int											y = 0;
	int											x = 0;

	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (y == coord.getY() && x == coord.getX())
			{
				return (*col);
			}
		}
		x = 0;
	}
	return (-1); // not found, error;
}

void		PStools::ChangeStateValue(PuzzleState &State, Point coord, int newVal)
{
	std::vector< std::vector<int> >::iterator	row;
	std::vector<int>::iterator					col;
	int											y = 0;
	int											x = 0;

	for (row = State.Values.begin(); row != State.Values.end(); row++, y++) 
	{
		for (col = row->begin(); col != row->end(); col++, x++) 
		{
			if (y == coord.getY() && x == coord.getX())
			{
				*col = newVal;
				return ;
			}
		}
		x = 0;
	}
}

void		PStools::MakeDefault(PuzzleState &State)
{
	int y = 0;
	int x = 0;
	int val = 0;

	State.PuzzleSize = 3;
	while (y < State.PuzzleSize)
	{
		std::vector<int> tmp;
		while (x < State.PuzzleSize)
		{
			tmp.push_back(val);
			x++;
			val++;
		}
		State.Values.push_back(tmp);
		y++;
		x = 0;
	}
}


void		PStools::MakeTarget(PuzzleState &State, int puzzleSize)
{
	int y = 0;
	int x = 0;
	int val = 1;

	State.PuzzleSize = puzzleSize;
	while (y < State.PuzzleSize)
	{
		std::vector<int> tmp;
		while (x < State.PuzzleSize)
		{
			if (val == (State.PuzzleSize * State.PuzzleSize))
				val = 0;
			tmp.push_back(val);
			x++;
			val++;
		}
		State.Values.push_back(tmp);
		y++;
		x = 0;
	}
}

void		PStools::PrintPuzzleState(PuzzleState &State)
{
	int y = 0;
	int x = 0;

	//std::cout << "PuzzleSize = " << State.PuzzleSize << "\n";
	while (y < State.PuzzleSize)
	{
		while (x < State.PuzzleSize)
		{
			std::cout << (State.Values[y])[x] << " ";
			x++;
		}
		std::cout << "\n";
		y++;
		x = 0;
	}
	std::cout << "\n";
}

void		PStools::SetValuesString(PuzzleState &State)
{
	int y = 0;
	int x = 0;

	std::ostringstream st;

	while (y < State.PuzzleSize)
	{
		while (x < State.PuzzleSize)
		{
			st << State.Values[y][x];
			x++;
		}
		y++;
		x = 0;
	}
	State.ValuesString = st.str();
}

void	PStools::PrintValuesString(PuzzleState &State)
{
	std::cout << State.ValuesString << "\n";
}