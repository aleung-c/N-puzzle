/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitPuzzle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 12:14:41 by aleung-c          #+#    #+#             */
/*   Updated: 2016/07/19 12:14:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Npuzzle.hpp"

int				InitPuzzle::CheckArgs(int argc, char **argv)
{
	if (argc > 2 || (argc == 2 && !argv[1][0]))
	{
		return (-1);
	}
	return (0);
}

PuzzleState		InitPuzzle::CreatePuzzle(int argc, char **argv)
{
	if (argc != 0 && argv[0])
	{
		std::cout << "start CreatePuzzle\n";
	}
	return (*(new PuzzleState()));
}

