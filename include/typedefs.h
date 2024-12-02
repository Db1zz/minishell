#ifndef TYPEDEFS_H
# define TYPEDEFS_H

typedef enum s_token_type
{
	T_UNKNOWN,
	T_IN,
	T_OUT,
	T_HEREDOC,
	T_APPEND,
	T_WORD,
	T_PIPE,
	T_AND,
	T_OR
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	struct s_token	*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	struct s_token	*tokens;
	struct s_cmd	*cmds;
}	t_shell;


#endif	// TYPEDEFS_H
