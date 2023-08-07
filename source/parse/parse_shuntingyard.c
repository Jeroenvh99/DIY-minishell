/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_cmdtree.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 14:33:57 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/07 18:29:16 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_stdlib.h"
#include <stdlib.h>

#include <stdio.h>
#include "msh_debug.h"

static t_errno	shyard_read(t_tunion **tunion, t_list **input, t_msh *msh);
static t_errno	shyard_move_ctl(t_tunion *tunion, t_list **ctl, t_list **out);
static void		tunion_free(void *ptr);

t_errno	ft_shuntingyard(t_list **out, t_list **input, t_msh *msh)
{
	t_list		*ctl;
	t_tunion	*tunion;
	t_errno		errno;

	ctl = NULL;
	while (*input)
	{
		errno = shyard_read(&tunion, input, msh);
		if (errno != MSH_SUCCESS)
			return (list_clear(&ctl, tunion_free), errno);
		if (tunion->tag == TAG_PPL)
		{
			if (list_append_ptr(out, tunion) != 0)
				return (list_clear(&ctl, tunion_free), MSH_MEMFAIL);
		}
		else if (tunion->tag == TAG_CTL)
		{
			if (shyard_move_ctl(tunion, out, &ctl) != 0)
				return (list_clear(&ctl, tunion_free), MSH_MEMFAIL);
		}
		printf("out:\n");
		shuntingyard_view(*out);
		printf("\nctl:\n");
		shuntingyard_view(ctl);
		printf("\n-----\n");
	}
	while (ctl)
		list_append(out, list_pop(&ctl));
	return (MSH_SUCCESS);
}

static t_errno shyard_read(t_tunion **tunion, t_list **input, t_msh *msh)
{
	t_errno	errno;
	
	*tunion = ft_calloc(1, sizeof(t_tunion));
	if (!*tunion)
		return (MSH_MEMFAIL);
	if (!is_ctltok((*input)->content))
	{
		(*tunion)->tag = TAG_PPL;
		errno = parse_pipeline(&(*tunion)->data.ppl, input, msh);
		if (errno != MSH_SUCCESS)
			return (free(*tunion), errno);
	}
	else
	{
		(*tunion)->tag = TAG_CTL;
		(*tunion)->data.ctl = list_pop_ptr(input);
	}
	return (MSH_SUCCESS);
}

static t_errno	shyard_move_ctl(t_tunion *tunion, t_list **out, t_list **ctl)
{
	if (tunion->data.ctl->type == TOK_OPENPAR)
		return (list_push_ptr(ctl, tunion));
	if (tunion->data.ctl->type == TOK_CLOSEPAR)
	{
		while (*ctl && ((t_tunion *)(*ctl)->content)->data.ctl->type != TOK_OPENPAR)
			list_append(out, list_pop(ctl));
		if (!*ctl)
			return (MSH_SYNTAX_ERROR);
		return (tunion_free(list_pop_ptr(ctl)), tunion_free(tunion), MSH_SUCCESS);
	}
	else
	{
		while (*ctl)
			list_append(out, list_pop(ctl));
	}
	return (list_push_ptr(ctl, tunion));
}

static void tunion_free(void *ptr)
{
	t_tunion *const	tunion = ptr;

	if (tunion->tag == TAG_PPL)
		list_clear(&tunion->data.ppl, (t_freef)cmd_free);
	else
		free(tunion->data.ctl);
	free(tunion);
}
