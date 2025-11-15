/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ambiguous_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:02:29 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/15 14:41:30 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

int	check_ambiguous_redir(t_shell *data, const char *filename, int mode)
{
	if (filename[0] == '*' && filename[1] == '\0')
	{
		if (mode == CHILD)
			return (exit_error(data, ERR_AMBIGUOUS_REDIR, EXIT_FAILURE));
		if (mode == FATHER)
			return (FAIL);
	}
}
