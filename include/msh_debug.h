/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   msh_debug.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dbasting <dbasting@codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 08:44:58 by dbasting      #+#    #+#                 */
/*   Updated: 2023/08/08 13:59:51 by dbasting      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_DEBUG_H
# define MSH_DEBUG_H

# include "msh.h"
# include "msh_parse.h"

# include "ft_list.h"

void	cmd_view(t_cmd *cmd);
void	cmds_view(t_list *cmds);
void	cmdtree_view(t_cmdtree *tree, int offset);
void	token_view(t_token *token);
void	tokens_view(t_list *tokens);

void	shuntingyard_view(t_list *out);

#endif
