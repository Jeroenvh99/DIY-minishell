/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 18:34:07 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/09 16:07:41 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_msh
{
	char		**env;
	int			envspc;
	int			envused;
	t_hashtable	*loc_var;
	t_cmd		*commands;
	int			last_status;
}				t_msh;

char			**copy_env(char **env);
int				env_size(char **env);
void			print_2d_arr(char **arr);
void			print_error(char *command, char *argument, char *message);
int				remove_var(char *name, char **env);

#endif