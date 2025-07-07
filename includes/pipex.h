/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:37:38 by diade-so          #+#    #+#             */
/*   Updated: 2025/07/07 12:23:37 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdbool.h>

typedef struct s_pipex
{
	int	in_fd;
	int	out_fd;
	int	prev_fd;
	int	pipefd[2];
	int	i;
	pid_t	child;
}	t_pipex;

typedef struct s_copy_state
{
	size_t	i;
	size_t	j;
	bool	in_single;
	bool	in_double;
}	t_copy_state;

// prototypes for utils.c
void    write_error_exit(char *msg);
bool    is_empty_cmd(const char *cmd);
void	print_error_exit(char *str);
void    free_array(char **arr);
char    **split_tokens(char *cmd, char c);

// prototypes for path_utils.c
bool    is_path(const char *cmd);
char    *get_path_variable(char **envp);
char    *get_full_path(char *path, char *cmd);
void    find_and_exec_cmd(char **paths, char **cmds, char **envp);
void    get_cmd_path(char *cmd, char **envp);

// prototypes for smart_split.c
size_t	count_tokens(char *s);
size_t	get_token_length(const char *s, char c);
void	copy_token(char *dst, const char *src, size_t len);
char	*allocate_copy_tokens(char **s, char c);
char	**smart_split(char *str, char c);

// prototypes for exec.c
void    process_cmd(char *cmd, t_pipex *p, char **envp);
void    exec_mid_cmds(int argc, char **argv, t_pipex *p, char **envp);
void    exec_last_cmd(int argc, char **argv, t_pipex *p, char **envp);

// prototypes for validate.c
void    validate_args(int argc, char **argv, char **envp);

// prototypes for child_utils.c
int    reap_children(pid_t last_pid);

#endif
