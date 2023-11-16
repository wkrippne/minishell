/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:34:55 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 11:41:44 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_cd(t_msh *data);

/* This dunc gets the previous directory path, tries to change the current
** directory to that path, and updates the necessary environment variables*/
static void	go_back(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = get_value_from_key(data->ppt->list, "OLDPWD");
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		free (next_pwd);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

/* this func gets the home directory path, tries to change the current
** directory to that path, and updates the necessary environment variables
** accordingly, if the home directory is not set or there is an error
** we print it otherwise we go to the home directory*/
static void	go_home(t_msh *data)
{
	char	*home;
	char	*actual_pwd;

	home = get_value_from_key(data->ppt->list, "HOME");
	if (!home)
		return (free (home), ft_putstr_fd("msh: HOME not set\n", 2));
	if (chdir(home) != 0)
	{
		perror("chdir");
		free (home);
		return ;
	}
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &home);
}

/* This Function takes an argument to change the current directory, if the
** argument is '-' it goes back to the previous directory if the argument
** '~' it goes to the home directory*/
static void	do_cd(t_msh *data)
{
	char	*next_pwd;
	char	*actual_pwd;

	next_pwd = ft_strdup(data->lst_cmd->argv[1]);
	if (abs_string_cmp(next_pwd, "-"))
		return (free (next_pwd), go_back(data));
	if (abs_string_cmp(next_pwd, "~"))
		return (free (next_pwd), go_home(data));
	if (chdir(next_pwd) != 0)
	{
		perror("chdir");
		free (next_pwd);
		return ;
	}
	free (next_pwd);
	next_pwd = getcwd(NULL, 0);
	actual_pwd = get_value_from_key(data->ppt->list, "PWD");
	modify_value(data, "OLDPWD", &actual_pwd);
	modify_value(data, "PWD", &next_pwd);
}

/* this func handles the cd command it checks the number of arguments
** provided and performs the appropriate action, if there are too many
** arguments it shows an error message, if one we change the current
** directory if it is 2 commands we also change the directory to the
** specified path*/
void	builtin_cd(t_msh *data)
{
	int	number_cmds;

	number_cmds = 0;
	while (data->lst_cmd->argv[number_cmds])
		number_cmds++;
	if (number_cmds > 2)
		return (ft_putstr_fd("msh: cd: too many arguments\n", 2));
	if (number_cmds == 1)
		go_home(data);
	if (number_cmds == 2)
		do_cd(data);
	free_table(data->env);
	init_env_table(data);
	g_exit_status = 0;
}
