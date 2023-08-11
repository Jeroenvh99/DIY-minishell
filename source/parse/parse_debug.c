/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_debug.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 16:17:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 14:20:32 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

#include "ft_list.h"
#include <stdio.h>

void	shuntingyard_view(t_list *out)
{
	t_cmdtree			*node;
	char const *const	ctls[4] = {"&&", "||", "(", ")"};

	while (out)
	{
		node = out->content;
		if (!node->op)
			printf("pipe (%02zu): %s\n",
				list_size(node->data.pipeline),
				((t_cmd *)node->data.pipeline->content)->argv.array[0]);
		else if (node->op)
			printf("%s\n", ctls[node->op - 1]);
		else
			printf("???\n");
		out = out->next;
	}
}
