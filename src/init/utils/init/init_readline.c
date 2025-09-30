/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:37:34 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/17 22:41:00 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Inicializa la librería de readline interactiva (ic_readline)
	configurando historial, marcador de prompt, multilinea, colores
	y estilos de texto para resaltar distintos elementos en la terminal.
*/

void	init_ic_readline(void)
{
	ic_set_history(DEFAULT_HISTORY, ILIMITED);
	ic_set_prompt_marker("", "");
	ic_enable_multiline(true);
	ic_enable_multiline_indent(false);
	ic_enable_highlight(true);
	ic_enable_color(true);
	ic_style_def("ic-prompt", "#4A90E2");
	ic_style_def("ic-info", "#6272a4");
	ic_style_def("ic-diminish", "#6272a4 italic");
	ic_style_def("ic-emphasis", "#8be9fd bold");
	ic_style_def("ic-hint", "#6272a4");
	ic_style_def("ic-error", "#ff5555 bold");
	ic_style_def("ic-bracematch", "#50fa7b bold");
}
