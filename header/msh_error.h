#ifndef MSH_ERROR_H
# define MSH_ERROR_H

typedef enum e_errno {
	MSH_SUCCESS = 0,
	MSH_GENERIC,
	MSH_MEMFAIL,
	MSH_SYNTAX_ERROR,
	MSH_INCOMPLETE_TOKEN,
	N_ERRNO,
}	t_errno;

#endif
