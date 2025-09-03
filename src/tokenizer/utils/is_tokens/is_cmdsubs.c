/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmdsubs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 20:47:41 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 17:03:21 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

void	is_cmdsubs(t_shell *data, t_prompt *prompt, const char *str, int *i)
{
	if (str[*i] == '`')
	{
		add_token(data, prompt, "`", CMD_SUBSTITUTION);
		(*i)++;
	}
}
