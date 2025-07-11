/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:47:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/07/07 12:17:30 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{ 
	t_pipex	p;
	int	exit_code;

	if (argc != 5)
		write_error_exit("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	validate_args(argc, argv, envp);
	exec_mid_cmds(argc, argv, &p, envp);
	exec_last_cmd(argc, argv, &p, envp);
	exit_code = reap_children(p.child);
	return (exit_code);
}
