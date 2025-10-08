/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:23:20 by migarrid          #+#    #+#             */
/*   Updated: 2025/10/08 23:36:03 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	handle_child(t_shell *data, t_node *node, int *pipefd, int side)
{
	if (side == LEFT)
	{
		setup_signals_child();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		executor_recursive(data, node, CHILD);
	}
	if (side == RIGHT)
	{
		setup_signals_child();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		executor_recursive(data, node, CHILD);
	}
}

void	exec_pipe(t_shell *data, t_node *node, int mode)
{
	int		pipefd[2];
	int 	status;
	pid_t	pid_left;
	pid_t	pid_right;

	status = 0;
	if (pipe(pipefd) == ERROR)
		exit_error(data, ERR_PIPE, EXIT_FAILURE);
	pid_left = fork();
	pid_right = fork();
	if (pid_left == ERROR || pid_right == ERROR)
		return(close_pipes(pipefd), (void)exit_error(data, ERR_FORK, FAIL));
	if (pid_left == 0)
		handle_child(data, node->left, pipefd, LEFT);
	if (pid_right == 0)
		handle_child(data, node->right, pipefd, RIGHT);
	close_pipes(pipefd);
	waitpid(pid_left, &status, 0);
	if (!node->right->background)
	{
		waitpid(pid_right, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
	}
}
