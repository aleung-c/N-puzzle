/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PuzzleState.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 17:32:32 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 17:32:35 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.hpp"

/*
**	Represent ONE state of the taquin board.
*/
class PuzzleState
{
	public:
		int									PuzzleSize;
		
		// Main values of the state with indexed positions;
		std::vector< std::vector <int> >	Values;

		// Values of the state as string for quick comparison;
		std::string							ValuesString;
		
		// Precedent node in the A* implementation;
		PuzzleState 						*ParentState;

		// Zero position to avoid useless loops;
		Point								ZeroPos;

		// cost set by selected Heuristic;
		int									HCost;
		int									TCost;

							PuzzleState();
							~PuzzleState();

		// Allow State duplication;
		PuzzleState			&operator=(const PuzzleState& other);	

};

struct LessThanByHeuristic
{
  bool operator()(const PuzzleState& lhs, const PuzzleState& rhs) const
  {
    return lhs.HCost > rhs.HCost;
  }
};