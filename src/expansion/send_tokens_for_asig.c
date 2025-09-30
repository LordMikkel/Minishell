/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_tokens_for_asig.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:57:13 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/30 19:03:06 by davdiaz-         ###   ########.fr       */
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
				asignation(data, &tokens[i], LOCAL); //hay que pasar la psocion refereniada ya que si no se hace asi, entonces siempre evalua el primer elemento del arr porque es a donde apunta
			else if (tokens[i].type == PLUS_ASIGNATION)
				asignation(data, &tokens[i], PLUS_ASIGNATION);
			else if (tokens[i].type == TEMP_ASIGNATION)
				asignation(data, &tokens[i], TEMP_ASIGNATION);
			i++;
		}
	}
	return (SUCCESS);
}
