/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:12:46 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/06 10:46:19 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex p;

	p.here_doc = 0;
	if (argc < 6)
 		write_error_exit("Error. Invalid number of args\n");
	if (is_here_doc(argv[1]))
	{
		p.here_doc = 1;
		handle_here_doc(argv[2]);
		p.in_fd = open(".here_doc_temp", O_RDONLY);
		if (p.in_fd == -1)
			print_error_exit("here_doc temp file open read");
	}
	else
	{
		p.in_fd = open(argv[1], O_RDONLY);
		if (p.in_fd == -1)
			print_error_exit(argv[1]);
	}
	validate_args_bonus(argc, argv, envp);
	exec_mid_cmds_bonus(argc, argv, &p, envp);
	exec_last_cmd_bonus(argc, argv, &p, envp);
	while (wait(NULL) > 0);
	if (p.here_doc && p.in_fd >= 0)
	{
		close(p.in_fd);
		unlink(".here_doc_temp");
	}
	return (0);
}

