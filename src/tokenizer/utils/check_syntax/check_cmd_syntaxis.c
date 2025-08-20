/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_syntaxis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:39:55 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/08/20 17:01:41 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta si un comando o built-in aparece justo después de un paréntesis
	cerrado. Si es así, lanza un error de sintaxis porque la estructura es
	inválida. Evita construcciones como ") ls", que no son válidas en el shell.
	Devuelve SUCCESS si no hay conflicto de sintaxis.
*/

int	check_cmd_syntax(t_shell *data, t_prompt *prompt, t_token *token, int i)
{
	char	*error_message;

	if (token[i].type == COMMAND || token[i].type == BUILT_IN)
	{
		if (i >= 1 && token[i - 1].type && token[i - 1].type == PAREN_CLOSE)
		{
			error_message = ft_strdup(token[i].value);
			if (!error_message)
			{
				exit_error(data, ERR_MALLOC, EXIT_FAILURE);
			}
			syntax_error(data, ERR_SYNTAX, EXIT_USE, error_message);
			free (error_message);
			return (SYNTAX_ERROR);
		}
	}
	return (SUCCESS);
}
