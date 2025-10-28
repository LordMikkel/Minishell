/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 10:08:33 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/10/28 10:33:50 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	update_envp(t_shell *data)
{
	if (!data->env.envp)
		return ;
	ft_free_str_array(data->env.envp);
	data->env.envp = NULL;
	data->env.envp = make_envp(data, &data->env, data->env.vars);
}

