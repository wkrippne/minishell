/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:23:35 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/03 12:36:43 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* This func is used to show you the folder you are currently in, prints it's
** name on the screen*/
void	builtin_pwd(t_msh *data)
{
	char	*path;

	if (data->lst_cmd->argv[1])
	{
		ft_putstr_fd("msh: pwd: too many arguments\n", 2);
		return ;
	}
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free (path);
	g_exit_status = 0;
}
