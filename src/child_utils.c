/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 11:47:23 by diade-so          #+#    #+#             */
/*   Updated: 2025/07/07 13:06:58 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	reap_children(pid_t last_pid)
{
	int	status;
	int	last_exit;
	pid_t	pid;

	last_exit = -1;
	pid = wait(&status);
	while (pid > 0)
	{
		if (WIFEXITED(status))
		{
			if (pid == last_pid)
				last_exit = WEXITSTATUS(status);
		}
		pid = wait(&status);
	}
	return (last_exit);
}

