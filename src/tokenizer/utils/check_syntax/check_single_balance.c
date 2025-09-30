/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_single_balance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:39:40 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/26 21:30:07 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Comprueba que las comillas dobles estén correctamente emparejadas.
	Usa un estado booleano: dentro o fuera de comillas.
	Cada comilla doble cambia el estado.
*/

int	check_single_balance(t_shell *data, t_prompt *promp, t_token *tokens)
{
	int	i;
	int	inside_quotes;


	i = 0;
	inside_quotes = FALSE;
	while (i < promp->n_tokens)
	{
		if (tokens[i].type == SINGLE_QUOTE) //Cadacomilla doble cambia el estado
		{
			if (inside_quotes == FALSE)
				inside_quotes = TRUE; // Entramos en comillas
			else
				inside_quotes = FALSE; // Salimos de comillas
		}
		i++;
	}
	if (inside_quotes == TRUE) // Si terminamos dentro de comillas, hay error
	{
		syntax_error(data, ERR_SYNTAX, EXIT_USE, "\"");
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}
