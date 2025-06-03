/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:43:35 by diade-so          #+#    #+#             */
/*   Updated: 2025/06/01 15:13:42 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*
typedef struct	s_copy_state
{
	size_t	i;
	size_t	j;
	bool	in_single;
	bool	in_double;
}	t_copy_state;

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
*/

size_t	count_tokens(char *s)
{
	bool	in_single;
	bool	in_token;
	bool	in_double;
	int	count;

	in_single = false;
	in_double = false;
	in_token = false;
	count = 0;
	while (*s)
	{
		if (*s == '\'' && !in_double)
			in_single = !in_single;
		else if (*s == '"' && !in_single)
			in_double = !in_double;
		else if (*s == ' '  && !in_single && !in_double)
			in_token = false;	
		else if (!in_token)
		{
			count++;
			in_token = true;
		}
		s++;
	}
	return (count);
}

size_t	get_token_length(const char *s, char c)
{
	size_t	len;
	bool	in_single;
	bool	in_double;

	len = 0;
	in_single = false;
	in_double = false;
	while(s[len])
	{
		if( s[len] == '\'' && !in_double)
			in_single = !in_single;
		else if (s[len] == '"' && !in_single)
			in_double = !in_double;
		else if (s[len] == c && !in_single && !in_double)
			break ;
		len++;
	}
	return (len);
}

void	copy_token(char *dst, const char *src, size_t len)
{
	t_copy_state	cs;

	cs.i = 0;
	cs.j = 0;
	cs.in_single = false;
	cs.in_double = false;
	while (cs.i < len)
	{
		if (src[cs.i] == '\'' && !cs.in_double)
		{
			cs.in_single = !cs.in_single;
			cs.i++;
			continue ;
		}
		if (src[cs.i] == '"' && !cs.in_single)
		{
			cs.in_double = !cs.in_double;
			cs.i++;
			continue ;
		}
		dst[cs.j++] = src[cs.i++];
	}
	dst[cs.j] = '\0';
}

char	*allocate_copy_tokens(char **s, char c)
{
	const char	*start;
	char		*token;
	size_t		len;
	
	while (**s == c)
		(*s)++;
	if (**s == '\0')
		return (NULL);
	start = *s;
	len = get_token_length(start, c);
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	copy_token(token, start, len);	
	*s += len;
	return (token);
}

char	**smart_split(char *str, char c)
{
	char	**str_arr;
	int	tokens;
	int	i;

	if (!str)
		return (NULL);
	tokens = count_tokens(str);
	str_arr = malloc((tokens + 1) * sizeof (*str_arr));
	if (!str_arr)
		return (NULL);
	i = 0;
	while(i < tokens)
	{
		str_arr[i] = allocate_copy_tokens(&str, c);
		if (!str_arr[i])
		{
			free_array(str_arr);
			return (NULL);
		}
		i++;
	}
	str_arr[i] = NULL;
	return (str_arr);
}
/*
int	main(int argc, char **argv)
{
	char	**tokens;
	int	i;

	if (argc != 3)
		return (1);
	tokens = smart_split(argv[1], argv[2][0]);
	if (!tokens)
		return (1);
	i = 0;
	while(tokens[i])
	{
		printf("%s\n", tokens[i]);
		i++;
	}
	free_array(tokens);
	return (0);		
}*/
