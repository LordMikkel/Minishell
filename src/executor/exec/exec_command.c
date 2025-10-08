/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:23:14 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/08 23:30:27 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	apply_properties(t_shell *data, t_node *node, t_env *env)
{
	if (node->assig_tmp)
		my_export(data, data->prompt.tokens, env, node);
	// if (node->redir);
	// 	apply_redirs();
}

void	wait_cmd_background(t_shell *data, t_node *node, pid_t pid)
{
	int status;

	status = 0;
	if (!node->background)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
	}
	if (node->background)
	{
		ft_printf_fd(STDOUT, "[&] %d\n", pid);
		data->exit_code = 0;
	}
}

void	execute_cmd_from_child(t_shell *data, t_node *node, t_env *env)
{
	char	*path;

	apply_properties(data, node, env);
	path = get_path(data, node->token->value, env->envp);
	execve(path, node->args, env->envp);
	free(path);
	exit_error(data, ERR_EXEC, EXIT_CMD_NOT_EXEC, node->token->value);
}

void	execute_cmd_from_father(t_shell *data, t_node *node, t_env *env)
{
	pid_t	pid;
	char	*path;

	pid = fork();
	if (pid == ERROR)
		exit_error(data, ERR_FORK, EXIT_FAILURE);
	if (pid == 0)
	{
		setup_signals_child();
		apply_properties(data, node, env);
		path = get_path(data, node->token->value, env->envp);
		execve(path, node->args, env->envp);
		free(path);
		exit_error(data, ERR_EXEC, EXIT_CMD_NOT_EXEC, node->token->value);
	}
	wait_cmd_background(data, node, pid);
}

void	exec_command(t_shell *data, t_node *node, t_env *env, int mode)
{
	if (mode == CHILD)
		execute_cmd_from_child(data, node, env);
	if (mode == FATHER)
		execute_cmd_from_father(data, node, env);
}
