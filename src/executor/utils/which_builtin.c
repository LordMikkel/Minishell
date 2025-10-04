/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:58:35 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/04 21:01:16 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void asignations(t_shell *data, t_token *token)
{
	if (token->type == ASIGNATION)
		data->last_exit_code = asignation(data, token, LOCAL);
	else if (token->type == PLUS_ASIGNATION)
		data->last_exit_code = asignation(data, token, PLUS_ASIGNATION);
	else if (token->type == TEMP_ASIGNATION)
		data->last_exit_code = asignation(data, token, TEMP_ASIGNATION);
}

static void	env_commands(t_shell *data, t_token *tokens, t_token *token)
{
	int flag_error;

	flag_error = 0;
	if (ft_strmatch_cmp(token->value, BUILTIN_EXPORT, &flag_error) == 0)
		data->last_exit_code = my_export(data, tokens, token, &data->env);
	else if (ft_strmatch_cmp(token->value, BUILTIN_UNSET, &flag_error) == 0)
		data->last_exit_code = my_unset(data, &data->env, tokens);
	else if (ft_strmatch_cmp(token->value, BUILTIN_ENV, &flag_error) == 0)
		data->last_exit_code = my_env(data->env.vars);
	else if (ft_strmatch_cmp(token->value, BUILTIN_UNSET, &flag_error) == 0)
		data->exit_code = my_unset(data, &data->env, tokens);
	if (flag_error == ERROR)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
}


static void	basic_builtins(t_shell *data, t_token *tokens, t_token *token)
{
	int flag_error;

	flag_error = 0;
	if (ft_strmatch_cmp(token->value, BUILTIN_ECHO, &flag_error) == 0)
		data->last_exit_code = my_echo(&data->prompt, token);
	else if (ft_strmatch_cmp(token->value, BUILTIN_PWD, &flag_error) == 0)
		data->last_exit_code = my_pwd(data);
	else if (ft_strmatch_cmp(token->value, BUILTIN_CD, &flag_error) == 0)
		data->last_exit_code = my_cd(data, tokens, token);
	else if (ft_strmatch_cmp(token->value, BUILTIN_EXIT, &flag_error) == 0)
		my_exit(data, &data->prompt, token);
	if (flag_error == ERROR)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
}

void	which_builtin(t_shell *data, t_token *tokens, t_token *token)
{
	asignations(data, token);
	env_commands(data, tokens, token);
	basic_builtins(data, tokens, token);
}
/*

assign(token, index)
{
	node crear;
	left = null;
	right = null;
	args = null;
	return;
}
search_for_word(tokens, i)
{
	while (mientras que sea word)
	{
		recoge eso como args para el nodo;
	}
	return ();
}

funcion(tokens, index)
{
	t_node left = NULL;

	left = assign(tokens, i);
	left = search_for_words(tokens, i);
	while (i < n_tokens)
	{
		t_node central_node;
		if (pipe)
		{
			central_node = assig(pipe);
		}
		if (and){
			central_node = assig(and);
		}
		i++;
		central_node->left = left;
		central_node->right = funtion(tokens, i);
		i++;
	}
	return (left);
}



parse_manager(t_token tokens, int i)
{
i = 0;

t_node root = parse_punto_coma(tokens, i);
}
parse_punto_coma(t_token tokens, int i)
{
	left = parse_and(tokens, i);
	if (token[i] == ";")
	{
		right = parse_and(tokens, i);
		return (new_punto_node(left, right));
	}
	return (left);
}
parse_and(t_token tokens, int i)
{
	left = parse_pipe(tokens, i);
	if (token[i] == "&&")
	{
		right = parse_pipe(tokens, i);
		return (new_and_node(left, right));
	}
	return (left);
}

parse_pipe(t_token tokens, int i)
{
	left = parse_redirection(tokens, i);
	if (token[i] == "|")
	{
		right = parse_redirection(tokens, i);
		return (new_pipe_node(left, right));
	}
	return (left);
}

parse_redirection(t_token tokens, int i)
{
	left = parse_parenthesis(tokens, i);
	if (token[i] == ">")
	{
		right = parse_parenthesis(tokens, i);
		return (new_redirection_node(left, right));
	}
	return (left);
}
parse_parentheses(t_token tokens, int i)
{
	t_node subexpr;
	if (PAREN)
	{
		(*i)++;
		subexpr = parse_punto_coma(tokens, i);
		(*i)++;
		return new_paren_node(subexpr);
	}
	return parse_cmd(tokens, i);
}


assign(t_token tokens, int i)
{
	node crear;
	left = null;
	right = null;
	args = search_for_words(tokens, i);
	return;
}

search_for_word(t_token tokens, int i)
{
	while (tokens[i].type == WORD)
	{
		nuestra_funcion();
		*i++;
	}
	return ();
}

funcion(t_token tokens, int i)
{
	t_node left = NULL;

	if (tokens[i].type && tokens[i].type == COMMAND)
		left = assign(tokens, &i);
}


#secuencia
#and_or
#pipe
#redir
#subshell-> secuencia
#comand
*/
