/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:37:06 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/10 01:05:18 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
 * Sistema de expansión de variables en un shell personalizado.
 *
 * Este módulo permite detectar, validar y reemplazar variables de entorno
 * dentro de los tokens que contienen expresiones como `$VAR`.
 *
 * Flujo general:
 * 1. La función `send_tokens_for_expansion` recorre todos los tokens del
 *    prompt. Si un token está marcado como tipo `EXPANSION`,
 *    se envía a la función  `expansion`.
 *
 *
 * 2. En `expansion`, se reserva memoria para almacenar el nombre de la
 *    variable (`key_to_find`) y se cuenta cuántos signos `$` hay
 *    en el token con `count_char`.
 *    Esto permite manejar múltiples variables dentro de una misma cadena.
 *
 * 3. Por cada `$` detectado, se llama a `extract_key_string`, que:

 *    - Usa `copy_key` para extraer el nombre de la variable si es
 *     válida (letras sin espacios). Llama a `find_key_in_lst` para buscar
 *     el valor correspondiente en la lista `env.vars`.

 *    - Si no se encuentra y estamos en `phase == 2`, se reemplaza
 *     el token por una cadena vacía.
 *
 * 4. Si se encuentra la variable, `copy_value` se encarga de:
 *    - Calcular el nuevo tamaño del token con `calculate_total_lenght`.
 *    - Reasignar memoria con `ft_realloc`.
 *    - Localizar el `$VAR` en el token con `find_key_in_new_buffer`.
 *    - Reemplazar el nombre de la variable por su valor.
 *
 * 5. Funciones auxiliares:
 *    - `aux_mem_alloc`: reserva memoria para `key_to_find`.
 *    - `count_char`: cuenta cuántos signos `$` hay en una cadena.
 *    - `calculate_total_lenght`: calcula el tamaño necesario para
 *       el token expandido.
 *    - `find_key_in_new_buffer`: localiza la posición del `$VAR` a reemplazar.
 *
 * Validaciones:
 * - Solo se consideran válidas las variables que comienzan con `$`
 *    seguido de letras.
 * - Se evita copiar variables mal formadas como `$ VAR` o `$1`.
 * - Se maneja correctamente el error de memoria con `exit_error`.
 *
 * Este sistema permite una expansión segura, dinámica y escalable de variables
 * dentro de un shell, respetando fases de ejecución y tipos de token.
 */

static int aux_mem_alloc(t_shell *data, t_token *token, char **key_to_find)
{
	int len;

	len = ft_strlen(token->value);
	*key_to_find = (char *)malloc((len + 1)* sizeof(char));
	if (!*key_to_find)
	{
		exit_error(data, ERR_MALLOC, EXIT_USE);
		return (ERROR);
	}
	(*key_to_find)[len] = '\0';
	return (SUCCESS);
}

int copy_key(char *buffer, char **key_to_find)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '$')
		{
			i++;
			if (!ft_isalpha(buffer[i]))
				continue;
			start = i;
			while (ft_isalpha(buffer[start]) || (*key_to_find)[j] != '\0')
			{
				(*key_to_find)[j++] = buffer[start];
				start++;
			}
			(*key_to_find)[j] = '\0';
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int extract_key_string(t_shell *data, t_token *token, char **key_to_find, int phase)
{
	int	j;
	int	k;
	int	found;
	int	match;

	j = 0;
	k = 0;
	found = FALSE;
	match = copy_key(token->value, key_to_find);
	if (!match)
		return (FAILURE);
	found = find_key_in_lst(data, token, *key_to_find);
	if (found == ERROR)
		return (ERROR);
	if (!found && phase == 2)
	{
		token->value = ft_strdup(""); //cambiar el value por una str vacia si no se haya CREO QU ESTO ESTA MAL porque reemplaza tooodo el valu por "" y solo necesito que reemplaze la expansion
		if (!token->type)
		{
			exit_error(data, ERR_MALLOC, EXIT_USE);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

static char *find_key_in_new_buffer(char *token_val, int len)
{
	char *ptr;

	while (len > 0)
	{
		ptr = ft_strchr(token_val, '$');
		if (ptr && ft_isalpha(*(ptr + 1)))
			return (ptr);
		len--;
	}
	return (ptr);
}

static int copy_value(t_shell *data, char **token_val, char *key_value, char *key_to_find)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	len = calculate_total_length(data, *token_val, key_to_find);
	ft_realloc(*token_val, len);
	if (!*token_val)
		return (ERROR);
	ptr = find_key_in_new_buffer(*token_val, len);
	while (key_value[i] != '\0')
	{
		ptr[i + 1] = key_value[i];
		i++;
	}
	return (SUCCESS);
}

static int find_key_in_lst(t_shell *data, t_token *token, char *key_to_f)
{
	t_var	*var;

	var = data->env.vars;
	while (var != NULL)
	{
		if (ft_strcmp(var->key, key_to_f) == 0)
		{
			token->type = WORD;
			if (copy_value(data, &token->value, var->value, key_to_f) == ERROR)
			{
				exit_error(data, ERR_MALLOC, EXIT_USE);
				return (ERROR);
			}
			return (TRUE);
		}
		var = var->next;
	}
	return (FALSE);
}

int count_char(char *buffer, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

int calculate_total_length(t_shell *data, char *str, char *key_to_find)
{
	t_var	*var;
	int	len_of_token;
	int	len_of_expansion;
	int	total_len;

	var = data->env.vars;
	len_of_token = 0;
	len_of_expansion = 0;
	len_of_token = ft_strlen(str);
	while (var != NULL)
	{
		if (ft_strcmp(var->key, key_to_find) == 0)
		{
			len_of_expansion = ft_strlen(var->value);
			break ;
		}
		var = var->next;
	}
	total_len = len_of_token + len_of_expansion;
	return (total_len);
}

int	expansion(t_shell *data, t_token *token, t_env *env, int phase)
{
	char	*key_to_find;
	int		i;
	int		j;
	int		found;

	i = 0;
	found = FALSE;
	if (aux_mem_alloc(data, token, &key_to_find) == ERROR)
		return (ERROR);
	j = count_char(token->value, '$');
	while (j > 0)
	{
		found = extract_key_string(data, token, &key_to_find, phase);
		if (found == ERROR)
			return (ERROR);
		j--;
	}
	free (key_to_find);
	return (found);
}

int send_tokens_for_expansion(t_shell *data, t_token *tokens, int phase)
{
	int i;

	i = 0;
	while (i < data->prompt.n_alloc_tokens)
	{
		if (tokens[i].type == EXPANSION)
		{
			if (expansion(data, &tokens[i], phase) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

