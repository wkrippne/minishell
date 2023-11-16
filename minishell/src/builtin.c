/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:51:10 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 13:39:08 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/parser.h"

/* This func checks the provided command and performs the corresponding action
** it can update the current directory, modify env variables, or remove them
** or exit the program*/
void	exit_or_update_env(t_msh *data, char *cmd)
{
	if (abs_string_cmp(cmd, "cd"))
		return (builtin_cd_update(data));
	if (abs_string_cmp(cmd, "export"))
		return (builtin_export_update(data));
	if (abs_string_cmp(cmd, "unset"))
		return (builtin_unset_update(data));
	if (abs_string_cmp(cmd, "exit"))
		return (builtin_exit_update(data));
}

/* This is responsible for executing bulitin commands*/
void	do_builtin(t_msh *data, char *cmd)
{
	if (abs_string_cmp(cmd, "echo"))
		builtins_echo(data);
	else if (abs_string_cmp(cmd, "cd"))
		builtin_cd(data);
	else if (abs_string_cmp(cmd, "export"))
		builtin_export(data);
	else if (abs_string_cmp(cmd, "unset"))
		builtin_unset(data);
	else if (abs_string_cmp(cmd, "env"))
		builtin_env(data);
	else if (abs_string_cmp(cmd, "pwd"))
		builtin_pwd(data);
	else
		builtin_exit(data);
}

/* This is to check if the given command is a valid builtin command
** and handles it as it is supposed to*/
bool	check_builtin(char *cmd)
{
	if (abs_string_cmp(cmd, "echo"))
		return (true);
	if (abs_string_cmp(cmd, "cd"))
		return (true);
	if (abs_string_cmp(cmd, "pwd"))
		return (true);
	if (abs_string_cmp(cmd, "export"))
		return (true);
	if (abs_string_cmp(cmd, "unset"))
		return (true);
	if (abs_string_cmp(cmd, "env"))
		return (true);
	if (abs_string_cmp(cmd, "exit"))
		return (true);
	return (false);
}
