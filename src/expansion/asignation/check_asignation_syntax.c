/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_asignation_syntax.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:34:34 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/08 17:15:08 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	Propósito:
	*Verifica si la sintaxis interna del token es válida para una asignación.

	Lógica:
	*El nombre de la variable debe comenzar con una letra o guion bajo.
	*No debe contener espacios, tabulaciones ni caracteres de control.
	*Debe haber exactamente un '=' en el token.
*/

int check_asignation_syntax(t_token *token)
{
	int	i;
	int	len;
	int	check_syntax;

	i = 0;
	check_syntax = 0;
	len = ft_strlen(token->value);
	if (len < 1)
		return (FALSE);
	if (!ft_isalpha(token->value[i]) && token->value[i] != '_')
		return (FALSE);
	while (token->value[i] != '\0')
	{
		if (token->value[i] == ' ' || token->value[i] == '\t'
			|| token->value[i] == '\v')
			return (FALSE);
		if (token->value[i] == '=')
			check_syntax++;
		i++;
	}
	if (check_syntax != 1)
		return (FALSE);
	return (TRUE);
}

int my_export(t_shell *data, t_token *tokens, t_env *env)
{
	int i;
	int result;

	i = tokens->id;
	result = is_it_asig(data, &tokens[i + 1], env, 18);
	return (result);
}

int which_builtin(t_shell *data, t_token *token, t_env *env)
{
	if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		my_echo();
	else if (ft_strcmp(token->value, BUILTIN_PWD) == 0)
		my_pwd();
	else if (ft_strcmp(token->value, BUILTIN_CD) == 0)
		my_cd();
	else if (ft_strcmp(token->value, BUILTIN_EXPORT) == 0)
		my_export(data, token, env);
	else if (ft_strcmp(token->value, BUILTIN_ENV) == 0)
		my_env();
	else if (ft_strcmp(token->value, BUILTIN_UNSET) == 0)
		my_unset();
	else if (ft_strcmp(token->value, BUILTIN_EXIT) == 0)
		my_exit();
}
