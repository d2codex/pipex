/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:12:36 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/06 10:07:09 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	process_cmd(char *cmd, t_pipex *p, char **envp)
{ if (dup2(p->in_fd, STDIN_FILENO) == -1)
		print_error_exit("dup2 in_fd");
	if (dup2(p->out_fd, STDOUT_FILENO) == -1)
		print_error_exit("dup2 out_fd");

	if (p->in_fd != STDIN_FILENO)
		close(p->in_fd);
	if (p->out_fd != STDOUT_FILENO)
		close(p->out_fd);
	printf("Executing command: %s\n", cmd);
	get_cmd_path(cmd, envp);
}

void	init_input_fd(t_pipex *p, int cmd_start)
{
	if (p->i != cmd_start)
		p->in_fd = p->prev_fd;
}

void	exec_mid_cmds_bonus(int argc, char **argv, t_pipex *p, char **envp)
{
	int	cmd_start;

	cmd_start = get_cmd_start_index(argv);
	p->i = cmd_start;
	p->prev_fd = -1;
	while (p->i < argc - 2)
	{
		if (pipe(p->pipefd) == -1)
			print_error_exit("Pipe");
		p->child = fork();
		if (p->child == -1)
			print_error_exit("Fork");
		if (p->child == 0)
		{
			init_input_fd(p, cmd_start);
			close(p->pipefd[0]);
			p->out_fd = p->pipefd[1];
			process_cmd(argv[p->i], p, envp);
		}
		if (p->prev_fd != -1)
			close(p->prev_fd);
		close(p->pipefd[1]);
		p->prev_fd = p->pipefd[0];
		p->i++;
	}
}

void	exec_last_cmd_bonus(int argc, char **argv, t_pipex *p, char **envp)
{
	int	flags;

	p->child = fork();
	if (p->child == -1)
		print_error_exit("Fork");
	if (p->child == 0)
	{
		p->in_fd = p->prev_fd;
		flags = O_WRONLY | O_CREAT;
		if (is_here_doc(argv[1]))
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		p->out_fd = open(argv[argc -1], flags, 0644);
		if (p->out_fd == -1)
			print_error_exit(argv[argc -1]);
		process_cmd(argv[argc -2], p, envp);
	}
	close(p->prev_fd);
}
