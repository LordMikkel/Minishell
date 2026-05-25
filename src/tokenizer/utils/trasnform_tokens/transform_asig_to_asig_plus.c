/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_asig_to_asig_plus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:38:33 by davdiaz-          #+#    #+#             */
/*   Updated: 2026/05/25 03:59:12 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static int	check_plus_asig_syntax(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i > 0 && str[i - 1] == '+')
		return (TRUE);
	return (FALSE);
}

void	transform_asig_to_asig_plus(t_prompt *prom, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < prom->n_tokens)
	{
		if (tokens[i].type != ASIGNATION && tokens[i].type != TEMP_ASIGNATION)
		{
			i++;
			continue ;
		}
		if (check_plus_asig_syntax(tokens[i].value))
			tokens[i].type = PLUS_ASIGNATION;
		i++;
	}
}
