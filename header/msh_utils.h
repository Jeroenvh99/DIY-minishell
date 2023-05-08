#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "msh_error.h"

# include "ft_list.h"
# include <stddef.h>

char	*get_path(char *pathname);
t_errno	list_append_ptr(t_list **lst, void *ptr);
t_list	*list_pop(t_list **lst);
void	*list_pop_ptr(t_list **lst);

#endif
