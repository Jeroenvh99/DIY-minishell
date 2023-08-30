/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_glob_destroy.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/15 20:09:08 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/21 15:56:59 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob.h"
#include "ft_list.h"
#include <stdlib.h>

void	ft_glob_destroy(t_ft_glob *pglob)
{
	list_clear(&pglob->globl, free);
	pglob->size = 0;
}
