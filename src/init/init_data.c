/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 23:17:43 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/17 17:12:57 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Inicializa la estructura 'data' del shell: limpia valores,
	inicia tokens, AST y variables de entorno, guarda el inicio
	de sesión y muestra mensaje de bienvenida.
*/

/*
	Simulación de la expansión de la variable especial `$$`.
	En shells como Bash, `$$` representa el PID (Process ID) del
	proceso actual del shell. Sin embargo, en este proyecto no se permite
	el uso directo de `getpid()`, ni se puede acceder al PID real desde
	las variables de entorno estándar.

	Por esta razón, se genera un valor simulado para `$$` al iniciar el shell,
	que se guarda en `data->shell_pid`.

	Este valor se usa únicamente para expandir `$$` en el contexto
	del shell, y no debe considerarse como el PID real del proceso.
	No se recomienda usarlo en comandos como `kill $$` o `ps -p $$`, ya que no
	reflejará un proceso válido en el sistema. Mientras se mantenga estable
	durante la sesión, esta simulación es suficiente para cumplir con las
	expectativas del usuario en la mayoría de los casos de uso.
*/

void	init_data(t_shell *data, char **input, char **envp)
{
	*input = NULL;
	*data = (t_shell){0};
	data->prompt.tokens = NULL;
	data->ast_root = NULL;
	data->env.vars = NULL;
	data->shell_pid = 4242;
	data->extra_features.session_start = time(NULL);
	init_ic_readline();
	init_enviroment(data, envp);
	print_session_start(data, data->extra_features.session_start,
		data->extra_features.user_name);
}
