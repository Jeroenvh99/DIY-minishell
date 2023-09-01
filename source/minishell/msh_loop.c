/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 15:49:21 by dbasting      #+#    #+#                 */
/*   Updated: 2023/09/01 14:25:00 by dbasting         ###   ########.fr       */
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

int	msh_loop(t_msh *msh)
{
	char	*line;
	t_list	*tokens;

	tokens = NULL;
	while (1)
	{
		msh->errno = cmdline_prompt(&line, msh);
		if (msh->errno == MSH_EOF)
			return (0);
		msh->errno = lex(&tokens, line);
		if (msh->errno != MSH_SUCCESS)
			break ;
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
