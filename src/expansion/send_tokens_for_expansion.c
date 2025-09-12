/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_tokens_for_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:57:13 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/12 21:09:52 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	send_tokens_for_expansion(t_shell *data, t_token *tokens, int phase)
{
	int	i;

	i = 0;
	while (i < data->prompt.n_alloc_tokens)
	{
		if (tokens[i].type == EXPANSION)
		{
			if (expansion(data, &tokens[i], &data->env, phase) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	send_tokens_for_asig(t_shell *data, t_token *tokens, int phase)
{
	int	i;

	i = 0;
	if (phase == 1)
	{
		if (tokens[i].type == ASIGNATION)
		{
			if (asignation(data, tokens, LOCAL))
				return (ERROR);
		}
	}
	else if (phase == 2)
	{
		while (i < data->prompt.n_alloc_tokens)
		{
			if (tokens[i].type == ASIGNATION)
			{
				if (asignation(data, tokens, LOCAL))
					return (ERROR);
			}
			i++;
		}
	}
	return (SUCCESS);
}

/*int send_tokens_to_process(t_shell *data, t_token *tokens, int phase, int type)
{
	if (type == EXPANSION)
		send_tokens_for_expansion(data, tokens, phase);
	else if (type == ASIGNATION)
		send_tokens_for_asig(data, tokens, LOCAL);
	return (SUCCESS);
}*/

