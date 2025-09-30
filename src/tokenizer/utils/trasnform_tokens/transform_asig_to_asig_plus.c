/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_asig_to_asig_plus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 18:38:33 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/26 14:28:02 by davdiaz-         ###   ########.fr       */
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
	int	result;

	i = 0;
	result = FALSE;
	while (i < prom->n_tokens)
	{
		if (tokens[i].type != ASIGNATION)
		{
			i++;
			continue ;
		}
		result = check_plus_asig_syntax(tokens[i].value);
		if (result)
			tokens[i].type = PLUS_ASIGNATION;
		i++;
	}
}
