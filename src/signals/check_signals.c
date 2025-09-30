/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:47:16 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/30 21:35:30 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_signals(t_shell *data)
{
	if (g_signal[0] == SIG_INTERACTIVE)
	{
		if (g_signal[1] == SIGINT)
		{
			data->exit_code = EXIT_CTRL_C;
			g_signal[1] = VOID;
			return (RECIVED_SIGNAL);
		}
	}
	else if (g_signal[0] == SIG_HEREDOC)
	{
		if (g_signal[1] == SIGINT)
		{
			data->exit_code = EXIT_CTRL_C;
			g_signal[1] = VOID;
			exit_error(data, NULL, EXIT_CTRL_C);
			return (RECIVED_SIGNAL);
		}
	}
	return (VOID);
}
