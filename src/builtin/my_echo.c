/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 01:23:24 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/16 00:20:17 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// /*
// 	Procesa los argumentos de 'echo' y detecta todas las opciones '-n'
// 	consecutivas o -nnnnn..., para evitar imprimir la nueva línea final y
// 	avanzar al primer argumento real.
// */

// static void	handle_n_flag(char **args, int *new_line, int *i)
// {
// 	int	j;

// 	j = 0;
// 	while (args[*i] && args[*i][0] == '-' && args[*i][1] == 'n')
// 	{
// 		j += 2;
// 		while (args[*i][j] == 'n')
// 			j++;
// 		if (args[*i][j] == '\0')
// 		{
// 			*new_line = FALSE;
// 			(*i)++;
// 		}
// 		else
// 			break ;
// 	}
// }

// /*
// 	Implementa el comando 'echo': imprime los argumentos y añade
// 	una nueva línea a menos que se use '-n'.
// */

// void	shell_echo(char **args)
// {
// 	int	i;
// 	int	new_line;

// 	i = 1;
// 	new_line = TRUE;
// 	handle_n_flag(args[i], &new_line, &i);
// 	while (args[i])
// 	{
// 		printf("%s", args[i]);
// 		if (args[i + 1])
// 			printf(" ");
// 		i++;
// 	}
// 	if (new_line)
// 		printf("\n");
// }

/*
	Procesa los argumentos de 'echo' y detecta todas las opciones '-n'
	consecutivas o -nnnnn..., para evitar imprimir la nueva línea final y
	avanzar al primer argumento real.
*/

static void	handle_n_flag(t_token *token, int *new_line, int n_tokens, int *i)
{
	int	j;

	j = 0;
	while (token->id + *i < n_tokens && token[*i].type
		&& token[*i].value[0] == '-' && token[*i].value[1] == 'n')
	{
		j += 2;
		while (token[*i].value[j] == 'n')
			j++;
		if (token[*i].value[j] == '\0')
		{
			*new_line = FALSE;
			(*i)++;
		}
		else
			break ;
	}
}

/*
	Implementa el comando 'echo': imprime los argumentos y añade
	una nueva línea a menos que se use '-n'.
*/

int	my_echo(t_prompt *prompt, t_token *token)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = TRUE;
	handle_n_flag(token, &new_line, prompt->n_tokens, &i);
	while (token->id + i < prompt->n_tokens
		&& !is_delimiter_type(token[i].type))
	{
		ft_printf_fd(STDOUT, "%s", token[i].value);
		if (token->id + i + 1 < prompt->n_tokens
			&& !is_delimiter_type(token[i + 1].type))
			ft_printf_fd(STDOUT, " ");
		i++;
	}
	if (new_line)
		ft_printf_fd(STDOUT, "\n");
	// fflush(stdout);
	return (0);
}
