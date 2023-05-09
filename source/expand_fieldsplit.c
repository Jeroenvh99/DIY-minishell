#include "msh_expand.h"
#include "msh_error.h"
#include "msh_utils.h"

#include "ft_list.h"
#include <stddef.h>
#include <stdlib.h>

static size_t	exp_strncpy(char *word, char *str, t_expop *ops);
static size_t	exp_wordlen(t_expop *ops);

//Split expstr.str according to expstr->ops; append every new word to list.
t_errno	expand_fieldsplit(t_expstr *expstr, t_list **words)
{
	char	*word;
	size_t	len;
	size_t	n_ops;

	expstr->i = 0;
	while (expstr->str[expstr->i])
	{
		while (expstr->ops[expstr->i] == EXPOP_ENDW)
			expstr->i++;
		len = exp_wordlen(&expstr->ops[expstr->i]);
	   	word = malloc((len + 1) * sizeof(char));
		if (word == NULL)
			return (MSH_MEMFAIL);
		n_ops = exp_strncpy(word, &expstr->str[expstr->i], &expstr->ops[expstr->i]);
		if (list_push_ptr(words, word) != MSH_SUCCESS)
			return (free(word), MSH_MEMFAIL);
		expstr->i += n_ops;
	}
	return (MSH_SUCCESS);
}

static size_t	exp_wordlen(t_expop *ops)
{
	size_t	len;

	len = 0;
	while (!(*ops == EXPOP_ENDW || *ops == EXPOP_ENDP))
	{
		if (*ops == EXPOP_COPY)
			len++;
		ops++;
	}
	return (len);
}

static size_t	exp_strncpy(char *word, char *str, t_expop *ops)
{
	size_t	i;

	i = 0;
	while (!(ops[i] == EXPOP_ENDP || ops[i] == EXPOP_ENDW))
	{
		if (ops[i] == EXPOP_COPY)
		{
			*word = str[i];
			word++;
		}
		i++;
	}
	*word = '\0';
	return (i);
}
