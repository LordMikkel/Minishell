/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:55:44 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/18 16:19:55 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static int	check_if_error(char **builtins, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!builtins[i])
		{
			ft_free_str_array(builtins);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

void	init_builtins(t_shell *data)
{
	char	**built_ins;
	int		index;
	int		len;

	len = 9;
	built_ins = ft_calloc(len + 1, sizeof(char *));
	if (!built_ins)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	built_ins[0] = ft_strdup("cd");
	built_ins[1] = ft_strdup("echo");
	built_ins[2] = ft_strdup("export");
	built_ins[3] = ft_strdup("unset");
	built_ins[4] = ft_strdup("env");
	built_ins[5] = ft_strdup("exit");
	built_ins[6] = ft_strdup("pwd");
	built_ins[7] = ft_strdup("alias");
	built_ins[8] = ft_strdup("unalias");
	built_ins[9] = NULL;
	if (check_if_error(built_ins, len) == ERROR)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	data->builtins = ft_calloc(1, sizeof(t_builtin));
	if (!data->builtins)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	data->builtins->builtins_selection = built_ins;
	data->builtins->len = len;
}
