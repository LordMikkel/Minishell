/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_word_to_asignation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:15:55 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/12 18:06:03 by davdiaz-         ###   ########.fr       */
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
		if (tokens[i].type != WORD && tokens[i].type != ASIGNATION && tokens[i].type != COMMAND)
		{
			i++;
			continue ;
		}
		if (phase == 1)
			result = check_asignation_syntax(&tokens[i]);
		else if (phase == 2)
			result = check_externs_syntax(data, &tokens[i]);
		if (result == TRUE)
			tokens[i].type = ASIGNATION;
		else if (result == IGNORE)
			tokens[i].type = DELETE; //o un bool que diga: state: ignore;
		i++;
	}
}
