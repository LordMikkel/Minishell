/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:58 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:21:40 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta el operador de redirección heredoc '<<' y añade token.
	Avanza el índice para saltar el token.
*/

void	is_heredoc(t_token *tokens, const char *str, int *i)
{
	if (!ft_strncmp(str, "<<", 2))
	{
		add_token(tokens, "<<", REDIR_HEREDOC);
		(*i)++;
	}
}
