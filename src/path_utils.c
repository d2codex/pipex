/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:45:37 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/02 16:06:10 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_path(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

char	*get_path_variable(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i],  "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_full_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
	{
		errno = ENOMEM;
		perror("strjoin1");
		return (NULL);
	}
	full_path = ft_strjoin(tmp, cmd);
	if (!full_path)
	{
		errno = ENOMEM;
		perror("strjoin2");
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (full_path);
}

void	find_and_exec_cmd(char **paths, char **cmds, char **envp)
{
	char	*full_path;
	int	i;

	i = 0;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], cmds[0]);
		if (!full_path)
		{
			free_array(paths);
			free_array(cmds);
			errno = ENOMEM;
			perror("full_path");
			exit(EXIT_FAILURE) ;
		}
		execve(full_path, cmds, envp);
		free(full_path);
 		i++;
	}
	perror("execve fail");
	free_array(paths);
	free_array(cmds);
	exit(EXIT_FAILURE);
}

void	get_cmd_path(char *cmd, char **envp)
{
	char	**cmds;
	char	*raw_path;
	char	**paths;

	if (is_path(cmd))
	{
		cmds = split_tokens(cmd, ' ');
		execve(cmds[0], cmds, envp);
		free_array(cmds);
		print_error_exit("excve");
	}
	raw_path = get_path_variable(envp);
	if (!raw_path)
		exit(EXIT_FAILURE);
	cmds = split_tokens(cmd, ' ');
	paths = ft_split(raw_path, ':');
	if (!paths)
	{
		free_array(cmds);
		errno = ENOMEM;
		print_error_exit("split fail2");
	}
	find_and_exec_cmd(paths, cmds, envp);
}
