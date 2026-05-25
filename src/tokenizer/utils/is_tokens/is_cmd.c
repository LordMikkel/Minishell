/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:35:11 by migarrid          #+#    #+#             */
/*   Updated: 2026/05/25 03:58:40 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

/*
	Libera los buffers temporales creados durante la busqueda en PATH.
*/

static void	free_path_parts(char **path_slash, char **full_path)
{
	if (*path_slash)
		free(*path_slash);
	*path_slash = NULL;
	if (*full_path)
		free(*full_path);
	*full_path = NULL;
}

/*
	Busca un ejecutable en cada directorio del PATH.
	- path_arr: lista de directorios del PATH.
	- path_slash: directorio + "/" temporal.
	- full_path: directorio + "/" + palabra (posible comando).
	- word: nombre del comando a buscar.
	- Retorna SUCCESS si lo encuentra, NOT_FOUND si no, ERROR si falla malloc.
	- Libera los temporales en cada iteracion.
*/

static int	find_bin(char **path_arr, char *word)
{
	int	i;
	char	*path_slash;
	char	*full_path;

	i = 0;
	path_slash = NULL;
	full_path = NULL;
	while (path_arr[i] != NULL)
	{
		path_slash = ft_strjoin(path_arr[i], "/");
		if (!path_slash)
			return (free_path_parts(&path_slash, &full_path), ERROR);
		full_path = ft_strjoin(path_slash, word);
		if (!full_path)
			return (free_path_parts(&path_slash, &full_path), ERROR);
		if (access(full_path, F_OK) == OK)
		{
			free_path_parts(&path_slash, &full_path);
			return (SUCCESS);
		}
		free_path_parts(&path_slash, &full_path);
		i++;
	}
	return (NOT_FOUND);
}

/*
	Comprueba si la palabra es un built-in conocido.
	- built_in: lista de comandos internos.
	- Si coincide, marca token->type = BUILT_IN
	- Devuelve YES si es built-in, NO si no lo es.
	- Usa ft_strmatch_cmp: Tranforma s1 para que haga match con s2 por si el
	usuario hace: Ls - Echo - ECHO - LS - CD - cd - etc...
*/

int	is_built_in(t_shell *data, t_token *token, char *str)
{
	char	**builtins;
	int		len;
	int		i;

	i = 0;
	len = data->builtins.n_builtins;
	builtins = data->builtins.builtins_selection;
	while (i < len)
	{
		if (ft_strmatch_cmp(builtins[i], str) == 0)
		{
			if (token)
				token->type = BUILT_IN;
			return (YES);
		}
		i++;
	}
	return (NO);
}

/*
	Determina si un token es un comando ejecutable o built-in.
	- Primero revisa built-ins con is_built_in.
	- Luego busca en PATH si no es built-in.
	- Si PATH no existe por no env, crea un PATH por defecto.
	- Actualiza token->type = COMMAND si lo encuentra.
	- Maneja errores de memoria y limpia recursos temporales.
*/

int	is_cmd(t_shell *data, t_token *token, char *str)
{
	char	**path_arr;
	char	*path;
	int		validate;

	path = get_var_value(data->env.vars, "PATH");
	if (!path)
		path = DEFAULT_PATH;
	if (is_built_in(data, token, str) == YES)
		return (OK);
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (exit_error(data, ERR_MALLOC, EXIT_FAILURE));
	validate = find_bin(path_arr, str);
	if (validate == ERROR)
	{
		ft_free_str_array(&path_arr);
		return (exit_error(data, ERR_MALLOC, EXIT_FAILURE));
	}
	if (validate == SUCCESS)
		token->type = COMMAND;
	ft_free_str_array(&path_arr);
	return (OK);
}
