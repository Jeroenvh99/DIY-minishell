/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:49:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/05 16:01:34 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_error.h"
#include "msh_execute.h"
#include "msh_parse.h"
#include "list_utils.h"

#include "ft_list.h"
#include <stdlib.h>
#include <unistd.h>

static inline void	cleanup(t_list **tokens, t_msh *msh);
static inline int		msh_procedure(t_msh *msh);

void	msh_loop(t_msh *msh)
{
	while (msh_procedure(msh) != 0)
		msh_strerror(msh->errno);
}

static inline int	msh_procedure(t_msh *msh)
{
	char	*line;
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		msh->errno = cmdline_prompt(&line, msh);
		if (msh->errno == MSH_EOF)
			return (0);
		else if (msh->errno == MSH_SYNTAX_ERROR)
			continue ;
		msh->errno = lex(&tokens, line);
		free(line);
		if (msh->errno != MSH_SUCCESS)
			break ;
		msh->errno = parse(msh, &tokens);
		if (msh->errno != MSH_SUCCESS)
			break ;
		msh->errno = execute(msh);
		if (msh->errno != MSH_SUCCESS)
			break ;
	}
	return (cleanup(&tokens, msh), 1);
}

static inline void	cleanup(t_list **tokens, t_msh *msh)
{
	list_clear(tokens, (t_freef)token_free);
	cmdtree_destroy(&msh->tree);
}
