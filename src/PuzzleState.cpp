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

PuzzleState			&PuzzleState::operator=(const PuzzleState& other)
{
	PuzzleSize = other.PuzzleSize;
	Values = other.Values;
	ValuesString = other.ValuesString;
	ParentState = other.ParentState;
	Cost = other.Cost;
	return (*this);
}


