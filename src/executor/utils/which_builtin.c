/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:58:35 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/28 02:36:14 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	which_builtin(t_shell *data, t_token *tokens, t_token *token)
{
	if (token->type == ASIGNATION)
		data->last_exit_code = asignation(data, token, LOCAL);
	if (token->type == PLUS_ASIGNATION)
		data->last_exit_code = asignation(data, token, PLUS_ASIGNATION);
	if (token->type == TEMP_ASIGNATION)
		data->last_exit_code = asignation(data, token, TEMP_ASIGNATION);
	if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		data->last_exit_code = my_echo(&data->prompt, token);
	else if (ft_strcmp(token->value, BUILTIN_PWD) == 0)
		data->last_exit_code = my_pwd(data);
	else if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		data->last_exit_code = my_echo(&data->prompt, token);
	else if (ft_strcmp(token->value, BUILTIN_EXPORT) == 0)
		data->last_exit_code = my_export(data, tokens, token, &data->env);
	else if (ft_strcmp(token->value, BUILTIN_UNSET) == 0)
		data->last_exit_code = my_unset(data, &data->env, tokens);
	else if (ft_strcmp(token->value, BUILTIN_ENV) == 0)
		data->last_exit_code = my_env(data->env.vars);
	else if (ft_strcmp(token->value, BUILTIN_CD) == 0)
		data->last_exit_code = my_cd(data, tokens, token);
	else if (ft_strcmp(token->value, BUILTIN_EXIT) == 0)
		my_exit(data, &data->prompt, token);
}
