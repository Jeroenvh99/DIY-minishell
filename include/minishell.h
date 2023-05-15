/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 18:34:07 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/05/10 13:49:27 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef size_t			(*t_hashf)(char const *, size_t);

typedef struct s_hash_slot
{
	char				*key;
	void				*value;
	struct s_hash_slot	*next;
}						t_hash_slot;

typedef struct s_hashtable
{
	size_t				base_size;
	t_hashf				hashf;
	t_hash_slot			**slots;
}						t_hashtable;

typedef struct s_msh
{
	char				**env;
	int					envspc;
	int					envused;
	t_hashtable			*loc_var;
	int *commands; //changed to int type for test
	int					last_status;
}						t_msh;

char					**copy_env(char **env);
int						env_size(char **env);
void					print_2d_arr(char **arr);
void					print_error(char *command, char *argument,
							char *message);
char					*get_env_var(char *name, char **env);
int						remove_var(char *name, char **env);

#endif