/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:15:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/07/07 12:16:08 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_cmd(char *cmd, t_pipex *p, char **envp)
{
	if (dup2(p->in_fd, STDIN_FILENO) == -1)
		print_error_exit("dup2 in_fd");
	if (dup2(p->out_fd, STDOUT_FILENO) == -1)
		print_error_exit("dup2 out_fd");
	if (p->in_fd != STDIN_FILENO)
		close(p->in_fd);
	if (p->out_fd != STDOUT_FILENO)
		close(p->out_fd);
	get_cmd_path(cmd, envp);
}

void	exec_mid_cmds(int argc, char **argv, t_pipex *p, char **envp)
{
	p->i = 2;
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
			if (p->i == 2)
				p->in_fd = open(argv[1], O_RDONLY);
			else
				p->in_fd = p->prev_fd;
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

void	exec_last_cmd(int argc, char **argv, t_pipex *p, char **envp)
{
	if ((p->child = fork()) == -1)
		print_error_exit("Fork");
	if (p->child == 0)
	{
		p->in_fd = p->prev_fd;
		p->out_fd = open(argv[argc - 1], 
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->out_fd < 0)
			print_error_exit("open outfile");
		process_cmd(argv[argc - 2], p, envp);
	}
	if (p->prev_fd)
		close(p->prev_fd);
}
