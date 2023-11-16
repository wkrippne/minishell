/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:36:30 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/05 11:24:02 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This func helps us execute a command in our minishell using the execve system
** call, if everything goes well the command runs, but if there's a progra, we
** an error message and stops the shell*/
void	execute_execve(t_msh *data, char *path_cmd)
{
	char	**cmd;

	cmd = (char **)data->lst_cmd->argv;
	if (execve(path_cmd, cmd, data->env) < 0)
	{
		printf("msh: error on execve\n");
		exit(1);
	}
}

/* This func helps us combine a directory path and a command or
** filename to create a full path by adding a slash between the
** path and the command, and we get the resulting file path*/
static char	*path_plus_cmd(char *path, char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	str = ft_strjoin(tmp, cmd);
	free (tmp);
	return (str);
}

/* This func helps us check if a command or file exists in 
** a list of directories, we split the list of directories,
** create file paths by combining each directory with the
** command and check if any of the paths exist, if found
** we return it otherwise we return Null*/
char	*check_access(char *path, char *cmd)
{
	int		i;
	char	*str;
	char	**table_path;

	i = -1;
	table_path = ft_split(path, ':');
	while (table_path[++i])
	{
		str = path_plus_cmd(table_path[i], cmd);
		if (access(str, F_OK) == 0)
		{
			free_table(table_path);
			return (str);
		}
		free (str);
	}
	free_table(table_path);
	return (NULL);
}
