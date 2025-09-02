/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:17:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/02 22:39:53 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_var	*lstlast_var(t_var *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	add_var(t_shell *data, char *key, char *value, int type)
{
	t_var	*new_var;
	t_var	*last_var;

	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return(free(key), free(value), (void)exit_error(data, ERR_MALLOC, 1));
	new_var->key = key;
	new_var->value = value;
	new_var->type = type;
	last_var = lstlast_var(data->env.vars);
	if (!last_var)
		data->env.vars = new_var;
	else
		last_var->next = new_var;
}

void	init_no_env(t_shell *data, t_env env, t_var *vars)
{
	char	*var[6];

	var[0] = strdup("PWD");
	var[1] = getcwd(NULL, 0);
	var[2] = strdup("SHLVL");
	var[3] = strdup("1");
	var[4] = strdup("_");
	var[5] = strdup("/usr/bin/env");
	if (!var[0] || !var[1] || !var[2] || !var[3] || !var[4] || !var[5])
		return(ft_free_str_array(var), (void)exit_error(data, ERR_MALLOC, 1));
	add_var(data, var[0], var[1], ENV);
	add_var(data, var[2], var[3], ENV);
	add_var(data, var[4], var[5], ENV);
}

void	init_enviroment(t_shell *data, char **envp)
{
	if (!envp)
		init_no_env(data, data->env, data->env.vars);
	else
	{
	}
}

void	init_data(t_shell *data, char **input, char **envp)
{
	*input = NULL;
	*data = (t_shell){0};
	data->prompt.tokens = NULL;
	data->ast_root = NULL;
	data->env.vars = NULL;
	data->session_start = time(NULL);
	init_enviroment(data, envp);
	print_session_start(data->session_start);
}
