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
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <regex>
#include <random>

class		Heuristic;
class		PuzzleState;
class		InitPuzzle;
class		Point;
class		Resolver;

#include "PuzzleState.hpp"



/*
**	Main structure containing puzzle datas.
*/
typedef struct 					s_NpuzzleData
{
	int PuzzleSize;

	PuzzleState					FirstState;
	PuzzleState					TargetState;

	std::vector<PuzzleState>	OpenedList;
	std::vector<PuzzleState>	ClosedList;
}								t_NpuzzleData;

#include "Heuristic.hpp"
#include "InitPuzzle.hpp"
#include "Point.hpp"
#include "Resolver.hpp"


#endif
