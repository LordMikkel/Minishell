/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_parenten.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:43:52 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 17:03:03 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Detecta y añade tokens para paréntesis de apertura '(' o cierre ')'.
*/

void	is_parenten(t_shell *data, t_prompt *prompt, const char *str, int *i)
{
	char	c;

	c = str[*i];
	if (c == '(')
	{
		add_token(data, prompt, "(", PAREN_OPEN);
		(*i)++;
	}
	else if (c == ')')
	{
		add_token(data, prompt, ")", PAREN_CLOSE);
		(*i)++;
	}
}
