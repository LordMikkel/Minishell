/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_matches.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:15:26 by davdiaz-          #+#    #+#             */
/*   Updated: 2025/11/21 19:43:23 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../inc/minishell.h"

static int	go_through_dir(t_wild *wild, DIR *dir)
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
			count++;
	}
	return (count);
}

int	count_matches(t_wild *wildcard)
{
	int		n_dirs;
	DIR		*directory;

	directory = opendir(".");
	if (!directory)
	{
		perror("minishell: opendir: ");
		ft_free((void **)&wildcard->key);
		wildcard->key = NULL;
		return (0);
	}
	n_dirs = go_through_dir(wildcard, directory);
	closedir(directory);
	return (n_dirs);
}
