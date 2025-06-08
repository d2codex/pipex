/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:12:46 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/08 19:38:29 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex p;

	if (argc < 4)
 		write_error_exit("Error. Invalid number of args\n");
	if (is_here_doc(argv[1]))
		handle_here_doc(argv[2]);
	validate_args_bonus(argc, argv, envp);
	exec_mid_cmds_bonus(argc, argv, &p, envp);
	exec_last_cmd_bonus(argc, argv, &p, envp);
	while (wait(NULL) > 0);
	if (p.in_fd > 2)
		close(p.in_fd);	
	if (is_here_doc(argv[1]))
		unlink(".here_doc_temp");
	return (0);
}

