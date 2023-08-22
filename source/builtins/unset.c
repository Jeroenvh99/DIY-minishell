/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-hal <jvan-hal@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 16:50:13 by jvan-hal      #+#    #+#                 */
/*   Updated: 2023/08/22 15:10:23 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_var.h"

#include "ft_stdio.h"
#include "ft_string.h"
#include <stddef.h>
#include <unistd.h>

/**
 * @brief	Unset an environment variable.
 * @return	An exit status:
 * 			- 0 on success;
 * 			- 1 if `cmd` contained at least one invalid identifier.
 * @note	All identifiers contained in `cmd` will be processed, irrespective
 * 			of their validity.
 * @note	"_" cannot be unset.
 */
int	msh_unset(t_cmd *cmd, t_msh *msh)
{
	size_t	i;
	int		ret;

	ret = 0;
	i = 1;
	while (cmd->argv.array[i])
	{
		if (var_isname(cmd->argv.array[i]) != 0)
		{
			ft_dprintf(STDERR_FILENO, "msh: unset: `%s': not a valid "
				"identifier\n", cmd->argv.array[i]);
			ret = 1;
		}
		else if (ft_strncmp(cmd->argv.array[i], "_", 2))
			env_unset(&msh->env, cmd->argv.array[i]);
		i++;
	}
	return (ret);
}
/* DB: Bij mij geeft bash geen melding 'does not exist' bij een niet-bestaande
 * naam. */
