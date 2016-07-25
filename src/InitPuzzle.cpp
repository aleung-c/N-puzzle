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
	if (Npuzzle)
	{}
	if (argc > 2 || (argc == 2 && !argv[1][0])) // more than one arg.
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
	std::ifstream			fs;
	std::string				line;
	bool					isSizeFound = false;
	int						puzzleSize;
	std::string				regex_2;
	int						curVal;
	char					*str;

	PuzzleState				ReturnedFirstState;

	if (argc > 1 && argv[1])
	{
		// One Argument --> Parse and get puzzle;
		// Exception setting.
		std::ios_base::iostate exceptionMask = fs.exceptions() | std::ios::failbit;
		fs.exceptions(exceptionMask);
		try
		{
			fs.open(argv[1]);
			
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
						curVal = std::strtol(str, &(str), 10);
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
		}
		catch (std::ios_base::failure& e)
		{
			std::cout << argv[1] << ": No such file or directory\n";
			exit(-1);
		}
	}
	else if (argv[1] && std::regex_match (line, std::regex("^(\\d+)$")))
	{
		// TODO: only a number. generate puzzle from size given in arg.
	}
	else if (argc == 1)
	{
		// TODO: no arg. generate random puzzle;
	}
	return (ReturnedFirstState);
}

int				InitPuzzle::GetPuzzleSizeFromStr(std::string line)
{
	if (line[0])
	{}
	return (0);
}

