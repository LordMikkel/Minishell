/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:51:54 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 21:05:44 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H_
# define MINISHELL_STRUCTS_H_

# include "minishell.h"

volatile sig_atomic_t	g_signal_event;

typedef enum	e_type
{
	WORD,
	GROUP,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	COMMAND,
	AND,
	OR
}	t_type;

typedef struct	s_token
{
	t_type		type;
	char		*value;
	bool		quoted;
	bool		expand;
	t_exp		expansion;
	t_token		*next;
}	t_token;

typedef struct	s_prompt
{
	int 		n_parentesis;
	int			n_single_quotes;
	int			n_double_quotes;
	int			n_escape;
	int			n_pipes;
	int			n_cmds;
	int			n_tokens;
	char		*prompt;
	t_token 	*tokens;
}	t_prompt;


typedef struct	s_var
{
	char		*key;
	char		*value;
}	t_var;

typedef struct	s_env
{
	t_var		*vars;
	int			size;
}	t_env;

typedef	struct s_exp
{
	bool		asterisk;
	bool		dolar;
	char		*input;
	t_env		*env;
}	t_exp;

typedef struct s_exec
{
	pid_t	*pids;
	int		n_pids;
	int		n_pipes;
	int		**pipes;
	int		original_stdin;
	int		original_stdout;
	t_env	*env;
}	t_exec;

typedef struct	s_node
{
	int				id;
	t_type			type;
	t_token			token;
	t_node			*left;
	t_node			*right;
	pid_t			pid;
	int				exit_code;
	bool			executed;
}	t_node;

typedef struct	s_shell
{
	t_prompt		prompt;
	t_node			*ast_root;
	t_exec			executor;
	t_env			env;
} t_shell;

#endif
