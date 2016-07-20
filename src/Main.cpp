/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:08:04 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 12:08:08 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Npuzzle.hpp"

int		main(int argc, char **argv)
{
	t_NpuzzleData		Npuzzle;

	if (InitPuzzle::CheckArgs(&Npuzzle, argc, argv) == 0)
	{
		// ------ Setting program base;
		std::cout << "Npuzzle Start !\n";
		//NpuzzleGlobal.FirstState = InitPuzzle::CreatePuzzle(&Npuzzle, argc, argv);

		Npuzzle.FirstState.MakeDefault();
		Npuzzle.FirstState.PrintPuzzleState();

		// ------ Starting PuzzleResolution;
		// ...
		
	}
	else
	{
		std::cout << "Usage: " << argv[0] << " [puzzle.txt]\n";
	}
	return (0);
}