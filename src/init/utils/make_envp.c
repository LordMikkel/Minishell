/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:43:35 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/16 21:17:00 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	**make_envp(t_shell *data, t_env *env, t_var *vars)
{
	int		i;
	int		substring_len;
	char	**envp;

	i = 0;
	**envp = ft_calloc(env->size, sizeof(char *));
	while(i < env->size)
	{
		if (vars->type == ENV)
			envp[i] = ft_strjoin_multi(3, vars->key, "=", vars->value);
		i++;
	}
	return (envp);
}
