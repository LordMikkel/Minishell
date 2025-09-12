/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_tokens_for_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:57:13 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/12 18:26:39 by davdiaz-         ###   ########.fr       */
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

int	send_tokens_for_asig(t_shell *data, t_token *tokens, int type)
{
	int	i;

	i = 0;
	while (i < data->prompt.n_alloc_tokens)
	{
		if (tokens[i].type == ASIGNATION)
		{
			if (asignation(data, tokens, type))
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int send_tokens_to_process(t_shell *data, t_token *tokens, int phase, int type)
{
	if (type == EXPANSION)
		send_tokens_for_expansion(data, tokens, phase);
	else if (type == ASIGNATION)
		send_tokens_for_asig(data, tokens, LOCAL);
	return (SUCCESS);
}

