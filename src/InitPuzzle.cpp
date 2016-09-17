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
	if (argc > 4) // more than 4 arg.
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

	// Usage: ./Npuzzle [-mlt] [-g 3-n | file ...]
	// check position1
	if (argc > 2 && std::regex_match (argv[1], std::regex("^(-[b|j|m|o|w|d]+)$")))// -mlt in pos 1 
	{
		// parse and set mlt;
		std::string args = argv[1];
		if (args.find('b') != std::string::npos)
		{
			Npuzzle->IsGreedySearchSelected = true;
		}
		if (args.find('j') != std::string::npos)
		{
			Npuzzle->IsDijkstraSearchSelected = true;
		}
		if (Npuzzle->IsDijkstraSearchSelected && Npuzzle->IsGreedySearchSelected)
		{
			std::cout << "Use only one of b or j" << std::endl;
			exit(-1);
		}

		if (args.find('m') != std::string::npos)
		{
			Npuzzle->IsManhattanSelected = true;
		}
		if (args.find('o') != std::string::npos)
		{
			Npuzzle->IsOutOfRowAndColSelected = true;
		}
		if (args.find('w') != std::string::npos)
		{
			Npuzzle->IsWronglyPlacedSelected = true;
		}
		if (args.find('d') != std::string::npos)
		{
			Npuzzle->DisplayTurns = true;
		}

		if (argc == 3 && argv[2][0] != '-') // file in pos 3;
		{
			// Parse File and get puzzle;
			// Exception setting.
			std::ios_base::iostate exceptionMask = fs.exceptions() | std::ios::failbit;
			fs.exceptions(exceptionMask);
			try
			{
				fs.open(argv[2]);
				ReturnedFirstState = FillPuzzleWithFile(fs, Npuzzle);
				fs.close();
			}
			catch (std::ios_base::failure& e)
			{
				std::cout << argv[2] << ": No such file or directory\n";
				exit(-1);
			}
		}
		else if (argc == 4
			&& std::regex_match (argv[2], std::regex("^(-g)$"))
			&& std::regex_match (argv[3], std::regex("^(\\d+)$"))) // -g and a number in pos 3 and 4;
		{
			// generate puzzle;
			// only -g and a number. generate puzzle from size given in arg.
			if (std::atoi(argv[3]) < 3)
			{
				std::cout << "Size of puzzle must be greater or equal to 3" << std::endl;
				exit (-1);
			}
			else if (std::atoi(argv[3]) > 2000)
			{
				std::cout << "Size of puzzle too big" << std::endl;
				exit (-1);
			}
			Npuzzle->PuzzleSize = std::atoi(argv[3]);
			ReturnedFirstState = GenerateRandomizedPuzzle(std::atoi(argv[3]));
		}
		else 
		{
			PrintUsage(argv[0]);
			exit(-1);
		}
	}
	else if (argc == 2 && std::regex_match (argv[1], std::regex("^(-h)$")))
	{
		// print help
		PrintHelp();
		exit(-1);
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
		if (!isSizeFound && std::regex_match(line, std::regex("^\\s*(\\d+)\\s*(\\#.*)*$")))
		{

			// get puzzle size in int;
			puzzleSize = std::strtol(line.c_str(), NULL, 10);
			if (puzzleSize < 3)
			{
				std::cout << "Puzzle size must be at least 3" << std::endl;
				exit (-1);
			}
			// set global and first state values;
			Npuzzle->PuzzleSize = puzzleSize;
			ReturnedFirstState.PuzzleSize = puzzleSize;

			// std::cout << "Found size. Size = " << puzzleSize << "\n";
			isSizeFound = true;

			// second regex is set from found size;
			regex_2 = "^(\\s*(\\d+)\\s*){" + std::to_string(puzzleSize) + "}\\s*(\\#.*)*$";
		}
		// Pass 2 : get puzzle values.
		else if (isSizeFound && std::regex_match(line, std::regex(regex_2)))
		{
			int						i = 0;
			std::vector<int>		tmp;

			str = (char *)line.c_str();
			while (i < puzzleSize)
			{
				curVal = std::strtol(str, &(str), 10); // &(str) -> tete de lecture.
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

/*
**	Check if values in the puzzle are correct;
*/
bool			InitPuzzle::ArePuzzleValuesCorrect(t_NpuzzleData *Npuzzle)
{
	std::string		PuzzleSortedString = Npuzzle->FirstState.ValuesString;
	std::string		TargetSortedString = Npuzzle->TargetState.ValuesString;

	// sort both puzzle strings.
	std::sort(PuzzleSortedString.begin(), PuzzleSortedString.end());		
	std::sort(TargetSortedString.begin(), TargetSortedString.end());
	if (PuzzleSortedString.compare(TargetSortedString) == 0)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

void			InitPuzzle::PrintUsage(std::string arg)
{
	// Usage: ./Npuzzle [-mlt | -h] [-g 3-n | file ...]
	std::cout << "Usage: " << arg << " [-bjmlwd | -h] [-g 3-n | file ...]\n";
}

void				InitPuzzle::PrintHelp()
{
	std::cout << KGRN "Npuzzle Help : " KRESET << std::endl << std::endl

	<< "Usage: " << "./Npuzzle [-bjmlwd | -h] [-g 3-n | file ...]\n" << std::endl << std::endl

	<< "-b : use Greedy search in stead of regular a star" << std::endl
	<< "-j : use Dijkstra search in stead of regular a star" << std::endl << std::endl
	<< "-m : use manhattan heuristic" << std::endl
	<< "-o : use out of row and column heuristic" << std::endl
	<< "-w : use case wrongly placed heuristic" << std::endl
	<< "-d : display each A star turn" << std::endl
	<< "-h : bring help feature when no other argument is given" << std::endl
	<< "! You can use more than one heuristic !" << std::endl << std::endl
	<< " -g : When no file is selected, generate a random puzzle of following size" << std::endl;
}
