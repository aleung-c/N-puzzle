/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitPuzzle.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:14:47 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 12:14:53 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Npuzzle.hpp"

/*
**	Initialize puzzle : open file or generate random board
**	from exec arguments. Static methods.
*/
class InitPuzzle
{
	public:
		static int				CheckArgs(t_NpuzzleData *Npuzzle, int argc, char **argv);
		static PuzzleState		CreatePuzzle(t_NpuzzleData *Npuzzle, int argc, char **argv);
		static int				GetPuzzleSizeFromStr(std::string line);
};
