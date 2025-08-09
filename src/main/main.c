/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:07:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 16:19:50 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	s_data;
{
	t_prompt	tokens;
	t_envp		envp;
	t_parser	ast;
}

int	main(int ac, char **av)
{
	t_shell	data;
	char	*input

	init_signals(void)
	init(&data, &input);
	while(1)
	{
		if (prompt(&input))
		{
			add_history(input);
			if (!minishell(data, input))
				return (exit_error(data));
		}
	}
	return (0);
}

int minishell(t_shell *data, char *input);
{
	if (!tokenizer(data, input))
		return (error(data));
	if (!expanstion(data->tokens, data->envp))
		return (error(data))
	if (!ast(data, data->tokens))
		return (error(data));
	if (!execute_recursive(data, data.ast))
		return (error(data));
	clean_data(data);
}

int	tokenizer
{
	review_global();
	asdv.kasbbdv.sc
	sdvasdv
	asdvasvvsa
	return (1)
}

int error(t_shell *data, char *error, int code)
{
	if (error)
		printf(error);
	if (data)
		clean_data(data);
	return (exit(code))
}

int init_signals()
{
	struct sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(ft_handler, sa) == ERROR)
	{
		perror(sigaction fail);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int ft_handler(int signal, saafw)
{
	if (signal == CTR_D)
	{
		global_flag == CLEAN_KILL;
	}
	else if (signal == CTRL_C)
	{
		global_flag == CLEAN;
	}
	else
	{
		global_flag == CONTINUE;
	}
}
