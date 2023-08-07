/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_debug.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/07 16:17:43 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/07 18:10:14 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

#include "ft_list.h"
#include <stdio.h>

void	shuntingyard_view(t_list *out)
{
	t_tunion			*tunion;
	char const *const	ctls[4] = {"&&", "||", "(", ")"};
	while (out)
	{
		tunion = out->content;
		if (tunion->tag == TAG_PPL)
			printf("pipe (%02zu): %s\n",
				list_size(tunion->data.ppl),
				((t_cmd *)tunion->data.ppl->content)->argv.array[0]);
		else if (tunion->tag == TAG_CTL)
			printf("%s\n", ctls[((t_token *)tunion->data.ctl)->type - TOK_CTL_MIN]);
		else
			printf("???\n");
		out = out->next;
	}
}
