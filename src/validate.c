/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:18:20 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/03 11:19:07 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_args(int argc, char **argv, char **envp)
{
	int	i;

	if (access(argv[1], R_OK) == -1)
		print_error_exit(argv[1]);
	if (access(argv[argc - 1], F_OK) == 0)
		if (access(argv[argc - 1], W_OK) == -1)
			print_error_exit(argv[argc - 1]);
	i = 0;
	while (i < argc - 1)
	{
		if (is_empty_cmd(argv[i]))
		{
			write(STDERR_FILENO, "Error: empty\n", 13);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (!get_path_variable(envp))
	{
		write(2, "Error: no path found\n", 21);
		exit(EXIT_FAILURE);
	}
}
