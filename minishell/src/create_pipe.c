/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankinzin <ankinzin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:52:55 by ankinzin          #+#    #+#             */
/*   Updated: 2023/07/01 10:52:56 by ankinzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* This func sets up a sytem of pipes for different parts of the shell program
** to communicate with each other*/
void	create_pipe(t_msh *data)
{
	int	i;

	i = 0;
	if (data->npipe == 0)
		return ;
	data->fd = (int **)malloc(sizeof(int *) * data->npipe);
	if (!data->fd)
	{
		ft_putstr_fd("Error while trying to malloc.\n", STDERR_FILENO);
		free_all(data);
		exit(1);
	}
	while (i < data->npipe)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(data->fd[i]) < 0)
		{
			ft_putstr_fd("Error while opening pipes\n", STDERR_FILENO);
			free_all(data);
			exit(1);
		}
		i++;
	}
}

/* this func takes care of connecting to the commands together using pipes and
** redirects their input & output appropriately, this allows commands to
** pass data between each other, creating a pipeline of operations*/
void	do_pipe(t_msh *data)
{
	t_scom	*tmp;

	tmp = data->lst_cmd;
	if (tmp->i == 0)
		redirect_updt(tmp->ft_stdin, data->fd[0][1]);
	else if (tmp->i == data->npipe)
		redirect_updt(data->fd[data->npipe - 1][0], tmp->ft_stdout);
	else
		redirect_updt(data->fd[tmp->i - 1][0], data->fd[tmp->i][1]);
	close_pipes(data);
}
