/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 21:45:52 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 23:12:03 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t g_signal_event;

/*Here we simply set the behaviour for when we get either SIGINT or SIGQUIT.
We use the rl functions from the gnu library to manage the line creation.
We also set the global variable to CLEAN. We'll check on every key point
if the global variable global_flag has been set to CLEAn in order to of course clean*/

void signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_event = CLEAN;
	}
	else if (sig == SIGQUIT) //do nothing
	{
		g_signal_event = CONTINUE;
	}
	return ;
}
