/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ask_to_close_quotes.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:50:26 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/03/22 17:15:35 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>

int	main()
{
	char	*line;
	int		squotes;
	int		dquotes;

	line = readline("please input a command");
	squotes = 0;
	dquotes = 0;
	while (*line)
	{
		if (*line == 34)
		{
			if (dquotes == 1)
				dquotes = 0;
			else
				dquotes = 1;
		}
		if (*line == 39)
		{
			if (squotes == 1)
				squotes = 0;
			else
				squotes = 1;
		}
		++line;
	}
	if (squotes == 1)
		line = readline("quotes >");
	if (dquotes == 1)
		line = readline("dquotes >");
	return (0);
}
