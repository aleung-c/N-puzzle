/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PStools.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/27 14:46:48 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/27 14:46:49 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.hpp"

/*
**	Every operation applicable on PuzzleState. Toolbox for the algorythm;
*/
class PStools
{
	public:
		static int			GetStateValue(PuzzleState &State, Point coord);
		static void			ChangeStateValue(PuzzleState &State, Point coord,
												int newVal);
		static void			PrintPuzzleState(PuzzleState &State);
		static void			MakeDefault(PuzzleState &State);
		static void			MakeTarget(PuzzleState &State, int puzzleSize);
		static void			SetValuesString(PuzzleState &State);
		static void			PrintValuesString(PuzzleState &State);
};