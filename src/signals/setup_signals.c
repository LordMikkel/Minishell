/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 02:02:04 by migarrid          #+#    #+#             */
/*   Updated: 2025/11/23 17:48:33 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal;

/*
 * Configura señales para modo interactivo: maneja Ctrl+C
 * personalizado e ignora Ctrl+\\ para mantener el prompt activo
*/

void	setup_signals_interactive(t_shell *data)
{
	data->mode = SIG_INTERACTIVE;
	signal(SIGINT, handle_sigint_interative);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Configura señales para modo non-interactive: ignora Ctrl+C
 * y Ctrl+\\ para mantener dejar el control al child
*/

void	setup_signals_noninteractive(t_shell *data)
{
	data->mode = SIG_IGNORE;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

/*
 * Establece señales por defecto en hijos: permiten que los
 * procesos terminen normalmente con Ctrl+C y Ctrl+\\
*/

void	setup_signals_child(t_shell *data)
{
	data->mode = SIG_CHILD;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
 * Prepara señales para heredoc: manejo especial que interrumpe
 * la lectura sin salir del shell cuando se presiona Ctrl+C
*/

void	setup_signals_heredoc(t_shell *data)
{
	data->mode = SIG_HEREDOC;
	signal(SIGINT, handle_sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

// /*
//  * Configura señales para modo interactivo: maneja Ctrl+C
//  * personalizado e ignora Ctrl+\\ para mantener el prompt activo
// */

// void	setup_signals_interactive(void)
// {
// 	g_signal[0] = SIG_INTERACTIVE;
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }

// /*
//  * Establece señales por defecto en hijos: permiten que los
//  * procesos terminen normalmente con Ctrl+C y Ctrl+
// */

// void	setup_signals_child(void)
// {
// 	g_signal[0] = SIG_CHILD;
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// /*
//  * Prepara señales para heredoc: manejo especial que interrumpe
//  * la lectura sin salir del shell cuando se presiona Ctrl+C
// */

// void	setup_signals_heredoc(void)
// {
// 	g_signal[0] = SIG_HEREDOC;
// 	signal(SIGINT, handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }
