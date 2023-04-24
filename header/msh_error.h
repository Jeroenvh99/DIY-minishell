#ifndef MSH_ERROR_H
# define MSH_ERROR_H

typedef enum e_errno {
	MSH_SUCCESS = 0,
	MSH_GENERIC,
	MSH_MEMFAIL,
	MSH_SYNTAX_ERROR,
	N_ERRNO,
}	t_errno;

#endif
