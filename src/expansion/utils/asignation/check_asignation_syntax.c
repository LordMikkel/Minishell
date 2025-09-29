/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_asignation_syntax.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:34:34 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/09/24 15:26:36 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Asignaciones solo pueden tener "&& || | asignaciones" detras y delante para
	funcionar. Nada de BUILT-INS o CMD o WORDS
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

static int	invalid_char(int c)
{
	if ((c >= 0 && c <= 31) || (c >= 33 && c <= 42) || (c >= 44 && c <= 47)
		|| (c >= 58 && c <= 64) || (c >= 91 && c <= 96)
		|| (c >= 123 && c <= 126) || c > 127)
		return (TRUE);
	return (FALSE);
}

/*
	Función para revisar la syntaxis de la asignación.

	1. Debe tener texto válido antes del "="
	2. Debe tener al menos un "="
	3. Debe tener texto después del "="

	Los espacios que se buscan son solamente en caso de que el usuarios haga:
	"VAR = Hola" - "VAR= Hola" - "VAR =Hola"
	De lo contrario, debería de poder pasar esa verificación facilemnte ya que
	una asignación no tiene espacios (al menos una local, ya que una de export
	de tipo EXP - "export l r" si funcionaria).

	Recordemos que hay tres tipos de asignación:

	1. LOCAL -> VAR=Hola -> Se guarda dentro del shell/local pero no en el env.
	2. ENV -> export VAR=hola -> Se guarda dentro del env.
	3. EXP -> export hola -> Se guarda en la lista de variables exportadas.
*/

static int	count_syntax(t_token *token)
{
	int	i;
	int	check_for_equal;
	int	text_before_equal;
	int	text_after_equal;

	i = 0;
	check_for_equal = 0;
	text_before_equal = 0;
	text_after_equal = 0;
	while (token->value[i] != '\0')
	{
		if (token->value[i] == '=')
			check_for_equal++;
		if (check_for_equal == 0)
			text_before_equal++;
		else if (check_for_equal > 0)
			text_after_equal++;
		if (i > 0 && token->value[i + 1] != '\0' && ft_isspace(token->value[i])
			&& token->value[i + 1] == '=')
				return (FALSE);
		i++;
	}
	if (!check_for_equal || !text_before_equal || !text_after_equal)
		return (FALSE);
	return (TRUE);
}

static int	check_invalid_char(t_token *token)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token->value[len] != '=' && token->value[len] != '\0')
		len++;
	while (token->value[i] != '=' && token->value[i] != '\0')
	{
		if (i == 0 && !ft_isalpha(token->value[i]) && token->value[i] != '_')
			return (FALSE);

		if (invalid_char(token->value[i]) && i + 1 < len
			&& token->value[i + 1] != '=' && token->value[i] == '+')
				return (FALSE);
		i++;
	}
	return (SUCCESS);
}

/*
	Esta funión verifica que la asignacion de tipo EXP no tenga ningun
	caracter invalido.

	Eg. hola=, hola@, @hola, etc...

	La diferencia con "check_invalid_char" es que en este caos iteramos sobre
	la totalidad del str, mientras que en la otra función simplemente iteramos
	hasta encontrarnos un "="
*/

static int	check_invalid_char_exp(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] != '\0')
	{
		if (i == 0 && !ft_isalpha(token->value[i]) && token->value[i] != '_')
			return (FALSE);
		if (invalid_char(token->value[i]))
			return (FALSE);
		i++;
	}
	if (i == 0)
		return (FALSE);
	return (SUCCESS);
}

int	check_asignation_syntax(t_token *token, int type)
{
	int	len;
	int	result;

	len = ft_strlen(token->value);
	if (len < 1)
		return (FALSE);
	if (type == EXP)
	{
		result = check_invalid_char_exp(token);
		return (result);
	}
	result = check_invalid_char(token);
	if (!result)
		return (FALSE);
	result = count_syntax(token);
	return (result);
}
