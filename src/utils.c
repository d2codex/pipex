/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:38:13 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/05 13:38:12 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_error_exit(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

bool	is_empty_cmd(const char *cmd)
{
	if (!cmd)
		return (true);
	while (*cmd)
	{
		if(!ft_isspace((unsigned char)*cmd))
			return (false);
		cmd++;
	}
	return (true);
}

void	print_error_exit(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_array(char **arr)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**split_tokens(char *cmd, char c)
{
	char	**tokens;

	tokens = smart_split(cmd, c);
	if (!tokens)
	{
		perror("split fail");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}
