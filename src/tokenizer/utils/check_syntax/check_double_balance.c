/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double_balance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 22:40:25 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/08/19 22:41:01 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
    Verifica si el balance de comillas está equilibrado.
    Si hay más cierres que aperturas o viceversa, lanza error de sintaxis.
*/

static int check_the_balance(t_shell *data, int balance, char *quote_type)
{
    if (balance < 0)
	{
	    syntax_error(data, ERR_SYNTAX, EXIT_USE, quote_type);// cierre sin apertura
		return (SYNTAX_ERROR);
	}
    else if (balance > 0)
    {
		syntax_error(data, ERR_SYNTAX, EXIT_USE, quote_type);// apertura sin cierre
		return (SYNTAX_ERROR);
    }
    return (SUCCESS);
}

/*
    Comprueba que las comillas dobles estén correctamente emparejadas.
    Luego llama a check_single_balance para validar también las comillas simples.
*/
static void first_coincidence(t_token *tokens, int *flag_check, int *balance, int i)
{
    if (tokens[i].type == DOUBLE_QUOTE && flag_check == FALSE)
	{
		*flag_check = TRUE;
		*balance++;
    }
}

int	check_double_balance(t_shell *data, t_prompt *prompt, t_token *tokens, int i)
{
	int balance;
	int flag_check;

	balance = 0;
	flag_check = FALSE;
    if (tokens[i].type == DOUBLE_QUOTE)
    {
        while (i < prompt->n_tokens)
	    {
            first_coincidence(tokens, &flag_check, &balance, i);
	        if (tokens[i].type == DOUBLE_QUOTE && i > 0)
            {
                flag_check = FALSE;
                balance--;
            }
	        if (!check_the_balance(data, balance, "\""))
                return (SYNTAX_ERROR);
	        i++;
	    }
        if (!check_the_balance(data, balance, "\""))
            return (SYNTAX_ERROR);
    }
    return (SUCCESS);
}
