/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_invalid_asig_to_word.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:56:00 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/12 18:12:36 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void transform_invalid_asig_to_word(t_prompt *prompt, t_token *tokens)
{
	int i;

	i = 0;
	while (i < prompt->n_tokens)
	{
		if (i >= 1 && tokens[i - 1].type)
		{
			if (tokens[i].type == ASIGNATION)
			{
				if (tokens[i - 1].type == COMMAND
					|| tokens[i - 1].type == WORD
					|| (tokens[i - 1].type == BUILT_IN
					&& ft_strcmp(tokens[i - 1].value, BUILTIN_EXPORT) != 0))
						tokens[i].type = WORD;
			}
		}
		i++;
	}

}
