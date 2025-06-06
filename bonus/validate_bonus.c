/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:11:31 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/06 10:26:04 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	validate_args_bonus(int argc, char **argv, char **envp)
{
	int	i;
	int	cmd_start;

	if (!is_here_doc(argv[1]))
	{
		if (access(argv[1], R_OK) == -1)
			print_error_exit(argv[1]);
	}
	if (access(argv[argc - 1], F_OK) == 0)
		if (access(argv[argc - 1], W_OK) == -1)
			print_error_exit(argv[argc - 1]);
	cmd_start = get_cmd_start_index(argv);
	i = cmd_start;
	while (i < argc - 1)
	{
		if (is_empty_cmd(argv[i]))
			write_error_exit("Error: empty cmd");
		i++;
	}
	if (!get_path_variable(envp))
		write_error_exit("Error: no path found");
}
