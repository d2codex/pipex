/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:47:58 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/11 12:48:17 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{ 
	t_pipex	p;

	if (argc != 5)
		write_error_exit("Usage: ./pipex infile cmd1 cmd2 outfile\n");
	validate_args(argc, argv, envp);
	exec_mid_cmds(argc, argv, &p, envp);
	exec_last_cmd(argc, argv, &p, envp);	
	while (wait(NULL) > 0);
	return (0);
}
