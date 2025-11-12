/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_matches.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davdiaz- <davdiaz-@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:15:26 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/12 21:34:12 by davdiaz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

static int	should_ignore_file(char *filename, char *wildc, int wildcard_type)
{
	if (ft_strcmp(filename, ".") == 0 || ft_strcmp(filename, "..") == 0) //ignorar . y ..
		return (TRUE);
	if (filename[0] == '.') // Si el archivo empieza con '.' (es oculto)
	{
		if (wildcard_type == END && wildc[0] == '.')// Solo incluirlo si también empieza con '.'
			return (FALSE); // No ignorar: patrón es .algo*
		if (wildcard_type == BEGINING && wildc[0] == '.')
			return (FALSE); // No ignorar: patrón es *.algo pero empieza con .
		if (wildcard_type == MIDDLE && wildc[0] == '.')
			return (FALSE); // No ignorar: patrón es *.algo*
		return (TRUE); // Ignorar: archivo oculto y patrón no empieza con .
	}
	return (FALSE); // No ignorar: archivo visible
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

static int	go_through_dir(DIR *directory, char *key_to_find, int wildcard_type)
{
	int		count;
	struct 	dirent *entry;

	count = 0;
	while (1)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (should_ignore_file(entry->d_name, key_to_find, wildcard_type))
			continue;
		if (wildcard_type == ALL)
			count++;
		else if (if_theres_match(entry->d_name, key_to_find, wildcard_type))
			count++;
	}
	return (count);
}

int	count_matches(t_shell *data, char *key_to_find, int wildcard_type)
{
	int		n_dirs;
	DIR 	*directory;

	directory = opendir(".");
	if (!directory)
	{
		perror("minishell: opendir: ");
		free (key_to_find);
		return (0);
	}
	n_dirs = go_through_dir(directory, key_to_find, wildcard_type);
	closedir(directory);
	return (n_dirs);
}
