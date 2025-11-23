/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_correction_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 21:34:18 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/23 00:46:53 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Función para lanzar la linea de pregunta para corregir el cmd.
	El suario puede decir yes/no/y/n. Cualquier otra cosa será considerada
	inválida y se lanzará la pregunta otra vez hasta que el usuario escriba
	una respuesta válida.
*/

static int	is_yes_or_no(const char *str)
{
	if (ft_strcmp(str, "y") == 0 || ft_strcmp(str, "yes") == 0)
		return (YES);
	else if (ft_strcmp(str, "n") == 0 || ft_strcmp(str, "no") == 0)
		return (NO);
	return (ERROR);
}

static	int	parse_answer(t_shell *d, t_token *token, char *str, char *built_in)
{
	int	result;

	result = is_yes_or_no(str);
	if (result == YES)
	{
		free (token->value);
		token->value = ft_strdup(built_in);
		if (!token->value)
			exit_error(d, ERR_MALLOC, EXIT_FAILURE);
		return (SUCCESS);
	}
	else if (result == FALSE)
		return (FALSE);
	return (ERROR);
}

int	ask_confirmation(t_shell *data, t_token *token, char *built_in)
{
	char	*ptr;

	while (1)
	{
		ft_printf_fd(1, ASK_CONFIRMATION, built_in);
		ptr = ic_readline(PROMPT_CMD);
		if (!ptr)
			return (FAILURE);
		if (check_signals(data, NULL, NULL))
		{
			free (ptr);
			return (FAILURE);
		}
		if (parse_answer(data, token, ptr, built_in) != ERROR)
		{
			free (ptr);
			return (SUCCESS);
		}
		free (ptr);
	}
	return (SUCCESS);
}
