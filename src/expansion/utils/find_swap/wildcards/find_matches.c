/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:42:56 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/12 21:38:29 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

static int	aux_alloc_mem(char ***dirs, int n_dirs)
{
	*dirs = ft_calloc(n_dirs + 1, sizeof(char *));
	if (!*dirs)
		return (ERROR);
	return (SUCCESS);
}

static int	extract_dir(char **dir_extract, char *word)
{
	*dir_extract = ft_strdup(word);
	if (!*dir_extract)
		return (ERROR);
	return (SUCCESS);
}

/*
	La lógica es sencilla, se lee el directorio y se si hay un match con el
	key to find. Para saber que comparar con que, se revisa el status/type
	del wildcard. También se revisa si el len del wildcard es mayor que el
	del dir/file/elemento. Entonces: *pdf -> no hara match con str:"pd"

	wildcard: *pdf
	elemento: minishell.pdf ft_strchr = "p";
	ft_strcmp: "pdf" vs "pdf"

	De este modo ya sabemos que debemos tomar el elemento en cuenta para la
	expansión.
	Cabe resaltar que ignoramos elemtos del sistema que tengan "." o ".."
*/

static int	should_ignore_file(char *filename, char *wildc, int wildcard_type)
{
	if (ft_strcmp(filename, ".") == 0 || ft_strcmp(filename, "..") == 0)// Siempre ignorar . y ..
		return (1);
	if (filename[0] == '.')// Si el archivo empieza con '.' (es oculto)
	{
		if (wildcard_type == END && wildc[0] == '.') // Solo incluirlo si el patrón también empieza con '.'
			return (0); // No ignorar: patrón es .algo*
		if (wildcard_type == BEGINING && wildc[0] == '.')
			return (0); // No ignorar: patrón es *.algo pero empieza con .
		if (wildcard_type == MIDDLE && wildc[0] == '.')
			return (0); // No ignorar: patrón es *.algo*

		return (1); // Ignorar: archivo oculto y patrón no empieza con .
	}

	return (0); // No ignorar: archivo visible
}

static int	if_theres_match(char *file, char *key, int wild_type)
{
	char	*found;
	int		file_len;
	int		key_len;

	file_len = ft_strlen(file);
	key_len = ft_strlen(key);
	if (key_len > file_len)
		return (FAILURE);
	if (wild_type == BEGINING)
	{
		if (ft_strcmp(file + (file_len - key_len), key) == 0)
			return (SUCCESS);
	}
	else if (wild_type == END)
	{
		if (ft_strncmp(file, key, key_len) == 0)
			return (SUCCESS);
	}
	else if (wild_type == MIDDLE)
	{
		found = ft_str_match(file, key);
		if (found)
			return (SUCCESS);
	}
	return (FAILURE);
}

static int	through_dir(DIR *dir, char **dirs, char *key, int wildcard_type)
{
	int	count;
	struct 	dirent *entry;

	count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (should_ignore_file(entry->d_name, key, wildcard_type))
			continue;
		if (wildcard_type == ALL)
		{
			if (extract_dir(&dirs[count], entry->d_name) == ERROR)
				return (ERROR);
			count++;
		}
		else if (if_theres_match(entry->d_name, key, wildcard_type))
		{
			if (extract_dir(&dirs[count], entry->d_name) == ERROR)
				return (ERROR);
			count++;
		}
	}
	return (SUCCESS);
}

/*
	Función para encontrar elementos que coincidan en nombre con
	el key_to_find. Luego los copia en un char ** y los retorna para
	luego expandir el wildcard.

	ejemplo:

	echo *pfd;

	Dir: Minishell
		->Makefile
		->minishell
		->header
		->minishell.pdf -> Toma este!
*/

char	**find_matches(t_shell *d, char *key_to_find, int n_dirs, int wild_type)
{
	char	**dirs;
	DIR 	*directory;

	directory = opendir(".");
	if (!directory)
	{
		perror("minishell: opendir: ");
		free (key_to_find);
		return (NULL);
	}
	if (aux_alloc_mem(&dirs, n_dirs) == ERROR
		|| through_dir(directory, dirs, key_to_find, wild_type) == ERROR)
	{
		free (key_to_find);
		ft_free_str_array(dirs);
		closedir(directory);
		exit_error(d, ERR_MALLOC, EXIT_FAILURE);
	}
	closedir(directory);
	return (dirs);
}
