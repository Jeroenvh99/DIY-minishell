#ifndef MSH_UTILS_H
# define MSH_UTILS_H

# include "msh_error.h"

# include "ft_list.h"
# include <stddef.h>

void	*ft_realloc(void *ptr, size_t newsize);
void	free_ptr_array(void **array, size_t size);
char	*get_path(char *pathname);
t_errno	list_append_ptr(t_list **lst, void *ptr);

#endif
