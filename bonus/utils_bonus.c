/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:25:11 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/05 17:19:34 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

bool	is_here_doc(char *arg)
{
	return (ft_strncmp(arg, "here_doc", 9) == 0);
}

int	get_cmd_start_index(char **argv)
{
	if (is_here_doc(argv[1]))
		return (3);
	else
		return (2);
}

void	handle_here_doc(char *limiter)
{
	int	fd;
	char	*line;

	fd = open (".here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		print_error_exit("here_doc temp file open");
	while (1)
	{
		write(2, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		if (access(".here_doc_temp", F_OK) == -1)
			write_error_exit("Temp file missing");
		free(line);
	}
	close(fd);
}

