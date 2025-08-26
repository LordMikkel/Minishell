/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmdsubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:47:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/26 21:09:44 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	is_cmdsubs(t_token *tokens, const char *str, int *i)
{
	if (str[*i] == '`')
	{
		add_token(tokens, "`", CMD_SUBSTITUTION);
		(*i)++;
	}
}
