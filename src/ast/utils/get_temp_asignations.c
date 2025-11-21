/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_temp_asignations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:54:11 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 15:05:56 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	Verifica si el token[i - 1] es una asignación temporal y la guarda como
	parte del contexto/metadata del comando que le sigue.
*/

static int	aux_alloc_mem(t_shell *data, char ***args, int n_args)
{
	*args = ft_calloc(n_args + 1, sizeof(char *));
	if (!*args)
	{
		ft_printf_fd(STDERR, ERR_MALLOC);
		data->error_state = TRUE;
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	extract_bin_arg(t_shell *data, char **arg_extract, char *word)
{
	*arg_extract = ft_strdup(word);
	if (!*arg_extract)
	{
		ft_free_str_array(&arg_extract);
		data->error_state = TRUE;
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
	Esto es porque después de restar a start, puede ser -1 o estar en un token
	que no corresponda a una asignacion temporal, de modo que hay que ubicar
	start en la TEMP_ASIG.
	Eg.
	(var=hola ls) -> start--; -> token[start].type == PAREN_OPEN
	var=hola ls -> start--; -> start == -1
*/

static int	get_correct_index(t_token *tokens, int n_tokens, int start)
{
	if (start >= 1 && is_asignation_type(tokens[start - 1].type))
	{
		start--;
		while (start >= 0 && is_asignation_type(tokens[start].type))
			start--;
		if (start < 0 && (start < n_tokens
				|| !is_asignation_type(tokens[start].type)))
			start++;
	}
	return (start);
}

static void	count_temps(t_token *tokens, int *start, int *temp_count, int i)
{
	while (*start < i && (tokens[*start].type == TEMP_ASIGNATION
			|| tokens[*start].type == TEMP_PLUS_ASIGNATION))
	{
		(*temp_count)++;
		(*start)++;
	}
}

char	**get_temp_asignations(t_shell *data, t_token *tokens, int i)
{
	char	**args;
	int		temp_count;
	int		start;

	if (i == 0)
		return (NULL);
	start = get_correct_index(tokens, data->prompt.n_tokens, i);
	if (start == i)
		return (NULL);
	temp_count = 0;
	count_temps(tokens, &start, &temp_count, i);
	if (temp_count == 0)
		return (NULL);
	if (!aux_alloc_mem(data, &args, temp_count))
		return (NULL);
	start = i - temp_count;
	temp_count = 0;
	while (start < i)
	{
		if (!extract_bin_arg(data, &args[temp_count], tokens[start].value))
			return (NULL);
		start++;
		temp_count++;
	}
	return (args);
}
