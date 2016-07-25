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
		std::cout << "Npuzzle Start !\n";
		
		Npuzzle.FirstState = InitPuzzle::CreatePuzzle(&Npuzzle, argc, argv); // now working basically.

		std::cout << "Puzzle first state parsed: \n";
		Npuzzle.FirstState.PrintPuzzleState();

		std::cout << "Puzzle Target state created: \n";
		Npuzzle.TargetState.TargetState(Npuzzle.PuzzleSize); // modified.
		Npuzzle.TargetState.PrintPuzzleState();

		// ------ Starting PuzzleResolution;
		// ...
		
	}
	else
	{
		std::cout << "Usage: " << argv[0] << " [puzzle.txt]\n";
	}

	/***** ZONE RADIOACTIVE *****/
	printf("%d\n", Heuristic::CasesTrulyPlaced(Npuzzle.FirstState.Values)); 
	printf("%d\n", Heuristic::CasesWronglyPlaced(Npuzzle.FirstState.Values));
	printf("%d\n", Heuristic::Manhattan(Npuzzle.FirstState.Values));
	/***** FIN DE LA ZONE RADIOACTIVE *****/
	return (0);
}