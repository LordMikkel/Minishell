/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_tokens_for_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:57:13 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/17 12:10:15 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	send_tokens_for_asig(t_shell *data, t_token *tokens, int phase)
{
	int	i;

	i = 0;
	if (phase == INITIAL_PHASE)
	{
		if (tokens[i].type == ASIGNATION)
			asignation(data, tokens, LOCAL);
	}
	else if (phase == FINAL_PHASE)
	{
		while (i < data->prompt.n_tokens)
		{
			if (tokens[i].type == ASIGNATION)
				asignation(data, tokens, LOCAL);
			i++;
		}
	}
	return (SUCCESS);
}
