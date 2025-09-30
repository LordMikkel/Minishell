/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_quoted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:23:00 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/26 21:40:22 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void is_it_quoted(t_prompt *prompt, t_token *tokens)
{
	int	i;
	int	in_quotes_flag;

	i = 0;
	in_quotes_flag = FALSE;
	while (i < prompt->n_tokens)
	{
		if (tokens[i].type == DOUBLE_QUOTE)
		{
			in_quotes_flag = !in_quotes_flag;
			i++;
			continue ;
		}
		else if (tokens[i].type == SINGLE_QUOTE)
		{
			in_quotes_flag = !in_quotes_flag;
			i++;
			continue ;
		}
		if (in_quotes_flag)
			tokens[i].double_quoted = TRUE;
		i++;
	}
}

