/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic_trans_args_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:19 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/21 22:07:43 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	logic_trans_args_cmd(t_shell *data, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type)
	{
		if (i > 0 && (tokens[i - 1].type == COMMAND
				|| tokens[i - 1].type == BUILT_IN
				|| tokens[i - 1].type == WORD))
		{
			if (tokens[i].type == DOUBLE_QUOTE
				|| tokens[i].type == SINGLE_QUOTE)
			{
				if (tokens[i + 1].type == COMMAND
					|| tokens[i + 1].type == BUILT_IN)
					tokens[i + 1].type = WORD;
			}
			else if (tokens[i].type == COMMAND || tokens[i].type == BUILT_IN)
				tokens[i].type = WORD;
		}
		i++;
	}
}
