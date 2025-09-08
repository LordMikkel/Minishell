/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:37:06 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/08 15:09:37 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
	Proceso de expansión de variables:
	1. Se busca el primer token de tipo EXPANSION dentro del array de tokens.

	2. Se extrae la clave eliminando el símbolo '$' del valor del token.

	3. Se recorre la lista de variables del entorno buscando coincidencia con
	la clave.

	4. Si se encuentra, se reemplaza el token por el valor correspondiente
	y se marca como WORD.

	5. Si no se encuentra y estamos en fase 2, se imprime una línea vacía.
*/

static int aux_mem_alloc(t_shell *data, char **key_to_find, int len)
{
	key_to_find = (char *)malloc((len + 1)* sizeof(char)); //cambiarlo or calloc
	if (!key_to_find)
	{
		exit_error(data, ERR_MALLOC, EXIT_USE, key_to_find);
		return (ERROR);
	}
	return (SUCCESS);
}
static void find_expansion_token(t_token *tokens, int number_tokens, int *i)
{
	while (*i < number_tokens)
	{
		if (tokens[*i].type == EXPANSION)
			return ;
		*i++;
	}
}

static void extract_key_string(char *token_value, char **key_to_find)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (token_value[j] != '\0')
	{
		if (token_value[j] != '$')
			(*key_to_find)[k++] = token_value[j];
		j++;
	}
	(*key_to_find)[k] = '\0';
}

static int find_key_in_lst(t_token *token, t_env *env, char *key_to_find, int i)
{
	t_var	*var;

	var = env->vars->next;
	while (var != NULL)
	{
		if (ft_strcmp(var->key, key_to_find) == 0)
		{
			token[i].type = WORD;
			token[i].value = ft_strdup(var->value); //value hay que liberarlo al final del programa si fue exitoso. si no, no pasa nada
			if (!token[i].value)
				return (ERROR);
			return (TRUE);
		}
		var = var->next;
	}
	return (FALSE);
}

int	expansion(t_shell *data, t_token *token, t_env *env, int phase)
{
	char	*key_to_find;
	int		i;
	int		len;
	int		found;

	i = 0;
	found = FALSE;
	find_expansion_token(token, data->prompt.n_alloc_tokens, &i);
	len = ft_strlen(token[i].value);
	if (aux_mem_alloc(data, &key_to_find, len) == ERROR)
		return (ERROR);
	extract_key_string(token[i].value, &key_to_find);
	found = find_key_in_lst(token, env, key_to_find, i);
	if (found == ERROR)
	{
		exit_error(data, ERR_MALLOC, EXIT_USE, key_to_find);
		return (ERROR);
	}
	if (!found)
	{
		if (phase == 2)
			printf("\n");
	}
	free (key_to_find);
	return (found);
}
