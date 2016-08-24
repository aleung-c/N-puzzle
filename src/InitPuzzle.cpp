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

int				InitPuzzle::CheckArgs(t_NpuzzleData *Npuzzle, int argc, char **argv)
{
	if (Npuzzle && argv)
	{}
	if (argc == 1)
	{
		return (-1);
	}
	if (argc > 3) // more than three arg.
	{
		return (-1);
	}
	return (0);
}

/*
**	Basic parsing function. Also sets Main struct puzzle size.
*/
PuzzleState		InitPuzzle::CreatePuzzle(t_NpuzzleData *Npuzzle, int argc, char **argv)
{
	PuzzleState				ReturnedFirstState;
	std::ifstream			fs;

	if (argc > 1 && argv[1] && argv[1][0] != '-')
	{
		// One Argument --> Parse and get puzzle;
		// Exception setting.
		std::ios_base::iostate exceptionMask = fs.exceptions() | std::ios::failbit;
		fs.exceptions(exceptionMask);
		try
		{
			fs.open(argv[1]);
			ReturnedFirstState = FillPuzzleWithFile(fs, Npuzzle);
			fs.close();
		}
		catch (std::ios_base::failure& e)
		{
			std::cout << argv[1] << ": No such file or directory\n";
			exit(-1);
		}
	}
	else if (argc == 3 && argv[1] && std::regex_match (argv[1], std::regex("^(-g)$"))
		&& argv[2] && std::regex_match (argv[2], std::regex("^(\\d+)$")))
	{
		// only -g and a number. generate puzzle from size given in arg.
		Npuzzle->PuzzleSize = std::atoi(argv[2]);
		ReturnedFirstState = GenerateRandomizedPuzzle(std::atoi(argv[2]));
	}
	else
	{
		PrintUsage(argv[0]);
		exit(-1);
	}
	ReturnedFirstState.ParentState = NULL;
	return (ReturnedFirstState);
}

PuzzleState		InitPuzzle::FillPuzzleWithFile(std::ifstream &fs, t_NpuzzleData *Npuzzle)
{
	std::string				line;
	bool					isSizeFound = false;
	int						puzzleSize;
	std::string				regex_2;
	int						curVal;
	char					*str;
	PuzzleState				ReturnedFirstState;
	
	// read file line by line;
	while (std::getline(fs, line))
	{
		// std::cout << line << "\n"; // display content of file;
		// Pass 1 : search puzzle size;
		if (!isSizeFound && std::regex_match (line, std::regex("^\\s*(\\d+)\\s*(\\#.*)*$")))
		{
			// get puzzle size in int;
			puzzleSize = std::strtol(line.c_str(), NULL, 10);
			
			// set global and first state values;
			Npuzzle->PuzzleSize = puzzleSize;
			ReturnedFirstState.PuzzleSize = puzzleSize;

			// std::cout << "Found size. Size = " << puzzleSize << "\n";
			isSizeFound = true;

			// second regex is set from found size;
			regex_2 = "^(\\s*(\\d+)\\s*){" + std::to_string(puzzleSize) + "}\\s*(\\#.*)*$";
		}
		// Pass 2 : get puzzle values.
		else if (isSizeFound && std::regex_match (line, std::regex(regex_2)))
		{
			int						i = 0;
			std::vector<int>		tmp;

			str = (char *)line.c_str();
			while (i < puzzleSize)
			{
				curVal = std::strtol(str, &(str), 10); // &(str) -> tete de lecture.
				// std:: cout << "val = " << curVal << "\n";
				tmp.push_back(curVal);
				i++;
			}
			if ((int)tmp.size() != puzzleSize)
			{
				std::cout << "Incorrect puzzle format (incorrect nb of columns in line)";
				exit(-1);
			}
			ReturnedFirstState.Values.push_back(tmp);
			i = 0;
		}
	}

	// OnEndParseLines
	if (!isSizeFound)
	{
		std::cout << "No size found in file. Incorrect file format.";
		exit(-1);
	}
	if ((int)ReturnedFirstState.Values.size() != puzzleSize)
	{
		std::cout << "Incorrect puzzle format (incorrect nb of lines)";
		exit(-1);
	}
	return (ReturnedFirstState);
}

PuzzleState		InitPuzzle::GenerateRandomizedPuzzle(int puzzleSize)
{
	PuzzleState				ReturnedState;
	int						x = 0;
	int						y = 0;
	std::random_device		rd;
	int						random_x;
	int						random_y;
	int						tmp;

	PStools::MakeTarget(ReturnedState, puzzleSize); // put the state in finished state before randomizing it;
	std::mt19937 rng(rd()); // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, puzzleSize - 1); // guaranteed unbiased
	while (y < puzzleSize)
	{
		while (x < puzzleSize)
		{
			// random position generating for swap;
			random_x = uni(rng);
			random_y = uni(rng);

			// value swap;
			tmp = (ReturnedState.Values[y])[x];
			(ReturnedState.Values[y])[x] = (ReturnedState.Values[random_y])[random_x];
			(ReturnedState.Values[random_y])[random_x] = tmp;
			x++;
		}
		y++;
		x = 0;
	}
	return (ReturnedState);
}

void			InitPuzzle::PrintUsage(std::string arg)
{
	std::cout << "Usage: " << arg << " [puzzle.txt] | -g [PuzzleSize]\n";
}

