/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:46:28 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:54:38 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This func checks the status of each command that was executed in the
** Minishell program, if a command exited normally it updates the exit
** status variable to indicate success, else error*/
void	get_exit_status(t_msh *data)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < data->nscom)
	{
		pid = waitpid(data->pid[i++], &status, 0);
		if (pid < 0)
			continue ;
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}
