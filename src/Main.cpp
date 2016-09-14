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


extern  t_NpuzzleData		Npuzzle;


int		main(int argc, char **argv)
{
	if (InitPuzzle::CheckArgs(&Npuzzle, argc, argv) == 0)
	{
		// ------ Setting program base;
		Npuzzle.FirstState = InitPuzzle::CreatePuzzle(&Npuzzle, argc, argv); // now working basically.
		PStools::SetValuesString(Npuzzle.FirstState);

		// TODO: Selecting Heuristic dynamically.
		Npuzzle.DisplayTurns = true;
		//Npuzzle.CurHeuristic = &Heuristic::Manhattan;
		// Npuzzle.CurHeuristic = &Heuristic::TilesOutOfRowandColumns;

		std::cout << KBLU "First state:" KRESET << std::endl;
		PStools::PrintPuzzleState(Npuzzle.FirstState);

		std::cout << KRED "Target state:" KRESET << std::endl;
		// Npuzzle.TargetState.TargetState(Npuzzle.PuzzleSize); // modified.
		PStools::MakeTarget(Npuzzle.TargetState, Npuzzle.PuzzleSize);
		PStools::PrintPuzzleState(Npuzzle.TargetState);

		// ------ Starting PuzzleResolution;
		Resolver		*Resolver = new Resolver::Resolver(&Npuzzle);
		Resolver->Start();
		// clean end;
		delete Resolver;
	}
	else
	{
		InitPuzzle::PrintUsage(argv[0]);
	}
	return (0);
}
