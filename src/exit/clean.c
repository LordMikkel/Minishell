/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:47:38 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:55 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_prompt(t_prompt *prompt)
{
	free(prompt->tokens);
	prompt->tokens = NULL;
	*prompt = (t_prompt){0};
}

void	clean_all(t_shell *data)
{
	if (data->prompt.tokens)
		clean_prompt(&data->prompt);
}
