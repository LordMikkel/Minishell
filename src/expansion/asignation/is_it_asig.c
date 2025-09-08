/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_asig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:33:47 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/08 17:12:14 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*
	1. si hay un "="
	2. Que sea un grupo independiente
	3. Que no tenga detras un word o cmd o built-in o delante
	4. Si no es el primer token, solo puede tener && o || a su alrededor


	ASIGNACIÓN.

	Errores:
	1. 1VAR=.... ->
	2. VAR = ... -> Se ejecuta VAR como cmd y da error de ejecución. NO SE ASIGNA NADA.
	3. VAR= ...  -> A VAR se le asigna una cadena vacia y el resto se pone como word, de modo que el error es el WORD. SE ASIGNA CADENA VACIA
	4. VAR="HOLA -> Este error ya esta manejado.
	5. VAR=""HOLA"" ->  no error.
	6. CMD/BUILTIN VAR=Hola
	7. VAR=Hola CMD/BUILTIN

	Si el usuario hace una asignación de expansion:
	1. VAR="Hola"
	2. VAR=Hola
	3. VAR="Hola";
	4. VAR='Hola'
	5. VAR='Hola';
	6. VAR=(vacio) ->cadena vacia

	PROCEDIMIENTO:

	PRE-VERIFICACÓN:
	1. Verificación de =
	2. Verificación de sintaxis externa
	VERIFICACÓN:
	1. Sintaxis del token
	2. ASIGNACIÓN.
*/

/*
	Propósito:
	*Determina si un token representa una asignación local válida.

	Lógica:
	*Solo se evalúa si el token es de tipo ASIGNATION.
	*Se verifica si contiene un '=' → posible asignación.
	*Se llama a check_externs_syntax() para validar el contexto sintáctico
	externo (tokens vecinos).
	*Si pasa la verificación, se ejecuta asignation() para almacenar
	la variable.
*/

static int check_case_1(t_token *token)
{
	if (token[token->id - 1].type && token[token->id + 1].type)
	{
		if (token[token->id - 1].type == AND
			&& (token[token->id + 1].type == AND
				|| token[token->id + 1].type == OR))
		return (1);
	}
	return (0);
}

static int check_case_2(t_token *token)
{
	if (token[token->id - 1].type && !token[token->id + 1].type)
	{
			if (token[token->id - 1].type == AND
				|| (token[token->id - 1].type == BUILT_IN
				&& ft_strcmp(token[token->id - 1].value, "export") == 0))
		return (1);
	}
	return (0);
}

static int check_case_3(t_token *token)
{
	if (!token[token->id - 1].type && token[token->id + 1].type)
	{
		if (token[token->id + 1].type == AND || token[token->id + 1].type == OR
			|| token[token->id + 1].type == ASIGNATION
			|| (token[token->id + 1].type == BUILT_IN
				&& ft_strcmp(token[token->id + 1].value, "export") == 0))
		return (1);
	}
	return (0);
}

static void check_externs_syntax(t_shell *data, t_token *token, int *result)
{
	if (token->id > 0 && token->id < data->prompt.n_alloc_tokens)
	{
		if (check_case_1(token))
			*result = check_asignation_syntax(token);
		else if (check_case_2(token))
			*result = check_asignation_syntax(token);
		else if (check_case_3(token))
			*result = check_asignation_syntax(token);
	}
	else
		*result = check_asignation_syntax(token);
}

int is_it_asig(t_shell *data, t_token *token, t_env *env, int type)
{
	int	result;

	result = FALSE;
	if (token->type == ASIGNATION)
	{
		if (ft_strchr(token->value, '='))
			check_externs_syntax(data, token, &result);
	}
	if (result == TRUE)
		result = asignation(data, token, type);
	return (result);
}
