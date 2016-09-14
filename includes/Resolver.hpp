/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resolver.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 18:47:53 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/26 18:47:56 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.hpp"

/*
** Resolve the puzzle. A star implementation.
*/
class Resolver
{
	public:
										Resolver();
										Resolver(t_NpuzzleData *nPuzzle);
										~Resolver();

		t_NpuzzleData					*CurNpuzzle;

		void							Start();

		bool							IsPuzzleSolvable(PuzzleState &State);

		int								getInvCount(std::vector<int> arr);

		void							AStarTurn(PuzzleState &State);
	
		void							ExpandState(PuzzleState &State);
		void							CreateNewPuzzleState(PuzzleState &State, Point TmpPos, Point zeroPos);
		void							ApplyHeuristics(PuzzleState &State);

		void							AddStatesToOpenList(std::vector<PuzzleState> expandedStates);
		bool							IsInList(std::vector<PuzzleState> &List, PuzzleState &State);

		PuzzleState						&SelectOpenListState(PuzzleState &State);

		void							EndFound(PuzzleState &State);

	private:
		PuzzleState						NewState; // tmp use;

};