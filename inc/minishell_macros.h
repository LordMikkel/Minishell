/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migarrid <migarrid@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:51:56 by migarrid          #+#    #+#             */
/*   Updated: 2025/08/09 21:16:55 by migarrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MACROS_H
# define MINISHELL_MACROS_H

/* ************************************************************************** */
/*                                  Limits                                    */
/* ************************************************************************** */
# define STDIN			0
# define STDOUT			1
# define STDERR			2
# define TRUE			1
# define FALSE			0
# define READ			0
# define WRITE			1
# define OUTFILE		1
# define APPEND			0
# define TRUNCATE		1
# define READ_ONLY		2
# define ERROR			-1
# define ERROR_EXECVE	1
# define EXIT_CMD		127
# define BUFFER_SIZE	1024
# define FILE_PERMS		0644

/* ************************************************************************** */
/*                                 Msg.Errors                                 */
/* ************************************************************************** */
# define ERRNO			"Errno: %s\n"
# define ERR_ARGS		"Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n"
# define ERR_PERMS		"Error: '%s' Permission denied\n"
# define ERR_PIPE		"Error: Failed to create pipe. System limit reached\n"
# define ERR_FILE		"Error: '%s' No such file or directory\n"
# define ERR_CMD		"Error: '%s' command not found\n"
# define ERR_CMD_N		"Error: '' command not found\n"
# define ERR_EXEC		"Error: Failed to execute command\n"
# define ERR_FORK		"Error: Fork process failed\n"
# define ERR_MEM		"Error: Memory alloc failed. Check system resources\n"

#endif
