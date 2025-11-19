/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_script_args_to_end.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:34:44 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/17 23:17:57 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static int	extract_script_args(t_prompt *p, t_token *tokens, t_token **out_tmp)
{
	int	j;
	int	count_args;
	int	delimiter_position;

	j = 0;
	delimiter_position = 0;
	count_args = 0;
	while (delimiter_position < p->n_tokens
		&& !is_delimiter_type(tokens[delimiter_position].type))
		delimiter_position++;
	*out_tmp = ft_calloc(delimiter_position, sizeof(t_token));
	if (!*out_tmp)
		return (ERROR);
	while (j < delimiter_position)
	{
		if (tokens[j].type == SCRIPT_ARG)
		{
			(*out_tmp)[count_args] = tokens[j];
			count_args++;
		}
		j++;
	}
	return (count_args);
}

static void	reorg_tokens(t_prompt *p, t_token *ts, t_token *tmp, int count_args)
{
	int	delimiter_position;
	int	write_position;
	int	j;

	j = 0;
	delimiter_position = 0;
	write_position = 0;
	while (delimiter_position < p->n_tokens
		&& !is_delimiter_type(ts[delimiter_position].type))
		delimiter_position++;
	while (j < delimiter_position)
	{
		if (ts[j].type != SCRIPT_ARG)
		{
			ts[write_position] = ts[j];
			write_position++;
		}
		j++;
	}
	ft_memmove(&ts[write_position], tmp, count_args * sizeof(t_token));
	ft_memmove(&ts[write_position + count_args], &ts[delimiter_position],
		(p->n_tokens - delimiter_position) * sizeof(t_token));
	free (tmp);
}

/*
	Funcion para mover los tokens SCRIPT_ARGS al final del prompt o al final
	del comando de modo que no se tengan en cuenta.

	Ejemplo:

	-> $1 && ls -> fake_node && cmd_node
	-> $1 $1 $1 ls && echo hola -> ls $1 $1 $1 && echo hola ->
		cmd_node && builtin_node
	-> ls $1$ $1$USER $1$abc && echo hola -> ls $ $USER $1 $1 $1 && echo hola

	Se detecta un delimitador o el final del prompt en caso de que no haya
	delimitador, de modo que se puedan mover al final siempre y cuando vengan
	acompañados de otros tokens. De lo contrario no se mueven.
*/

void	move_script_args_to_end(t_shell *data, t_prompt *p, t_token *tokens)
{
	t_token	*tmp;
	int	count_args;

	tmp = NULL;
	count_args = extract_script_args(p, tokens, &tmp);
	if (count_args == ERROR)
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	else if (count_args == 0)
	{
		free (tmp);
		return ;
	}
	reorg_tokens(p, tokens, tmp, count_args);
}
