/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 18:34:07 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 14:17:13 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_msh {
	char		**env;
	int			envspc;
	int			envused;
	t_hashtable	*loc_var;
	t_cmd		*commands;
	int			last_status;
}	t_msh;

void	print_error(char *command, char *argument, char *message);

#endif