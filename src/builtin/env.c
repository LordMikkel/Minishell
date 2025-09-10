/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:09:26 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/03 01:15:54 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	shell_env(t_var *vars)
{
	t_var	*var;

	var = vars;
	while (var)
	{
		if (var->type == ENV)
			printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
}
