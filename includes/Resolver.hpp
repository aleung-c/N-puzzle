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
	
		std::vector<PuzzleState>		ExpandState(PuzzleState State);

};