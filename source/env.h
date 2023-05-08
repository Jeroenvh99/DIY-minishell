typedef struct s_msh {
	char		**env;
	t_hashtable	*loc_var;
	t_cmd		*commands;
	int			last_status;
}	t_msh;