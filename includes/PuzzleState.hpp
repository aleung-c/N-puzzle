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
		std::vector< std::vector <int> >	Values;

		PuzzleState();
		~PuzzleState();

		void PrintPuzzleState();
		void MakeDefault();
};