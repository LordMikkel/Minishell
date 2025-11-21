/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_balance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:25 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 15:00:24 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Comprueba que las comillas dobles estén correctamente emparejadas.
	Usa un estado booleano: dentro o fuera de comillas.
	Cada comilla doble cambia el estado.
*/

int	check_double_balance(t_shell *data, t_prompt *promp, t_token *tokens)
{
	int	inside_quotes;
	int	i;

	inside_quotes = FALSE;
	i = 0;
	while (i < promp->n_tokens)
	{
		if (tokens[i].type == DOUBLE_QUOTE)
		{
			if (inside_quotes == FALSE)
				inside_quotes = TRUE;
			else
				inside_quotes = FALSE;
		}
		i++;
	}
	if (inside_quotes == TRUE)
	{
		syntax_error(data, ERR_SYNTAX, EXIT_USE, "\"");
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
