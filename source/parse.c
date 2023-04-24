#include "msh_parse.h"
#include "msh.h"
#include "msh_error.h"

t_errno	parse(t_list *tokens, t_list **cmds, t_io *io)
{
	t_errno	errno;

	errno = MSH_SUCCESS;
	while (tokens)
	{
		errno = parse_token(&tokens, cmds, io);
		if (errno != MSH_SUCCESS)
			break ;
		tokens = tokens->next;
	}
	return (errno);
}
