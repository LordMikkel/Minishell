/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_matches.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:42:56 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 19:43:30 by migarrid         ###   ########.fr       */
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

static int	through_dir(t_wild *wild, DIR *dir, char **dirs)
{
	int				count;
	struct dirent	*entry;

	count = 0;
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (should_ignore_file(entry->d_name, wild))
			continue ;
		if (match_wildcard(wild->key, entry->d_name))
		{
			if (extract_dir(&dirs[count++], entry->d_name) == ERROR)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

/*
	Ordena los matches alfabeticamente igual que bash.
*/

static void	sort_matches(char **dirs)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (dirs[0] && dirs[i])
	{
		j = i;
		while (j > 0 && ft_strcmp(dirs[j - 1], dirs[j]) > 0)
		{
			tmp = dirs[j];
			dirs[j] = dirs[j - 1];
			dirs[j - 1] = tmp;
			j--;
		}
		i++;
	}
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

char	**find_matches(t_shell *data, t_wild *wildcard_info, int n_dirs)
{
	char	**dirs;
	DIR		*directory;

	directory = opendir(".");
	if (!directory)
	{
		perror("minishell: opendir: ");
		ft_free((void **)&wildcard_info->key);
		return (NULL);
	}
	if (aux_alloc_mem(&dirs, n_dirs) == ERROR
		|| through_dir(wildcard_info, directory, dirs) == ERROR)
	{
		ft_free((void **)&wildcard_info->key);
		ft_free_str_array(&dirs);
		closedir(directory);
		exit_error(data, ERR_MALLOC, EXIT_FAILURE);
	}
	closedir(directory);
	sort_matches(dirs);
	return (dirs);
}
