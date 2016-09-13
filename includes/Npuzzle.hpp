/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Npuzzle.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:09:30 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 12:09:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <regex>
# include <random>
# include <algorithm>
# include <math.h>

// color in text;
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\x1B[0m"

class		Heuristic;
class		Point;
class		PuzzleState;
class		InitPuzzle;
class		Resolver;
class		PStools;

// Placed first for include compilation order;
#include "Point.hpp"
#include "PuzzleState.hpp"

/*
**	Main structure containing puzzle datas.
*/
typedef struct 					s_NpuzzleData
{
	// Start settings
	int							PuzzleSize;

	bool						DisplayTurns;

	// selected heuristics.
	bool						IsManhattanSelected;
	bool						IsWronglyPlacedSelected;
	bool						IsTrulyPlacedSelected;
	bool						IsOutOfRowAndColSelected;

	// Pointer to selected heuristic fonction;
	int							(*CurHeuristic)(std::vector< std::vector <int> > Values);

	// Initials values to be modified at runtime;
	PuzzleState					FirstState;
	PuzzleState					TargetState;

	std::vector<PuzzleState>	OpenedList;
	std::vector<PuzzleState>	ClosedList;

	// Running Datas
	int 						ResolverTurn; // ==> complexity in time;
	int 						NbOfMoves; // nb of games moves till solution found.

}								t_NpuzzleData;

#include "Heuristic.hpp"
#include "InitPuzzle.hpp"
#include "Resolver.hpp"
#include "PStools.hpp"



#endif
