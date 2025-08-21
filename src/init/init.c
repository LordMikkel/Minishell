/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:17:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/21 17:17:45 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(t_shell *data, char **input)
{
	*input = NULL;
	*data = (t_shell){0};
	data->prompt.tokens = NULL;
	data->ast_root = NULL;
	data->env.vars = NULL;
	data->session_start = time(NULL);
	print_session_start(data->session_start);
}
