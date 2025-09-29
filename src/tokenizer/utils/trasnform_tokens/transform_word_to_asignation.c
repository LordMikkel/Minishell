/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_word_to_asignation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:15:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/26 01:58:55 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	transform_word_to_asignation(t_shell *data, t_token *tokens, int phase)
{
	int	i;
	int	result;

	i = 0;
	while (i < data->prompt.n_tokens)
	{
		if (tokens[i].type != WORD && tokens[i].type != ASIGNATION
			&& tokens[i].type != COMMAND)
		{
			i++;
			continue ;
		}
		if (phase == INITIAL_PHASE)
			result = check_asignation_syntax(&tokens[i], INDIFERENT);
		else if (phase == FINAL_PHASE)
			result = check_externs_syntax(data, tokens, &tokens[i], INDIFERENT);
		if (result == TRUE)
			tokens[i].type = ASIGNATION;
		else if (result == FALSE && phase == FINAL_PHASE
			&& tokens[i].type == ASIGNATION)
			tokens[i].type = WORD;
		i++;
	}
}
