/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:02:29 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/23 03:12:26 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	check_ambiguous_redir(t_shell *data, t_redir *redir, int mode)
{
	t_prompt prompt;

	prompt = data->prompt;
	if (redir->type == REDIR_HEREDOC);
		return (OK);
	if (!redir->filename)
		return (FAIL);
	if (redir->filename[0] == '*' && redir->filename[1] == '\0')
	{
		if (mode == CHILD)
			return (exit_error(data, ERR_AMBIGUOUS_REDIR, EXIT_FAILURE, "*"));
		if (mode == FATHER || mode == SUBSHELL)
			return (ft_printf_fd(STDERR, ERR_AMBIGUOUS_REDIR, "*"), FAIL);
	}
	else if (redir->filename[0] == '$' && ischrkey(redir->filename[1]))
	{
		if (mode == CHILD)
			return (exit_error(data, ERR_AMBIGUOUS_REDIR, EXIT_FAILURE, redir->filename));
		if (mode == FATHER)
			return (ft_printf_fd(STDERR, ERR_AMBIGUOUS_REDIR, redir->filename), FAIL);
	}
	return (OK);
}
