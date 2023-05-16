#ifndef MSH_DEBUG_H
# define MSH_DEBUG_H

# include "msh.h"
# include "msh_parse.h"

# include "ft_list.h"

void	cmd_view(t_cmd *cmd);
void	cmds_view(t_list *cmds);
void	token_view(t_token *token);
void	tokens_view(t_list *tokens);

#endif
