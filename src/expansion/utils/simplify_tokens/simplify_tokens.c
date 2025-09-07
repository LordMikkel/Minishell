/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 20:37:22 by migarrid          #+#    #+#             */
/*   Updated: 2025/09/07 06:03:36 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../inc/minishell.h"

static void	join_tokens(t_prompt *prompt, t_token *tokens, int *range)
{
	int		i;
	char	*tmp;
	char	*result;

	i = range[0];
	result = ft_strdup("");
	while(i <= range[1])
	{
		if (is_cmd_type(tokens[i].type))
		{
			tmp = result;
			result = ft_strjoin(result, tokens[i].value);
			free(tmp);
		}
		i++;
	}
	reorganize_tokens(prompt, tokens, range, result);
}

static int is_possible_simplify(t_token *tokens, int *range)
{
	int	i;
	int	has_no_space;

	i = range[0];
	has_no_space = 0;
	while(i <= range[1])
	{
		if (tokens[i].type == NO_SPACE)
			has_no_space = 1;
		if (tokens[i].type == EXPANSION)
			return (0);
		i++;
	}
	return (has_no_space);
}

int find_range_start(t_token *tokens, int no_space_position)
{
	int start;

	start = no_space_position;
	if (start >= 5
		&& is_quote_type(tokens[start - 1].type)
		&& is_quote_type(tokens[start - 2].type)
		&& is_quote_type(tokens[start - 3].type)
		&& is_between_quotes_type(tokens[start - 4].type))
		return (start - 5);
	else if(start >= 4
		&& is_quote_type(tokens[start - 1].type)
		&& is_quote_type(tokens[start - 2].type)
		&& is_quote_type(tokens[start - 3].type)
		&& is_quote_type(tokens[start - 4].type))
		return (start - 4);
	else if (start >= 4
		&& is_quote_type(tokens[start - 1].type)
		&& is_quote_type(tokens[start - 2].type)
		&& is_between_quotes_type(tokens[start - 3].type))
		return (start - 4);
	else if (start >= 3
		&& is_quote_type(tokens[start - 1].type)
		&& is_between_quotes_type(tokens[start - 2].type))
		return (start - 3);
	else if (start >= 2
		&& is_quote_type(tokens[start - 1].type)
		&& is_quote_type(tokens[start - 2].type))
		return (start - 2);
	else if (start >= 1)
		return (start - 1);
}

int find_range_end(t_token *tokens, int no_space_position)
{
	int end;

	end = no_space_position;
	if (tokens[end + 5].type
		&& is_quote_type(tokens[end + 1].type)
		&& is_quote_type(tokens[end + 2].type)
		&& is_quote_type(tokens[end + 3].type)
		&& is_between_quotes_type(tokens[end + 4].type))
		return (end + 5);
	else if(tokens[end + 4].type
		&& is_quote_type(tokens[end + 1].type)
		&& is_quote_type(tokens[end + 2].type)
		&& is_quote_type(tokens[end + 3].type)
		&& is_quote_type(tokens[end + 4].type))
		return (end + 4);
	else if (tokens[end + 4].type
		&& is_quote_type(tokens[end + 1].type)
		&& is_quote_type(tokens[end + 2].type)
		&& is_between_quotes_type(tokens[end + 3].type))
		return (end + 4);
	else if (tokens[end + 3].type
		&& is_quote_type(tokens[end + 1].type)
		&& is_between_quotes_type(tokens[end + 2].type))
		return (end + 3);
	else if (tokens[end + 2].type
		&& is_quote_type(tokens[end + 1].type)
		&& is_quote_type(tokens[end + 2].type))
		return (end + 2);
	else if (end >= 1)
		return (end + 1);
}

int	get_no_space_range(t_token *tokens, int *range, int start_i)
{
	int i;
	int	j;

	i = start_i;
 	while(tokens[i].type)
	{
		if (tokens[i].type == NO_SPACE)
		{
			j = i + 1;
			range[0] = find_range_start(tokens, i);
			// while(tokens[j].type && is_simplify_type(tokens[j].type))
			// {
			// 	if (tokens[j].type == NO_SPACE)
			// 	{
			// 		range[1] = find_range_end(tokens, j);
			// 		return (SUCCESS);
			// 	}
			// 	j++;
			// }
			range[1] = find_range_end(tokens, i);
			return (SUCCESS);
		}
		i++;
	}
	return(FAILURE);
}

void	simplify_tokens(t_shell *data, t_prompt *prompt, t_token *tokens)
{
	int i;
	int	range[2];

	i = 0;
	while(tokens[i].type)
	{
		if (get_no_space_range(tokens, range, i))
		{
			if (is_possible_simplify(tokens, range))
			{
				join_tokens(prompt, tokens, range);
				i = range[0] + 1;
				continue;
			}
		}
		i++;
	}
}
