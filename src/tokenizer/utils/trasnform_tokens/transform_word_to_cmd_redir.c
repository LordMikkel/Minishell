/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:36:32 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/11 20:41:47 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	transform_word_to_cmd_redir(t_prompt *prompt, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < prompt->n_tokens)
	{
		if (i + 1 > prompt->n_tokens
			&& tokens[i].type == WORD
			&& (i > 0 && tokens[i - 1].type == DELIMITER
				|| tokens[i - 1].type == FILENAME))
			tokens[i].type = COMMAND;
		i++;
	}
}
