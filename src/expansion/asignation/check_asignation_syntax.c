/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_asignation_syntax.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:34:34 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/10 01:16:12 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/*

	Asignaciones solo pueden tener && || | asignaciones detras y delante para funcionar. Nada de BUILT-INS o CMD o WORDS
	Si tiene asignaciones - cmd ignora la asignacion.
	si tiene cmd asignacion - es parte argumento
	Export funciona ignorarndo todo lo que no sea asignacion.
	Si export tiene detras un cmd, es WORD
	Si export tiene detras un word o cmd falla
	Propósito:
	*Verifica si la sintaxis interna del token es válida para una asignación.

	Lógica:
	*El nombre de la variable debe comenzar con una letra o guion bajo.
	*No debe contener espacios, tabulaciones ni caracteres de control.expo
	export && hola -> bash: hola: command not found
	export=jaja=jiji -> hace export de todo el str:
	bash-3.2$ echo $export=jaja=jiji
	bash-3.2$ jaja=jiji=jaja=jiji
*/

static int count_syntax(t_token *token)
{
	int i;
	int	check_for_equal;
	int	before_text;
	int after_text;

	check_for_equal = 0;
	before_text = 0;
	after_text = 0;
	while (token->value[i] != '\0')
	{
		if (check_for_equal == 0)
			before_text++;
		else if (check_for_equal > 0)
			after_text++;
		if (is_space(token->value[i]))
			return (FALSE);
		if (token->value[i] == '=')
			check_for_equal++;
		i++;
	}
	if (!check_for_equal || !before_text || !after_text)
		return (FALSE);
	return (TRUE);
}

int check_asignation_syntax(t_token *token)
{
	int	i;
	int	len;
	int	result;

	i = 0;
	len = ft_strlen(token->value);
	if (len < 1)
		return (FALSE);
	if (!ft_isalpha(token->value[i]) && token->value[i] != '_')
		return (FALSE);
	result = count_syntax(token->value);
	return (result);
}


/**
 * Implementación de la función `export` en un shell personalizado.
 *
 * Propósito:
 * Ejecutar asignaciones de variables de entorno cuando se llama al comando `export`,
 * y mostrar las variables exportadas si no se proporcionan argumentos válidos.
 *
 * Lógica general:
 * - La función recibe un puntero al token que representa el comando `export`.
 * - Comienza a recorrer los tokens a partir de su posición (`tokens->id`).
 * - En cada iteración:
 *   - Si encuentra un operador lógico (`AND`, `OR`), un pipe (`PIPE`) o un paréntesis de apertura (`PAREN_OPEN`),
 *     se detiene, ya que esos tokens indican un cambio de contexto en el árbol de ejecución.
 *   - Si el token actual es de tipo `ASIGNATION`, se ejecuta la asignación mediante `is_it_asig()`.
 *   - Los tokens que no sean asignaciones se ignoran silenciosamente.
 *
 * Comportamiento especial:
 * - Si no se ejecuta ninguna asignación (es decir, si `export` se llama sin argumentos válidos),
 *   se imprime la lista de variables exportadas actualmente en el entorno.
 * - Cada variable se muestra en formato Bash-compatible: `declare -x VAR="value"`.
 *
 * Ventajas del diseño:
 * - Evita ejecutar tokens irrelevantes o comandos que no forman parte de `export`.
 * - Respeta el flujo lógico del AST y la semántica real del comando `export`.
 * - Permite extender fácilmente el comportamiento para soportar más casos (como `export -p` o variables sin valor).
 */

int my_export(t_shell *data, t_token *tokens, t_env *env)
{
	t_var	*var;
	int	i;
	int	result;

	var = env->vars;
	i = tokens->id;
	while (i < data->prompt.n_alloc_tokens)
	{
		if (tokens[i].type == PIPE || tokens[i].type == AND
			|| tokens[i].type == OR || tokens[i].type == PAREN_OPEN
			|| (tokens[i].type == WORD)
			&& ft_strcmp(tokens[i].value, BUILTIN_EXPORT) == 0)
			break ;
		if (tokens[i].type == ASIGNATION)
			result = is_it_asig(data, &tokens[i], env, ENV);
		i++;
	}
	if (i == 1 && (tokens[i].type == WORD
		&& ft_strcmp(tokens[i].value, BUILTIN_EXPORT) == 0))
	{
		while (var)
		{
			if (var->type == ENV)
				printf("declare -x %s=\"%s\"\n", var->key, var->value);
			var = var->next;
		}
	}
	return (result);
}

int which_builtin(t_shell *data, t_token *token, t_env *env)
{
	if (ft_strcmp(token->value, BUILTIN_ECHO) == 0)
		my_echo();
	else if (ft_strcmp(token->value, BUILTIN_PWD) == 0)
		my_pwd();
	else if (ft_strcmp(token->value, BUILTIN_CD) == 0)
		my_cd();
	else if (ft_strcmp(token->value, BUILTIN_EXPORT) == 0)
		my_export(data, token, env);
	else if (ft_strcmp(token->value, BUILTIN_ENV) == 0)
		my_env();
	else if (ft_strcmp(token->value, BUILTIN_UNSET) == 0)
		my_unset();
	else if (ft_strcmp(token->value, BUILTIN_EXIT) == 0)
		my_exit();
}

void token_words_to_asignation(t_shell *data, t_token *tokens)
{
	int i;
	int	result;

	i = 0;
	while (i < data->prompt.n_alloc_tokens)
	{
		result = check_externs_syntax(data, &tokens[i], &result);
		if (result == TRUE)
			tokens->type = ASIGNATION;
		else if (result == IGNORE)
			eliminate_token(&tokens[i]); //o simpelmete un bool que diga: state: ignore;
	}
}
