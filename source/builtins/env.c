/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:51:40 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/29 10:26:16 by jvan-hal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

#include "msh.h"
#include "ft_stdio.h"
#include "ft_string.h"

enum e_enverrno {
	ENV_SUCCESS = 0,
	ENV_INVARG,
	N_ENV_ERRNO,
};

static void	_env_strerror(int errno);
static void	_env_print(int fd, char **envp);

/**
 * @brief	Interact with the shell environment.
 * @return	An exit status:
 * 			- 0 on success
 * 			- 1 if `cmd` contains an invalid argument.
 */
int	msh_env(t_cmd *cmd, t_msh *msh)
{
	if (cmd->argc == 1)
	{
		_env_print(cmd->io[1], msh->env.envp);
		return (0);
	}
	_env_strerror(ENV_INVARG);
	return (127);
}
/*DB: De handleiding stelt dat deze functie ook programma's moet uitvoeren
 * met de als variabele opgegeven waarden als omgevingsvariabelen. Die moeten
 * dan niet blijven staan voor het volgende commando! Dus:
 * $env lorem=ipsum dolor | sit		-> 'dolor' kan de waarde van lorem zien
 * 									maar 'sit' kan dat niet.
 * De foutmelding 'no such file or directory' wordt niet door env() zelf
 * gegeven, maar door de subshell als die het programma dat op de laatste
 * positie staat niet kan vinden.
 */

static void	_env_strerror(int errno)
{
	char const *const	errmsg[N_ENV_ERRNO] = {
		NULL,
		"Invalid argument"};

	ft_dprintf(2, "msh: env: %s\n", errmsg[errno]);
}

static void	_env_print(int fd, char **envp)
{
	while (*envp)
	{
		ft_dprintf(fd, "%s\n", *envp);
		envp++;
	}
}
