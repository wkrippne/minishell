/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:39:18 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 11:28:23 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_cd_up(t_msh *data);

/* This Function moves you to the previous dirctory you were in, updates the
environment variables to reflect the change, and makes sure everything is
working correctly*/
static void	go_back_up(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = get_value_from_key(data->ppt->list, "OLDPWD");
	if (chdir(next_pwd) != 0)
		return (free (next_pwd));
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

/* this func takes you back to your home directory, updates the environment
** variables to reflect the change, and makes sure everything works correctly*/
static void	go_home_up(t_msh *data)
{
	char	*home;
	char	*actual_pwd;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
		return (free(home));
	if (chdir(home) != 0)
		return (free (home));
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &home);
}

/* This func takes a directory path and either goes back to the
** previous directory, goes to the home directory, or changes to
** a new directory*/
static void	do_cd_up(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = ft_strdup(data->lst_cmd->argv[1]);
	if (abs_string_cmp(next_pwd, "-"))
		return (free (next_pwd), go_back_up(data));
	if (abs_string_cmp(next_pwd, "~"))
		return (free (next_pwd), go_home_up(data));
	if (chdir(next_pwd) != 0)
		return (free (next_pwd));
	free (next_pwd);
	next_pwd = getcwd(NULL, 0);
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

/* In terms this checks the number of commands given by the user
**  if there is only one command it goes to the home directory,
** if there are two commands it changes to the specified directory
** finally sets the exit status to 0*/
void	builtin_cd_update(t_msh *data)
{
	int	number_cmds;

	number_cmds = 0;
	while (data->lst_cmd->argv[number_cmds])
		number_cmds++;
	if (number_cmds > 2)
		return ;
	if (number_cmds == 1)
		go_home_up(data);
	if (number_cmds == 2)
		do_cd_up(data);
	g_exit_status = 0;
}
