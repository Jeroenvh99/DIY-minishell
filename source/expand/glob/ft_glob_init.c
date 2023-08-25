/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob_init.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 15:47:44 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 15:51:51 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "ft_string.h"

void	ft_glob_init(t_ft_glob *pglob)
{
	ft_memset(pglob, 0x0, sizeof(t_ft_glob));
}
