/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 21:22:59 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/16 18:51:34 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	LÓGICA:
	En esta función se halla el old_len del str original: Hello $USER.
	Se haya el key_len de la key: $USER.
	Se haya el value_len del valor de la key (val_of_k): DAVID
	Luego, se operan los len para poder determinar el len del str reemplazando
	$USER -> DAVID y poder usarlo en ft_realloc, que hará la alocación.
	Luego se cuentan los '$' y se busca uno por uno, en busca de $USER.
	Se hace la cuenta para evitar reconocer falsos-positivos
	en los que str: Hello $ $USER. -> Se ignora el primer '$' de modo
	que no se haga ninguna operación desde ese ptr en memoria.
*/
/*
int	copy_value(t_shell *d, char **token_val, char *key_value, char *key_to_find)
{
	char	*new_buffer;
	int		new_len;
	int		old_len;
	int		key_len;
	int		value_len;

	old_len = ft_strlen(*token_val);
	key_len = ft_strlen(key_to_find);
	value_len = ft_strlen(key_value);
	if (value_len != 0)
		new_len = old_len - key_len + value_len;
	else
		new_len = old_len - key_len + 1;
	new_buffer = ft_realloc(*token_val, old_len + 1, new_len + 10);
	if (!new_buffer)
	{
		free (key_to_find);
		exit_error(d, ERR_MALLOC, EXIT_FAILURE);
	}
	*token_val = new_buffer;
	new_buffer[new_len] = '\0';
	new_buffer = ft_strchr(*token_val, '$');
	if ((!new_buffer || !ft_isalpha(*(new_buffer + 1)))
		&& !is_symbol(*(new_buffer + 1)))
		return (ERROR);
	if (value_len != 0)
	{
		ft_memmove(new_buffer + value_len, new_buffer + key_len + 1,
			ft_strlen(new_buffer + key_len + 1) + 1);
		ft_memcpy(new_buffer, key_value, value_len);
	}
	else
	{
		ft_memmove(new_buffer, new_buffer + key_len + 1,
			ft_strlen(new_buffer + key_len + 1) + 1);
		ft_memcpy(new_buffer, key_value, 0);
	}
	(*token_val)[new_len] = '\0';
	return (SUCCESS);
}*/

static int	validate_and_find_dollar(char *str, char **dollar_pos)
{
	*dollar_pos = ft_strchr(str, '$');
	if (!*dollar_pos)
		return (ERROR);
	if (*(*dollar_pos + 1) == '\0')
		return (ERROR);
	if (!ft_isalpha(*(*dollar_pos + 1)) && !is_symbol(*(*dollar_pos + 1)))
		return (ERROR);
	return (SUCCESS);
}

static char	*realloc_token(t_shell *d, char **token_val, char *key_to_find, int new_len)
{
	char	*new_buffer;
	int		old_len;

	old_len = ft_strlen(*token_val);
	new_buffer = ft_realloc(*token_val, old_len + 1, new_len + 1);
	if (!new_buffer)
	{
		free(key_to_find);
		exit_error(d, ERR_MALLOC, EXIT_FAILURE);
	}
	new_buffer[new_len + 1] = '\0';
	printf("new_buffer: %s\n\n", new_buffer);
	*token_val = new_buffer;
	return (new_buffer);
}

int	copy_value(t_shell *d, char **token_val, char *key_value, char *key_to_find)
{
	char	*dollar_pos;
	int		new_len;
	int		key_len;
	int		value_len;

	key_len = ft_strlen(key_to_find);
	value_len = ft_strlen(key_value);
	new_len = ft_strlen(*token_val) - key_len + value_len;
	realloc_token(d, token_val, key_to_find, new_len);
	if (validate_and_find_dollar(*token_val, &dollar_pos) == ERROR)
		return (ERROR);
	if (value_len > 0)
	{
		ft_memmove(dollar_pos + value_len, dollar_pos + key_len + 1,
			ft_strlen(dollar_pos + key_len + 1) + 1);
		ft_memcpy(dollar_pos, key_value, value_len);
	}
	else
		ft_memmove(dollar_pos, dollar_pos + key_len,
			ft_strlen(dollar_pos + key_len) + 1);
	(*token_val)[new_len] = '\0';
	return (SUCCESS);
}
