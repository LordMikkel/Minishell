/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:45 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:22:46 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta redirecciones de salida '>', '>>' o entrada '<'.
	Añade el token correspondiente y ajusta el índice si es doble.
*/

void	is_redir(t_token *tokens, const char *str, int *i)
{
	if (!ft_strncmp(str, ">>", 2))
	{
		add_token(tokens, ">>", REDIR_APPEND);
		(*i)++;
	}
	else if (str[0] == '>')
		add_token(tokens, ">", REDIR_OUTPUT);
	else if (str[0] == '<')
		add_token(tokens, "<", REDIR_INPUT);
}
