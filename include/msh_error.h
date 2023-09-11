/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_error.h                                        :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:42:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/11 15:57:42 by dbasting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

# include <stdarg.h>

typedef enum e_errno {
	MSH_SUCCESS = 0,
	MSH_ENDCMD_PIPE,
	MSH_ENDCMD_CTL,
	MSH_GENERIC,
	MSH_SYNTAX_ERROR,
	MSH_INVVARID,
	MSH_INCOMPLETE_TOKEN,
	MSH_EOF,
	MSH_PIPEFAIL,
	MSH_FILEFAIL,
	MSH_FORKFAIL,
	MSH_MEMFAIL,
	N_ERRNO,
}	t_errno;

void	msh_perror(unsigned int n, ...);
void	msh_strerror(t_errno errno);

#endif
