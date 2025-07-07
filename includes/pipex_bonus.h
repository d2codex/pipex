/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:37:38 by diade-so          #+#    #+#             */
/*   Updated: 2025/07/07 13:03:27 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

#include "libft.h"
#include "pipex.h"

// prototypes for exec_bonus.c
void    process_cmd(char *cmd, t_pipex *p, char **envp);
void    init_input_fd(t_pipex *p, int cmd_start, char **argv);
void    exec_mid_cmds_bonus(int argc, char **argv, t_pipex *p, char **envp);
void    exec_last_cmd_bonus(int argc, char **argv, t_pipex *p, char **envp);

// prototypes for utils_bonus.c
bool    is_here_doc(char *arg);
int     get_cmd_start_index(char **argv);
void    handle_here_doc(char *limiter);

// prototypes for validate_args_bonus.c
void    validate_args_bonus(int argc, char **argv, char **envp);

#endif
