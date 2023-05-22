/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_error.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:42:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/05/22 08:43:03 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_ERROR_H
# define MSH_ERROR_H

typedef enum e_errno {
	MSH_SUCCESS = 0,
	MSH_ENDCMD_PIPE,
	MSH_ENDCMD_CTL,
	MSH_GENERIC,
	MSH_SYNTAX_ERROR,
	MSH_NO_VARSTR,
	MSH_INCOMPLETE_TOKEN,
	MSH_FILEFAIL,
	MSH_MEMFAIL,
	N_ERRNO,
}	t_errno;

void	msh_strerror(t_errno errno);

#endif
